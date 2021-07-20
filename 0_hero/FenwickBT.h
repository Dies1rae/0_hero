#pragma once

#include <vector>
#include <type_traits>
#include <stdexcept>
#include <algorithm>

template<
	typename NumericType,
	typename = typename std::enable_if<std::is_arithmetic<NumericType>::value, NumericType>::type
>

class IndexedTree {
public:
	explicit IndexedTree() noexcept = default;
	IndexedTree(const size_t size) {
		this->elems_.reserve(size);
	}
	explicit IndexedTree(const std::vector<NumericType>& other) {
		if (other.empty()) {
			throw std::range_error("Empty value array");
		}
		std::copy(other.begin(), other.end(), this->elems_.begin());
		for (size_t ptr = 1; ptr < this->elems_.size(); ptr++) {
			int nxt_idx = ptr + this->LSB(ptr);
			if (nxt_idx < this->elems_.size()) {
				this->elems_[nxt_idx] += this->elems_[ptr];
			}
		}
	}
	explicit IndexedTree(std::vector<NumericType>&& other) {
		if (other.empty()) {
			throw std::range_error("Empty value array");
		}
		std::swap(other, this->elems_);
		for (size_t ptr = 1; ptr < this->elems_.size(); ptr++) {
			int nxt_idx = ptr + this->LSB(ptr);
			if (nxt_idx < this->elems_.size()) {
				this->elems_[nxt_idx] += this->elems_[ptr];
			}
		}
	}

	~IndexedTree(){}

	const size_t Size() const noexcept {
		return this->elems_.size();
	}

	const bool IsEmpty() const noexcept {
		return this->elems_.empty();
	}

	NumericType prefixSum(int idx) {
		NumericType sum = 0;
		if (idx == -1) {
			return this->elems_[0];
		}
		while (idx > 0) {
			sum += this->elems_[idx];
			idx -= this->LSB(idx);
		}
		return sum;
	}

	NumericType distanceSum(const int first, const int last) {
		if (last < first) {
			throw std::range_error("Wrong slice");
		}
		return this->prefixSum(last) - this->prefixSum(first - 1);
	}

	void add(size_t idx, const NumericType value) {
		while (idx < this->elems_.size()) {
			this->elems_[idx] += value;
			idx = idx | (idx + 1);
		}
	}
	void set(const size_t idx, const NumericType value) {
		NumericType tmp_valon_idx = this->distanceSum(idx, idx - 1);
		this->add(idx, value - tmp_valon_idx);
	}

	size_t showLSB(const size_t idx) {
		return this->LSB(idx);
	}

	std::vector<NumericType> getArraySummirized() const {
		return this->elems_;
	}

	std::vector<NumericType> getArrayBased() {
		std::vector<NumericType> res;
		res.resize(this->elems_.size());
		for (size_t ptr = 0; ptr + 1 < this->elems_.size(); ptr++) {
			res[ptr] = this->distanceSum(ptr, ptr + 1);
		}
		return res;
	}
private:
	size_t LSB(const int idx) {
		return idx & (-1 * idx);
	}

	std::vector<NumericType> elems_;
};
 