#pragma once

#include <algorithm>

template <typename T>
class BinarySearchTree {
public:
	explicit BinarySearchTree() = default;
	explicit BinarySearchTree(const T& elem) : node_count_(1), root_(new TreeNode(elem)) {}

	size_t Size() const {
		return this->node_count_;
	}

	bool IsEmpty() const {
		return this->Size() == 0;
	}

	bool Add(const T& elem) {
		if (this->Contains(elem)) {
			return false;
		}

		this->root_ = this->Add(this->root_, elem);
		this->node_count_++;
		return true;
	}

	bool Contains(const T& elem) {
		return this->Contains(this->root_, elem);
	}

	bool Remove(const T& elem) {
		if (this->Contains(elem)) {
			this->root_ = this->Remove(this->root_, elem);
			this->node_count_--;
			return true;
		}
		return false;
	}

	size_t Height() {
		return this->Height(this->root_);
	}
private:
	struct TreeNode {
		TreeNode() = default;
		TreeNode(T data) : val(data) {
			TreeNode* left = nullptr;
			TreeNode* right = nullptr;
		};
		TreeNode(T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

		T val = NULL;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
	};

	TreeNode * Add(TreeNode * node, const T& elem) {
		if (node == nullptr) {
			node = new TreeNode(elem);
		} else {
			if (elem < node->val) {
				node->left = this->Add(node->left, elem);
			} else {
				node->right = this->Add(node->right, elem);
			}
		}

		return node;
	}

	TreeNode * Remove(TreeNode * node, const T& elem) {
		if (!node) {
			return nullptr;
		}
		int compliance = elem - node->val;
		if (compliance < 0) {
			node->left = this->Remove(node->left, elem);
		} else if (compliance > 0) {
			node->right = this->Remove(node->right, elem);
		} else {
			if (node->left == nullptr) { //first var
				TreeNode * rgt_tmp = node->right;
				node->val = NULL;
				node = nullptr;
				return rgt_tmp;
			} else if(node->right == nullptr) { //second var
				TreeNode * lft_tmp = node->left;
				node->val = NULL;
				node = nullptr;
				return lft_tmp;
			} else { //third var
				TreeNode* tmp = this->MaxLeft(node->right);
				node->val = tmp->val;
				node->right = this->Remove(node->right, tmp->val);
			}
		}
		return node;
	}

	TreeNode * MaxLeft(TreeNode* node) {
		TreeNode* curr = node;
		while (curr->left) {
			curr = curr->left;
		}
		return curr;
	}

	TreeNode * MaxRight(TreeNode* node) {
		TreeNode* curr = node;
		while (curr->right) {
			curr = curr->right;
		}
		return curr;
	}

	bool Contains(TreeNode* node, const T& elem) {
		if (node == nullptr) {
			return false;
		}
		int compliance = elem - node->val;
		if (compliance < 0) {
			this->Contains(node->left, elem);
		} else if (compliance > 0) {
			this->Contains(node->right, elem);
		} else {
			return true;
		}
	}

	size_t Height(TreeNode * node) {
		if (!node) {
			return 0;
		}
		return std::max(this->Height(node->left), this->Height(node->right)) + 1;
	}

	size_t node_count_ = 0;
	TreeNode * root_ = nullptr;
};