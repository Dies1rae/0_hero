#pragma once

#include "SingleLinkedLIst.h"

#include <stdexcept>

template <typename T>
class Stack {
public:
	explicit Stack() = default;
	explicit Stack(const T& val) {
		this->Push(val);
	}
	explicit Stack(const LinkedList<T>* node) {
		this->Push(node->val_);
	}

	~Stack() {
		while (this->top_) {
			LinkedList<T>* tmp_root = this->top_;
			this->top_ = this->top_->next_;
			delete tmp_root;
		}
	}

	void Push(const T& val) {
		LinkedList<T>* new_elem = new LinkedList(val);
		new_elem->next_ = this->top_;
		this->top_ = new_elem;
		this->size_++;
	}

	T Pop() {
		if(this->top_) {
			LinkedList<T>* tmp = this->top_;
			this->top_ = this->top_->next_;
			this->size_--;
			T tmp_value = tmp->val_;
			delete tmp;
			return tmp_value;	
		}
		throw std::range_error("Empty stack");
	}

	T Top() const noexcept {
		if (!this->Empty()) {
			return this->top_->val_;
		}
		throw std::range_error("Empty stack");
	}

	T Peek() const noexcept {
		if (!this->Empty()) {
			return this->top_->val_;
		}
		throw std::range_error("Empty stack");
	}

	bool Empty() const {
		return this->size_ == 0;
	}

	size_t Size() const {
		return this->size_;
	}

private:
	size_t size_ = 0;
	LinkedList<T>* top_ = nullptr;
};

