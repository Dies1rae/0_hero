#pragma once
#include <list>
#include <map>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename T>
class priority_queue {
public:
	explicit priority_queue() = default;

	explicit priority_queue(const size_t size) {
		this->elems_.resize(size);
		this->size_ = size;
		this->capacity_ = size;
	}
	template <typename TCont>
	explicit priority_queue(const TCont& elems) {
		this->size_ = elems.size();
		this->capacity_ = this->size_ ;

		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			this->elems_.push_back(elems[ptr]);
			std::set<size_t> tmp = this->pos_hsh_[elems[ptr]];
			tmp.insert(ptr);
			this->pos_hsh_[elems[ptr]] = tmp;
		}

		int tmp_ptr = (this->size_ / 2) - 1;
		for (int ptr = std::max(0, tmp_ptr) ; ptr >= 0; ptr--) {
			this->SinkDowmn(ptr);
		}
	}

	~priority_queue() {}

	priority_queue& Add(const T& elem) {
		if (this->size_ < this->capacity_) {	//????????
			this->elems_.push_back(elem);
		} else {
			this->elems_.push_back(elem);
			this->capacity_++;
		}
		
		//this->SwimUp(this->size_);
		this->size_++;
		if (this->size_ > 1) {
			this->HeapSort();
		}
		this->HshRenew();
		return *this;
	}

	T Peek() {
		if (this->IsEmpty()) {
			return NULL;
		}
		
		return *this->elems_.begin();
	}

	T Poll() {
		return this->RemoveAt(0);
	}

	T Remove(const T& elem) {
		if (elem == NULL) {
			throw std::runtime_error("Wrong arg");
		}
		
		size_t rem_index = this->pos_hsh_.at(elem);
		if (rem_index) {
			return this->RemoveAt(rem_index);
		}
		return NULL;
	}

	T RemoveAt(const size_t pos) {
		if (this->IsEmpty()) {
			return NULL;
		}

		this->size_--;

		auto elem_ = this->elems_.begin();
		auto elem_size = this->elems_.begin();
		std::advance(elem_, pos);
		std::advance(elem_size, this->size_);

		T remvd_elem = *elem_;
		std::swap(elem_, elem_size);

		if (pos == this->size_) {
			return remvd_elem;
		}

		std::advance(elem_, pos);
		T tmp_elem = *elem_;
		this->SinkDowmn(pos);
		std::advance(elem_size, pos);

		if (*elem_size == tmp_elem) {
			this->SwimUp(pos);
		}
		return remvd_elem;
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

	bool Contains(T elem) const {
		if (elem == nullptr) {
			return false;
		}
		return this->pos_hsh_.at(elem);
	}

	void PrintPQ() {
		std::cout << "ELEMENTS PRESENTED: ";
		for (const auto& elem : this->elems_) {
			std::cout << elem << ' ';
		}
		std::cout << '\n';
	}

	void PrintHSHPQ() {
		std::cout << "HASH PRESENTED:\n";
		for (const auto& [elem, positions] : this->pos_hsh_) {
			std::cout << elem << ': ';
			for (const auto& pos : positions) {
				std::cout << pos << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	bool isMinHeap(const size_t node_pos = 0) {
		if (node_pos >= this->size_) {
			return true;
		}
		size_t left_ch = 2 * node_pos + 1;
		size_t right_ch = 2 * node_pos + 2;
		if (left_ch < this->size_ && this->LessCmp(node_pos, left_ch)) {
			return false;
		}
		if (right_ch < this->size_ && this->LessCmp(node_pos, right_ch)) {
			return false;
		}
		return this->isMinHeap(left_ch) && this->isMinHeap(right_ch);
	}
protected:
	bool Swap(const size_t lhs_pos, const size_t rhs_pos) {
		if (lhs_pos >= this->size_ || rhs_pos >= this->size_) {
			return false;
		}
		auto elem_l = this->elems_.begin();
		auto elem_r = this->elems_.begin();
		std::advance(elem_l, lhs_pos);
		std::advance(elem_r, rhs_pos);
		auto lhs_hsh_iter = this->pos_hsh_.at(*elem_l).find(lhs_pos);
		auto rhs_hsh_iter = this->pos_hsh_.at(*elem_r).find(rhs_pos);
		if (lhs_hsh_iter == this->pos_hsh_.at(*elem_l).end() || rhs_hsh_iter == this->pos_hsh_.at(*elem_r).end()) {
			return false;
		}
		std::swap(lhs_hsh_iter, rhs_hsh_iter);
		std::swap(elem_l, elem_r);
		return true;
	}

	
private:
	bool LessCmp(const size_t lhs, const size_t rhs) {
	
		auto elem_l = this->elems_.begin();
		auto elem_r = this->elems_.begin();
		std::advance(elem_l, lhs);
		std::advance(elem_r, rhs);
		return *elem_l < *elem_r;
	}

	void HshRenew() {
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			auto it = this->elems_.begin();
			std::advance(it, ptr);
			std::set<size_t> tmp;
			if (this->pos_hsh_[*it].size() != 0) {
				tmp = this->pos_hsh_.at(*it);
			}
			tmp.insert(ptr);
			this->pos_hsh_[*it] = tmp;
		}
	}

	void SwimUp(const size_t node_pos) {
		size_t parrent_left = (node_pos - 1) / 2;
		size_t largest_pos = node_pos;

		while (largest_pos > 0 && this->LessCmp(largest_pos, parrent_left)) {
			//std::swap(this->elems_[largest_pos], this->elems_[parrent_left]);
			this->Swap(largest_pos, parrent_left);
			largest_pos = parrent_left;
			parrent_left = (largest_pos - 1) / 2;
		}
		this->HshRenew();
	}

	void SinkDowmn(size_t node_pos) {
		while (true) {
			size_t left_ch = 2 * node_pos + 1;
			size_t right_ch = 2 * node_pos + 2;
			size_t smallest_pos = left_ch;

			if (right_ch < this->size_ && this->LessCmp(right_ch, left_ch)) {
				smallest_pos = right_ch;
			}
			if (left_ch >= this->size_ || this->LessCmp(node_pos, smallest_pos)) {
				break;
			}
			auto elem_node = this->elems_.begin();
			auto elem_small = this->elems_.begin();
			std::advance(elem_node, node_pos);
			std::advance(elem_small, smallest_pos);
			std::swap(elem_small, elem_node);
			node_pos = smallest_pos;
		}
		this->HshRenew();
	}

	void HeapSort() {
		for (size_t ptr = this->size_ / 2 - 1; ptr >= 0; ptr--) {
			this->Heapify(this->size_, ptr);
		}
		for (size_t ptr = this->size_ - 1; ptr >= 0; ptr--) {
			auto zero = this->elems_.begin();
			auto it = this->elems_.begin();
			std::advance(it, ptr);
			std::swap(zero, it);
			this->Heapify(ptr, 0);
		}
	}

	void Heapify(const size_t heap_size, const size_t node_pos) {
		size_t largest_pos = node_pos;
		size_t left_ch = 2 * node_pos + 1;
		size_t right_ch = 2 * node_pos + 2;

		if (left_ch < largest_pos && this->LessCmp(largest_pos, left_ch)) {
			largest_pos = left_ch;
		}
		if (right_ch < largest_pos && this->LessCmp(largest_pos, right_ch)) {
			largest_pos = right_ch;
		}
		if (largest_pos != node_pos) {
			auto elem_node = this->elems_.begin();
			auto elem_large = this->elems_.begin();
			std::advance(elem_node, node_pos);
			std::advance(elem_large, largest_pos);
			std::swap(elem_node, elem_large);
			Heapify(heap_size, largest_pos);
		}
	}

	size_t size_ = 0;
	size_t capacity_ = 0;
	std::list<T> elems_;
	std::map<T, std::set<size_t>> pos_hsh_;
};

