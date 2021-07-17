#pragma once

#include <vector>
#include <type_traits>

template<
	typename NumericType,
	typename = typename std::enable_if<std::is_arithmetic<NumericType>::value, NumericType>::type
>
class IndexedTree {
public:
	explicit IndexedTree() noexcept = default;
	~IndexedTree(){}

	const size_t Size() const noexcept {
		return this->elems_.size();
	}

	const bool IsEmpty() const noexcept {
		return this->elems_.empty();
	}


private:
	std::vector<NumericType> elems_;
};
 