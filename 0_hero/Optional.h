#pragma once

#include <stdexcept>
#include <utility>

class BadOptionalAccess : public std::exception {
public:
    using exception::exception;

    virtual const char* what() const noexcept override {
        return "Bad optional access";
    }
};

template <typename T>
class Optional {
public:
    Optional() = default;
    Optional(const T& value) {
        this->data_ptr = new (&this->data_[0]) T(value);
        this->is_initialized_ = 1;
    }
    Optional(T&& value) {
        this->data_ptr = new (&this->data_[0]) T(std::move(value));
        this->is_initialized_ = 1;
    }
    Optional(const Optional& other) {
        if (this != &other) {
            if (!this->is_initialized_ && !other.is_initialized_) {
                this->is_initialized_ = other.is_initialized_;
            } else if (!this->is_initialized_ && other.is_initialized_) {
                this->data_ptr = new (&this->data_[0]) T(*other.data_ptr);
                this->is_initialized_ = 1;
            } else if (this->is_initialized_ && !other.is_initialized_) {
                this->Reset();
            } else if (this->is_initialized_ && other.is_initialized_) {
                this->data_ptr = new (&this->data_[0])T(*other.data_ptr);
            }
        }
    }
    Optional(Optional&& other) {
        if (this != &other) {
            if (!this->is_initialized_ && !other.is_initialized_) {
                this->is_initialized_ = std::move(other.is_initialized_);
            } else if (!this->is_initialized_ && other.is_initialized_) {
                this->data_ptr = new (&this->data_[0]) T(std::move(*other.data_ptr));
                this->is_initialized_ = std::move(other.is_initialized_);
            } else if (this->is_initialized_ && !other.is_initialized_) {
                this->Reset();
            } else if (this->is_initialized_ && other.is_initialized_) {
                std::swap(this->data_, other.data_);
                std::swap(this->data_ptr, other.data_ptr);
                this->is_initialized_ = std::move(other.is_initialized_);
            }
        }
    }

    Optional& operator=(const T& value) {
        if (is_initialized_) {
            **this = value;
        } else {
            this->data_ptr = new (data_) T(value);
            is_initialized_ = 1;
        }
        return *this;
    }
    Optional& operator=(T&& rhs) {
        if (is_initialized_) {
            **this = std::move(rhs);
        } else {
            this->data_ptr = new (this->data_) T(std::move(rhs));
            is_initialized_ = 1;
        }
        return *this;
    }
    Optional& operator=(const Optional& rhs) {
        if (&rhs != this) {
            if (!this->is_initialized_ && !rhs.is_initialized_) {
                this->is_initialized_ = rhs.is_initialized_;
            } else if (!this->is_initialized_ && rhs.is_initialized_) {
                this->data_ptr = new (&this->data_[0]) T(*rhs.data_ptr);
                this->is_initialized_ = 1;
            } else if (this->is_initialized_ && !rhs.is_initialized_) {
                this->Reset();
            } else if (this->is_initialized_ && rhs.is_initialized_) {
                *this->data_ptr = *rhs.data_ptr;
            }
        }

        return *this;
    }
    Optional& operator=(Optional&& rhs) {
        if (&rhs != this) {
            if (!this->is_initialized_ && !rhs.is_initialized_) {
                this->is_initialized_ = std::move(rhs.is_initialized_);
            } else if (!this->is_initialized_ && rhs.is_initialized_) {
                this->is_initialized_ = std::move(rhs.is_initialized_);
                this->data_ptr = new (&this->data_[0]) T(std::move(*rhs.data_ptr));
            } else if (this->is_initialized_ && !rhs.is_initialized_) {
                this->Reset();
            } else if (this->is_initialized_ && rhs.is_initialized_) {
                *this->data_ptr = std::move(*rhs.data_ptr);
            }
        }
        return *this;
    }

    ~Optional() {
        if (is_initialized_) {
            this->data_ptr->~T();
        }
    }

    bool HasValue() const {
        return this->is_initialized_;
    }

    T& operator*()& {
        return *this->data_ptr;
    }
    const T& operator*() const& {
        return *this->data_ptr;
    }
    T* operator->() {
        return this->data_ptr;
    }
    const T* operator->() const {
        return this->data_ptr;
    }

    T& Value()& {
        if (!this->is_initialized_) {
            BadOptionalAccess res;
            throw res;
        }
        return *this->data_ptr;
    }
    const T& Value() const& {
        if (!this->is_initialized_) {
            BadOptionalAccess res;
            res.what();
        }
        return *this->data_ptr;
    }

    T&& operator*()&& {
        return std::move(*this->data_ptr);
    }
    T&& Value()&& {
        if (!this->is_initialized_) {
            BadOptionalAccess res;
            res.what();
        }
        return std::move(*this->data_ptr);
    }

    void Reset() {
        this->~Optional();
        this->is_initialized_ = 0;
        this->data_ptr = nullptr;
    }

    size_t get_data_size() {
        return sizeof(this->data_);
    }

    template <typename... Types>
    Optional& Emplace(Types&&... args) {
        this->data_ptr = new (this->data_) T(T(std::forward<Types>(args)...));
        is_initialized_ = 1;
        return *this;
    }

private:
    T* data_ptr = nullptr;
    alignas(T) char data_[sizeof(T)];
    bool is_initialized_ = false;
};


template <typename T>
inline bool operator==(const T& lhs, const T& rhs) {
    return lhs == rhs;
}

template <typename T>
inline bool operator!=(const T& lhs, const T& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline bool operator==(const Optional<T>& lhs, const Optional<T>& rhs) {
    if (lhs.Value() != rhs.Value()) {
        return false;
    }
    if (lhs.HasValue() != rhs.HasValue()) {
        return false;
    }
    if (lhs.get_data_size() != rhs.get_data_size()) {
        return false;
    }
    return true;
}

template <typename T>
inline bool operator!=(const Optional<T>& lhs, const Optional<T>& rhs) {
    return !(lhs == rhs);
}