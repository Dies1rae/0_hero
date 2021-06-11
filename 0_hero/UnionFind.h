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
		this->elemes_.resize(size);

		for (size_t ptr = 0; ptr < size; ptr++) {
			this->ids_[ptr] = ptr;
			this->comp_sizes_[ptr] = 1;
			this->elemes_[ptr] = NULL;
		}
	}

	void SetElement(const size_t pos, const T& elem) {
		if (pos >= this->size_) {
			throw std::range_error("Wrong position");
		}
		elems_ptr_ = pos;
 		this->elemes_[pos] = elem;
	}

	void SetElement(const std::vector<T> elems) {
		if (elems.size() > this->size_) {
			throw std::range_error("Wrong sizes");
		}
		for (size_t ptr = 0; ptr < elems.size(); ptr++) {
			this->elems_ptr_++;
			this->elemes_[this->elems_ptr_] =  elems[ptr];
		}
	}

	std::vector<T> FindElemsUnify(size_t p) {
		if (p >= this->size_) {
			throw std::range_error("Wrong sizes");
		}
		//BAD DESIGN!!!
		std::vector<T> res;
		for (size_t ptr = 0; ptr < this->size_; ptr++) {
			if (this->ids_[ptr] == p) {
				res.push_back(this->elemes_[ptr]);
			} else if ((ptr == p && this->elemes_[p] != NULL)) {
				p = this->ids_[ptr];
				for (size_t ptr1 = 0; ptr1 < this->size_; ptr1++) {
					if (this->ids_[ptr1] == p) {
						res.push_back(this->elemes_[ptr1]);
					}
				}
				break;
			}
		}
		return res;
	}

	void Unify(size_t p, size_t q) {
		int root1 = this->FindPos(p);
		int root2 = this->FindPos(q);

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
		return this->FindPos(p) == this->FindPos(q);
	}

	size_t ComponentSize(const size_t p) {
		return this->comp_sizes_[this->FindPos(p)];
	}

	size_t Size() const {
		return this->size_;
	}

	size_t NumberComponents() const {
		return this->comp_num_;
	}

private:
	size_t FindPos(size_t p) {
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

	size_t elems_ptr_ = 0;									//pointer for add elems
	size_t size_ = 0;										//allabove size
	size_t comp_num_ = 0;									//allabove components
	std::vector<size_t> comp_sizes_;						//track how many nodes in each component
	std::vector<size_t> ids_;								//points to parrent id of node
	std::vector<T> elemes_;									//elements of tree  -- BAD DESIGN
};