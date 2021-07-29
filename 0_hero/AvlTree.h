#pragma once

#include <algorithm>
#include <stack>
#include <vector>
#include <queue>

template <typename T>
class AvlTree {
public:
	explicit AvlTree() = default;

	explicit AvlTree(T value) : node_count_(1), root_(new TreeNode(value)) {}

	int height() const {
		if (this->root_ == nullptr) {
			return 0;
		}
		return this->root_->height;
	}

	size_t Size() const {
		return this->node_count_;
	}

	bool IsEmpty() const {
		return this->Size() == 0;
	}

	bool Contains(const T& elem) {
		return this->Contains(this->root_, elem);
	}

	bool Add(const T& elem) {
		if (this->Contains(elem) || elem == NULL) {
			return false;
		}

		this->root_ = this->Add(this->root_, elem);
		this->node_count_++;
		return true;
	}

private:
	struct TreeNode {
		TreeNode() = default;
		TreeNode(T data) : val(data) {
			TreeNode* left = nullptr;
			TreeNode* right = nullptr;
		};
		TreeNode(T x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

		int balanced_factor = 0;
		int height = 0;
		T val = NULL;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
	};

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

	TreeNode* Add(TreeNode* node, const T& elem) {
		if (node == nullptr) {
			node = new TreeNode(elem);
		} else {
			if (elem < node->val) {
				node->left = this->Add(node->left, elem);
			} else {
				node->right = this->Add(node->right, elem);
			}
		}

		this->update(node);
		return node; //NEED TO DO AND RETURN BALANCED NODE(balance for all tree)
	}

	void update(TreeNode* node) {
		int left_node_h = 0;
		int right_node_h = 0;
		node->left == nullptr ? left_node_h = -1 : left_node_h = node->left->height;
		node->right == nullptr ? right_node_h = -1 : right_node_h = node->right->height;

		node->height = 1 + std::max_element(left_node_h, right_node_h);
		node->balanced_factor = right_node_h - left_node_h;
	}
	
	void balance(TreeNode* node) {
		if (node->balanced_factor == -2) {
			if (node->left->balanced_factor <= 0) {
				return this->leftLeftCase(node);
			} else {
				return this->leftRightCase(node);
			}
		} else if (node->balanced_factor == 2) {
			if (node->right->balanced_factor >= 0) {
				return this->rightRightCase(node);
			} else {
				return this->rightLeftCase(node);
			}
		}
	}

	TreeNode* leftLeftCase(TreeNode* node) {
		return this->rightRotation(node);
	}
	TreeNode* leftRightCase(TreeNode* node) {
		node->left = this->leftRotation(node->left);
		return this->leftLeftCase(node);
	}
	TreeNode* rightRightCase(TreeNode* node) {
		return this->leftRotation(node);
	}
	TreeNode* rightLeftCase(TreeNode* node) {
		node->right = this->rightRotation(node->right);
		return this->rightRightCase(node);
	}

	TreeNode* leftRotation(TreeNode* node) {
		//need to do
	}
	TreeNode* rightRotation(TreeNode* node) {
		//need to do
	}

	size_t node_count_ = 0;
	TreeNode* root_ = nullptr;
	std::vector<T> traversals_;
};