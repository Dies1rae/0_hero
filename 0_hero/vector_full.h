#pragma once
#include <cassert>
#include <cstdlib>
#include <new>
#include <utility>
#include <memory>

template <typename T>
class RawMemory {
public:
    RawMemory() = default;
    RawMemory(const RawMemory&) = delete;

    explicit RawMemory(size_t capacity) : buffer_(Allocate(capacity)), capacity_(capacity) {}
    RawMemory(RawMemory&& other) noexcept {
        this->Allocate(other.capacity_);
        std::swap(this->capacity_, other.capacity_);
        std::swap(this->buffer_, other.buffer_);
    }

    ~RawMemory() {
        Deallocate(buffer_);
    }

    RawMemory& operator=(RawMemory&& rhs) noexcept {
        if (this != &rhs) {
            this->buffer_ = std::move(rhs.buffer_);
            this->capacity_ = std::move(rhs.capacity_);
        }
        return *this;
    }

    RawMemory& operator=(const RawMemory& rhs) = delete;

    T* operator+(size_t offset) noexcept {
        assert(offset <= capacity_);
        return buffer_ + offset;
    }

    const T* operator+(size_t offset) const noexcept {
        return const_cast<RawMemory&>(*this) + offset;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<RawMemory&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < capacity_);
        return buffer_[index];
    }

    void Swap(RawMemory& other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(capacity_, other.capacity_);
    }

    const T* GetAddress() const noexcept {
        return buffer_;
    }

    T* GetAddress() noexcept {
        return buffer_;
    }

    size_t Capacity() const {
        return capacity_;
    }

private:
    static T* Allocate(size_t n) {
        return n != 0 ? static_cast<T*>(operator new(n * sizeof(T))) : nullptr;
    }

    static void Deallocate(T* buf) noexcept {
        operator delete(buf);
    }

    T* buffer_ = nullptr;
    size_t capacity_ = 0;
};

template <typename T>
class Vector {
public:
    using iterator = T*;
    using const_iterator = const T*;

    Vector() = default;

    explicit Vector(size_t size) : data_(size), size_(size) {
        std::uninitialized_value_construct_n(this->data_.GetAddress(), this->size_);
    }

