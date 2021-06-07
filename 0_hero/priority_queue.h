#pragma once

#include <vector>
#include <map>
#include <set>
#include <stdexcept>
#include <algorithm>
#include <iostream>

template <typename T>
class priority_queue {
public:
	explicit priority_queue() = default;

	explicit priority_queue(const size_t capacity) {
		this->elemss_.resize(capacity);
		this->capacity_ = capacity;
		this->size_ = 0;
	}

	template <typename TCont>
	explicit priority_queue(const TCont& elems) {
		this->elemss_.resize(elems.size());
		this->capacity_ = elems.size();
		this->size_ = 0;

		for (size_t ptr = 0; ptr < this->capacity_; ptr++) {
			this->Add(elems[ptr]);
		}
	}

	~priority_queue() {}

	void Add(const T& elem) {
		if(this->size_ == this->capacity_) {
			this->capacity_ = 2*this->capacity_;
			this->elemss_.resize(this->capacity_);
		}

		this->size_++;
		this->elemss_[this->size_ - 1] = elem;

		this->SwimUp(this->size_ - 1);
		
		this->HshRenew();
	}

	T Peek() {
		if (this->IsEmpty()) {
			return NULL;
		}
		
		return this->elemss_[0];
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

		T remvd_elem = this->elemss_[pos];
		std::swap(this->elemss_[pos], this->elemss_[this->size_]);
		this->elemss_.erase(this->elemss_.begin() + this->size_);
		this->pos_hsh_[remvd_elem].erase(pos);
		
		if (this->pos_hsh_[remvd_elem].empty()) {
			this->pos_hsh_.erase(remvd_elem);
		}

		if (pos == this->size_) {
			this->HshRenew();
			return remvd_elem;
		}

		T tmp_elem = this->elemss_[pos];
		this->SinkDown(pos);

		if (this->elemss_[pos] == tmp_elem) {
			this->SwimUp(pos);
		}
		this->HshRenew();
		return remvd_elem;
	}

	void Clear() {
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			this->elemss_[ptr] = NULL;
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
		for (const auto& elem : this->elemss_) {
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

	void PrintHeap() {
		size_t power = 0;
		size_t value = 1;
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			if (ptr == value) {
				std::cout << '\n';
				power += 1;
				value += (1 << power);
			}
			std::cout << this->elemss_[ptr] << "  ";
		}
		std::cout << '\n';
	}
private:
	size_t Parrent(const size_t pos) {
		return (pos - 1) / 2;
	}

	size_t left_ch(const size_t pos) {
		return 2 * pos + 1;
	}

	size_t right_ch(const size_t pos) {
		return 2 * pos + 2;
	}

	void HshRenew() {
		this->pos_hsh_.clear();
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			std::set<size_t> tmp_new = this->pos_hsh_[this->elemss_[ptr]];
			if (tmp_new.empty()) {
				tmp_new.insert(ptr);
				this->pos_hsh_[this->elemss_[ptr]] = tmp_new;
			} else {
				this->pos_hsh_.at(this->elemss_[ptr]).insert(ptr);
			}
		}
	}

	bool LessCmp(const size_t lhs, const size_t rhs) {
		return this->elemss_[lhs] <= this->elemss_[rhs];
	}

	void SwimUp(size_t node_pos) {
		size_t parrent_left = this->Parrent(node_pos);

		while (node_pos > 0 && this->LessCmp(node_pos, parrent_left)) {
			std::swap(this->elemss_[parrent_left], this->elemss_[node_pos]);
			node_pos = parrent_left;
			parrent_left = this->Parrent(node_pos);
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
			std::swap(this->elemss_[smallest_pos], this->elemss_[node_pos]);
			node_pos = smallest_pos;
		}
	}

	void Heapify(size_t n, size_t node) {
		size_t largest = node;
		size_t lhs = this->left_ch(node);
		size_t rhs = this->right_ch(node);

		if (lhs < n && this->elemss_[lhs] < this->elemss_[largest]) {
			largest = lhs;
		}

		if (rhs < n && this->elemss_[rhs] < this->elemss_[largest]) {
			largest = rhs;
		}

		if (largest != node) {
			std::swap(this->elemss_[node], this->elemss_[largest]);
			this->Heapify(n, largest);
		}
	}

	void HeapSort() {
		for (int ptr = (this->size_ / 2) - 1; ptr >= 0; ptr--) {
			this->Heapify(this->size_, ptr);
		}

		for (int ptr = this->size_ - 1; ptr >= 0; ptr--) {
			std::swap(this->elemss_[0], this->elemss_[ptr]);
			this->Heapify(ptr, 0);
		}
	}


	size_t size_ = 0;
	size_t capacity_ = 0;
	std::vector <T> elemss_;
	std::map <T, std::set<size_t>> pos_hsh_;
};

