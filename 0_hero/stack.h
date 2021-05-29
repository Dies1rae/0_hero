#pragma once

#include "SingleLinkedLIst.h"

class Stack {
public:
	explicit Stack() = default;
	explicit Stack(const int& val) {
		this->Push(val);
	}
	explicit Stack(const LinkedList * node) {
		this->Push(node->val_);
	}

	~Stack() {
		while (this->top_) {
			LinkedList* tmp_root = this->top_;
			this->top_ = this->top_->next_;
			delete tmp_root;
		}
	}

	void Push(const int& val) {
		LinkedList* new_elem = new LinkedList(val);
		new_elem->next_ = this->top_;
		this->top_ = new_elem;
		this->size_++;
	}

	int Pop() {
		if(this->top_) {
			LinkedList* tmp = this->top_;
			this->top_ = this->top_->next_;
			this->size_--;
			return tmp->val_;	
		}
	}

	int Top() const noexcept {
		if (!this->Empty()) {
			return this->top_->val_;
		}
	}

	int Peek() const noexcept {
		if (!this->Empty()) {
			return this->top_->val_;
		}
	}

	bool Empty() const {
		return this->size_ == 0;
	}

	size_t Size() const {
		return this->size_;
	}

private:
	size_t size_ = 0;
	LinkedList* top_ = nullptr;
};