    Vector(const Vector& other) : data_(other.size_), size_(other.size_) {
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(other.data_.GetAddress(), this->size_, this->data_.GetAddress());
        } else {
            std::uninitialized_copy_n(other.data_.GetAddress(), this->size_, this->data_.GetAddress());
        }
    }

    Vector(Vector&& other) noexcept {
        std::swap(this->size_, other.size_);
        this->data_.Swap(other.data_);
    }

    ~Vector() {
        std::destroy(this->data_.GetAddress(), this->data_.GetAddress() + this->size_);
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= this->data_.Capacity()) {
            return;
        }
        RawMemory<T> new_data(new_capacity);
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
        } else {
            std::uninitialized_copy_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
        }
        std::destroy_n(this->data_.GetAddress(), this->size_);
        this->data_.Swap(new_data);
    }

    size_t Size() const noexcept {
        return this->size_;
    }

    size_t Capacity() const noexcept {
        return this->data_.Capacity();
    }

    void Swap(Vector& other) noexcept {
        std::swap(this->size_, other.size_);
        this->data_.Swap(other.data_);
    }

    void Resize(const size_t new_size) {
        if (new_size > this->size_) {
            this->Reserve(new_size);
            std::uninitialized_value_construct_n(this->data_.GetAddress() + this->size_, new_size - this->size_);
        }
        if (new_size < this->size_) {
            std::destroy(this->data_.GetAddress() + new_size, this->data_.GetAddress() + this->size_);
        }
        this->size_ = new_size;
    }

    void PushBack(const T& value) {
        if (this->size_ == this->Capacity()) {
            size_t capacity_tmp = 0;
            this->size_ == 0 ? capacity_tmp += 1 : capacity_tmp += this->size_ * 2;

            RawMemory<T> new_data(capacity_tmp);
            new (new_data + this->size_) T(value);
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            } else {
                std::uninitialized_copy_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            }

            std::destroy_n(this->data_.GetAddress(), this->size_);
            this->data_.Swap(new_data);
        } else {
            new (this->data_ + this->size_) T(value);
        }
        this->size_++;
    }

    void PushBack(T&& value) {
        if (this->size_ == this->Capacity()) {
            size_t capacity_tmp = 0;
            this->size_ == 0 ? capacity_tmp += 1 : capacity_tmp += this->size_ * 2;

            RawMemory<T> new_data(capacity_tmp);
            new (new_data + this->size_) T(std::move(value));
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            } else {
                std::uninitialized_copy_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            }

            std::destroy_n(this->data_.GetAddress(), this->size_);
            this->data_.Swap(new_data);
        } else {
            new (this->data_ + this->size_) T(std::move(value));
        }
        this->size_++;
    }

    void PopBack() noexcept {
        std::destroy_n(this->data_.GetAddress() + this->size_ - 1, 1);
        this->size_--;
    }

    template <typename... Args>
    T& EmplaceBack(Args&&... args) {
        if (this->size_ == this->Capacity()) {
            size_t capacity_tmp = 0;
            this->size_ == 0 ? capacity_tmp += 1 : capacity_tmp += this->size_ * 2;

            RawMemory<T> new_data(capacity_tmp);
            new (new_data + this->size_) T(std::forward<Args>(args)...);
            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            } else {
                std::uninitialized_copy_n(this->data_.GetAddress(), this->size_, new_data.GetAddress());
            }

            std::destroy_n(this->data_.GetAddress(), this->size_);
            this->data_.Swap(new_data);
        } else {
            new (this->data_ + this->size_) T(std::forward<Args>(args)...);
        }
        this->size_++;
        return this->data_[this->size_ - 1];
    }

    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            if (rhs.size_ > this->data_.Capacity()) {
                Vector tmp_cpy(rhs);
                this->Swap(tmp_cpy);
            } else {
                if (rhs.size_ < this->size_) {
                    for (size_t ptr = 0; ptr < rhs.size_; ptr++) {
                        this->data_[ptr] = rhs.data_[ptr];
                    }
                    std::destroy_n(this->data_.GetAddress() + rhs.size_, this->size_ - rhs.size_);
                } else {
                    for (size_t ptr = 0; ptr < this->size_; ptr++) {
                        this->data_[ptr] = rhs.data_[ptr];
                    }
                    std::uninitialized_copy_n(rhs.data_.GetAddress() + this->size_, rhs.size_ - this->size_, this->data_.GetAddress() + this->size_);
                }
            }
        }
        this->size_ = rhs.size_;
        return *this;
    }

    Vector& operator=(Vector&& rhs) noexcept {
        this->Swap(rhs);
        return *this;
    }

    const T& operator[](size_t index) const noexcept {
        return const_cast<Vector&>(*this)[index];
    }

    T& operator[](size_t index) noexcept {
        assert(index < size_);
        return this->data_[index];
    }

    iterator begin() noexcept {
        return this->data_.GetAddress();
    }
    iterator end() noexcept {
        return (this->data_.GetAddress() + this->size_);
    }

    const_iterator begin() const noexcept {
        return this->data_.GetAddress();
    }
    const_iterator end() const noexcept {
        return (this->data_.GetAddress() + this->size_);
    }

    const_iterator cbegin() const noexcept {
        return this->data_.GetAddress();
    }
    const_iterator cend() const noexcept {
        return (this->data_.GetAddress() + this->size_);
    }

    iterator Insert(const_iterator pos, const T& value) {
        return this->Emplace(pos, value);
    }

    iterator Insert(const_iterator pos, T&& value) {
        return this->Emplace(pos, std::forward<T>(value));
    }

    template <typename... Args>
    iterator Emplace(const_iterator pos, Args&&... args) {
        size_t result = pos - this->begin();
        if (this->size_ == result) {
            this->EmplaceBack(std::forward<Args>(args)...);
        } else if (this->size_ < this->Capacity()) {
            T tmp = T(std::forward<Args>(args)...);
            new (this->data_ + this->size_) T(std::move(this->data_[this->size_ - 1u]));
            std::move_backward(this->data_.GetAddress() + result, this->end() - 1, this->end());
            this->data_[result] = std::move(tmp);
            this->size_++;
        } else {
            RawMemory<T> new_data(this->size_ * 2);
            new(new_data + result) T(std::forward<Args>(args)...);

            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(this->data_.GetAddress(), result, new_data.GetAddress());
            } else {
                std::uninitialized_copy_n(this->data_.GetAddress(), result, new_data.GetAddress());
            }

            if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
                std::uninitialized_move_n(this->data_.GetAddress() + result, this->size_ - result, new_data.GetAddress() + result + 1);
            } else {
                std::uninitialized_copy_n(this->data_.GetAddress() + result, this->size_ - result, new_data.GetAddress() + result + 1);
            }

            std::destroy_n(this->data_.GetAddress(), this->size_);
            this->data_.Swap(new_data);
            this->size_++;
        }

        return (this->data_.GetAddress() + result);
    }

    iterator Erase(const_iterator pos) {
        iterator pos_it = const_cast<iterator>(pos);
        std::move(pos_it + 1, this->end(), pos_it);
        std::destroy_n(this->data_.GetAddress() + (--this->size_), 1);
        return pos_it;
    }
private:
    RawMemory<T> data_;
    size_t size_ = 0;
};