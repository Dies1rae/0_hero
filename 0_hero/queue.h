#pragma once

#include "SingleLinkedLIst.h"

class queue {
public:
	explicit queue() = default;
	explicit queue(const int& val) {
		this->Enqueue(val);
	}
	explicit queue(const LinkedList * node) {
		this->Enqueue(node->val_);
	}

	~queue() {
		while (head_) 	{
			LinkedList* tmp_root = this->head_;
			this->head_ = this->head_->next_;
			delete tmp_root;
		}
	}

	void Enqueue(const int& val) {
		LinkedList* next_node = new LinkedList(val);
		if (!this->head_) {
			this->head_ = next_node;
			this->tail_ = this->head_;
		} else {
			this->tail_->next_ = next_node;
			this->tail_ = this->tail_->next_;
		}
		this->size_++;
	}

	void Dequeue() {
		if (!this->head_) {
			this->size_ = 0;
			return;
		}
		if (this->head_ != this->tail_) {
			LinkedList* prev_node = this->head_;
			this->head_ = this->head_->next_;
			delete prev_node;
		} else if (this->head_ == this->tail_) {
			LinkedList* prev_node = this->head_;
			this->head_ = this->head_->next_;
			this->tail_ = this->tail_->next_;
			delete prev_node;
		}
		this->size_--;
	}

	LinkedList* Head() const noexcept {
		return this->head_;
	}

	LinkedList* Tail() const noexcept {
		return this->tail_;
	}

	size_t Size() const {
		return this->size_;
	}
	
	bool IsEmpty() const {
		return this->size_ == 0;
	}

private:
	size_t size_ = 0;
	LinkedList* head_ = nullptr;
	LinkedList* tail_ = nullptr;
};

