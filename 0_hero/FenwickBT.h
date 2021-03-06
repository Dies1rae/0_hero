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
		if (size == 0) {
			throw std::range_error("Empty value array");
		}
		this->elems_.reserve(size);
	}

	explicit IndexedTree(const std::vector<NumericType>& other) : elems_(other.size(), 0) {
		if (other.empty()) {
			throw std::range_error("Empty value array");
		}
		
		for (size_t ptr = 0; ptr < this->elems_.size(); ptr++) {
			this->add(ptr, other[ptr]);
		}
	}

	~IndexedTree(){}

	const size_t Size() const noexcept {
		return this->elems_.size();
	}

	const bool IsEmpty() const noexcept {
		return this->elems_.empty();
	}

	NumericType prefixSum(int idx) const {
		int idx_tmp = idx;
		NumericType sum = 0;
		while (idx_tmp >= 0) {
			sum += this->elems_[idx_tmp];
			//idx_tmp = (idx_tmp & (idx_tmp + 1)) - 1;
			idx_tmp = idx_tmp - this->LSB(idx_tmp + 1);
		}
		return sum;
	}

	NumericType distanceSum(const int first, const int last) const {
		if (last < first) {
			throw std::range_error("Wrong slice");
		}
		return this->prefixSum(last) - this->prefixSum(first - 1);
	}

	void add(const size_t idx, const NumericType value) {
		int idx_tmp = idx;
		while (idx_tmp < this->elems_.size()) {
			this->elems_[idx_tmp] += value;
			//idx_tmp = idx_tmp | (idx_tmp + 1);
			idx_tmp = idx_tmp + this->LSB(idx_tmp + 1);
		}
	}

	void set(size_t idx, const NumericType value) {
		NumericType delta = this->distanceSum(idx, idx);
		this->add(idx, delta - value);
	}

	size_t showLSB(const size_t idx) {
		return this->LSB(idx);
	}

	std::vector<NumericType> getArraySummirized() const {
		return this->elems_;
	}

	std::vector<NumericType> getArrayBased() const {
		std::vector<NumericType> res;
		res.resize(this->elems_.size());
		for (size_t ptr = 0; ptr < this->elems_.size(); ptr++) {
			res[ptr] = this->distanceSum(ptr, ptr);
		}
		return res;
	}
private:
	size_t LSB(const int idx) const {
		return idx & (-1 * idx);
	}

	std::vector<NumericType> elems_;
};
 