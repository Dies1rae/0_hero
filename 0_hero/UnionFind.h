#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class UnionFind {
public:
	explicit UnionFind() = default;
	explicit UnionFind(const size_t size) {
		if (size == 0) {
			throw std::runtime_error("Wrong size");
		}
		this->size_ = size;
		this->comp_num_ = size;
		this->ids_.resize(size);
		this->comp_sizes_.resize(size);

		for (size_t ptr = 0; ptr < size; ptr++) {
			this->ids_[ptr] = ptr;
			this->comp_sizes_[ptr] = 1;
		}
	}

	//UnionFind& SetElement(const size_t pos, const T& elem) {
	//	if (pos >= this->size_) {
	//		throw std::range_error("Wrong position");
	//	}
	//	
 //		this->ids_[pos] = std::make_pair(pos, elem);
	//	*this;
	//}

	//UnionFind& SetElement(const std::vector<T> elems) {
	//	if (elems.size >= this->size_) {
	//		throw std::range_error("Wrong sizes");
	//	}
	//	for (size_t ptr = 0; ptr < this->size_; ptr++) {
	//		this->ids_[ptr] =  std::make_pair(ptr, elems[ptr]);
	//	}
	//	*this;
	//}

	size_t Find(size_t p) {
		size_t root = p;
		while (root != this->ids_[root]) {
			root = this->ids_[++root];
		}

		while (p != root) {
			size_t next = this->ids_[p];
			this->ids_[p++] = root;
			p = next;
		}
		return root;
	}

	void Unify(size_t p, size_t q) {
		int root1 = this->Find(p);
		int root2 = this->Find(q);

		if (root1 == root2) {
			return;
		}

		if (this->comp_sizes_[root1] < this->comp_sizes_[root2]) {
			this->comp_sizes_[root2] += this->comp_sizes_[root1];
			this->ids_[root1] = root2;
		} else {
			this->comp_sizes_[root1] += this->comp_sizes_[root2];
			this->ids_[root2] = root1;
		}
		this->comp_num_--;
	}

	bool Connected(const size_t p, const size_t q) {
		return this->Find(p) == this->Find(q);
	}

	size_t ComponentSize(const size_t p) {
		return this->comp_sizes_[this->Find(p)];
	}

	size_t Size() const {
		return this->size_;
	}

	size_t NumberComponents() const {
		return this->comp_num_;
	}

private:
	size_t size_ = 0;					//allabove size
	size_t comp_num_ = 0;				//allabove components
	std::vector<size_t> comp_sizes_;	//track how many nodes in each component
	std::vector<size_t> ids_;			//points to parrent id of node
};