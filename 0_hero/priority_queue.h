#pragma once
#include <list>
#include <map>
#include <set>

template <typename T, typename TCont>
class priority_queue {
public:
	explicit priority_queue() = default;

	explicit priority_queue(const size_t size) {
		this->elems_.resize(size);
		this->size_ = size;
		this->capacity_ = size;
	}

	explicit priority_queue(const TCont& elems) {
		this->size_ = this->elems_.size();
		this->capacity_ = this->size_;
		this->elems_.resize(this->size_);

		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			this->elems_[ptr] = elems[ptr];
			this->pos_hsh_[this->elems_[ptr]] = ptr;
		}
	}

	template <typename... Args>
	explicit priority_queue(Args&&... args) {
		this->elems_.push_back(std::forward<Args>(args)...);
		this->size_ = this->elems_.size();
		this->capacity_ = this->size_;
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			this->pos_hsh_[this->elems_[ptr]] = ptr;
		}
	}

	~priority_queue() {}

	void Add(const T& elem) {
		this->elems_.push_back(elem);
		this->pos_hsh_[elem].insert(this->elems.size() - 1);
		this->size_++;
	}

	T Peek() {
		if (this->IsEmpty) {
			return nullptr;
		}
		return this->elems_[0];
	}

	T Poll() {

	}

	T Remove(const T& elem) {

	}

	void Clear() {
		for (size_t ptr = 0; ptr < this->capacity_; ptr++) {
			this->elems_[ptr] = NULL;
		}
		this->size_ = 0;
		this->pos_hsh_.clear;
	}

	bool IsEmpty() const {
		return this->size_ == 0;
	}

	size_t Size() const {
		return this->size_;
	}

	void Bubling() {

	}

private:
	bool Swap(const size_t lhs_pos, const size_t rhs_pos) {
		if (lhs_pos >= this->size_ || rhs_pos >= this->size_) {
			return false;
		}
		auto lhs_hsh_iter = this->pos_hsh_.at(this->elems[lhs_pos]).find(lhs_pos);
		auto rhs_hsh_iter = this->pos_hsh_.at(this->elems[rhs_pos]).find(rhs_pos);
		if (lhs_pos == this->pos_hsh_.at(this->elems[lhs_pos]).end() || rhs_pos == this->pos_hsh_.at(this->elems[rhs_pos]).end()) {
			return false;
		}
		std::swap(*lhs_hsh_iter, *rhs_hsh_iter);
		return true;
	}

	size_t size_ = 0;
	size_t capacity_ = 0;
	std::list<T> elems_;
	std::map<T, std::set<size_t>> pos_hsh_;
};

