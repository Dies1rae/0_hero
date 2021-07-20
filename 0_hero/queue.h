#pragma once

#include "SingleLinkedLIst.h"
#include <stdexcept>

template <typename T>
class queue {
public:
	explicit queue() = default;
	explicit queue(const T& val) {
		this->Enqueue(val);
	}
	explicit queue(const LinkedList<T> * node) {
		this->Enqueue(node->val_);
	}

	~queue() {
		while (head_) 	{
			LinkedList* tmp_root = this->head_;
			this->head_ = this->head_->next_;
			delete tmp_root;
		}
	}

	void Enqueue(const T& val) {
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
			throw std::range_error("Empty queue");
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

	LinkedList<T>* Head() const noexcept {
		return this->head_;
	}

	LinkedList<T>* Tail() const noexcept {
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
	LinkedList<T>* head_ = nullptr;
	LinkedList<T>* tail_ = nullptr;
};

