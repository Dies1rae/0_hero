#pragma once
#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <list>

template <typename T>
class priority_queue {
public:
	explicit priority_queue() = default;

	explicit priority_queue(const size_t size) {
		this->elemss_.reserve(size);
		this->size_ = size;
		this->capacity_ = size;
	}

	explicit priority_queue(const std::vector<T>& elems) {
		for (const auto& elem : elems) {
			this->Add(elem);
		}
	}

	template <typename TCont>
	explicit priority_queue(const TCont& elems) {
		this->size_ = elems.size();
		this->capacity_ = this->size_;

		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			this->elems_.push_back(elems[ptr]);
		}

		int tmp_ptr = (this->size_ / 2) - 1;
		for (int ptr = std::max(0, tmp_ptr); ptr >= 0; ptr--) {
			this->SinkDown(ptr);
		}
		this->HshRenew();
	}

	~priority_queue() {}

	priority_queue& Add(const T& elem) {
		if (this->size_ < this->capacity_) {
			this->elemss_.push_back(elem);
		} else {
			this->elemss_.push_back(elem);
			this->capacity_++;
		}

		if (this->pos_hsh_[*this->ElemByPos(this->size_)].empty()) {
			std::set<size_t> tmp_new;
			tmp_new.insert(this->size_);
			this->pos_hsh_[*this->ElemByPos(this->size_)] = tmp_new;
		} else {
			this->pos_hsh_.at(*this->ElemByPos(this->size_)).insert(this->size_);
		}

		this->SwimUp(this->size_);
		this->size_++;
		this->HshRenew();
		return *this;
	}

	T Peek() {
		if (this->IsEmpty()) {
			return NULL;
		}
		
		return *this->ElemByPos(0);
	}

	T Poll() {
		return this->RemoveAt(0);
	}

	T Remove(const T& elem) {
		std::set<size_t> rem_set = this->pos_hsh_.at(elem);
		if (!rem_set.empty()) {
			return this->RemoveAt(*(--rem_set.end()));
		}
		return NULL;
	}

	T RemoveAt(const size_t pos) {
		if (this->IsEmpty()) {
			return NULL;
		}

		this->size_--;

		T remvd_elem = *this->ElemByPos(pos);
		std::swap(*this->ElemByPos(pos), *this->ElemByPos(this->size_));
		auto erase_iter = this->elemss_.begin();
		std::advance(erase_iter, this->size_);
		this->elemss_.erase(erase_iter);
		this->pos_hsh_[remvd_elem].erase(pos);
		
		if (this->pos_hsh_[remvd_elem].empty()) {
			this->pos_hsh_.erase(remvd_elem);
		}

		if (pos == this->size_) {
			this->HshRenew();
			return remvd_elem;
		}

		T tmp_elem = *this->ElemByPos(pos);
		this->SinkDown(pos);

		if (*this->ElemByPos(pos) == tmp_elem) {
			this->SwimUp(pos);
		}
		this->HshRenew();
		return remvd_elem;
	}

	void Clear() {
		for (size_t ptr = 0; ptr < this->capacity_; ptr++) {
			*this->ElemByPos(ptr) = NULL;
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

	bool Contains(const T& elem) const {
		return this->pos_hsh_.count(elem);
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
			std::cout << elem << ": ";
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
		if (left_ch < this->size_ && !this->LessCmp(node_pos, left_ch)) {
			return false;
		}
		if (right_ch < this->size_ && !this->LessCmp(node_pos, right_ch)) {
			return false;
		}
		return this->isMinHeap(left_ch) && this->isMinHeap(right_ch);
	}
private:
	T* ElemByPos(const size_t pos) {
		auto it = this->elemss_.begin();
		std::advance(it, pos);
		return &(*it);
	}

	void HshRenew() {
		this->pos_hsh_.clear();
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			std::set<size_t> tmp_new = this->pos_hsh_[*this->ElemByPos(ptr)];
			if (tmp_new.empty()) {
				tmp_new.insert(ptr);
				this->pos_hsh_[*this->ElemByPos(ptr)] = tmp_new;
			} else {
				this->pos_hsh_.at(*this->ElemByPos(ptr)).insert(ptr);
			}
		}
	}

	bool LessCmp(const size_t lhs, const size_t rhs) {
		T node_lhs = *this->ElemByPos(lhs);
		T node_rhs = *this->ElemByPos(rhs);
		return node_lhs <= node_rhs;
	}

	void SwimUp(const size_t node_pos) {
		size_t largest_pos = node_pos;
		size_t parrent_left = (largest_pos - 1) / 2;

		while (largest_pos > 0 && this->LessCmp(largest_pos, parrent_left)) {
			std::swap(*this->ElemByPos(parrent_left), *this->ElemByPos(largest_pos));
			largest_pos = parrent_left;
			parrent_left = (largest_pos - 1) / 2;
		}
	}

	void SinkDown(size_t node_pos) {
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
			std::swap(*this->ElemByPos(smallest_pos), *this->ElemByPos(node_pos));
			node_pos = smallest_pos;
		}
	}

	size_t size_ = 0;
	size_t capacity_ = 0;
	std::list<T> elemss_;
	std::map<T, std::set<size_t>> pos_hsh_;
};

