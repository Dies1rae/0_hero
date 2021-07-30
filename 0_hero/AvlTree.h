#pragma once

#include <algorithm>
#include <stack>
#include <vector>
#include <queue>

template <typename T>
class AvlTree {
public:
	enum class OrderTraversal {
		preOrderTraversal
		, inOrderTraversal
		, postOrderTraversal
		, levelOrderTraversal
	};

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

	bool Remove(const T& elem) {
		if (this->Contains(elem)) {
			this->root_ = this->Remove(this->root_, elem);
			this->node_count_--;
			return true;
		}
		return false;
	}

	bool bstInvariant() {
		TreeNode* node = this->root_;
		if (node == nullptr) {
			return true;
		}
		T val = node->val;
		bool isValid = true;
		if (node->left != nullptr) {
			isValid = isValid && (node->left->val - val < 0);
		}
		if (node->right != nullptr) {
			isValid = isValid && (node->right->val - val > 0);
		}
		return isValid && this->bstInvariant(node->left) && this->bstInvariant(node->right);
	}

	std::vector<T> travers(const OrderTraversal& order) {
		switch (order) {
		case OrderTraversal::preOrderTraversal:
			this->preOrderTraversal();
			return this->traversals_;
			break;
		case OrderTraversal::inOrderTraversal:
			this->inOrderTraversal();
			return this->traversals_;
			break;
		case OrderTraversal::postOrderTraversal:
			this->postOrderTraversal();
			return this->traversals_;
			break;
		case OrderTraversal::levelOrderTraversal:
			this->levelOrderTraversal();
			return this->traversals_;
			break;
		default:
			return this->traversals_;
			break;
		}
		return this->traversals_;
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

		node->height = 1 + std::max(left_node_h, right_node_h);
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
		TreeNode* tmp_node = node->right;
		node->right = tmp_node->left;
		tmp_node->left = node;
		this->update(node);
		this->update(tmp_node);
		return tmp_node;
	}
	TreeNode* rightRotation(TreeNode* node) {
		TreeNode* tmp_node = node->left;
		node->left = tmp_node->right;
		tmp_node->right = node;
		this->update(node);
		this->update(tmp_node);
		return tmp_node;
	}

	TreeNode* Remove(TreeNode* node, const T& elem) {
		if (!node) {
			return nullptr;
		}
		int compliance = elem - node->val;
		if (compliance < 0) {
			node->left = this->Remove(node->left, elem);
		} else if (compliance > 0) {
			node->right = this->Remove(node->right, elem);
		} else {
			if (node->left == nullptr) {
				return node->right;
			} else if (node->right == nullptr) {
				return node->left;
			} else { 
				if (node->left->height > node->right->height) {
					T scs_value = this->findMax(node->left);
					node->val = scs_value;
					node->left = this->Remove(node->left, scs_value);
				} else {
					T scs_value = this->findMax(node->right);
					node->val = scs_value;
					node->right = this->Remove(node->right, scs_value);
				}
			}
		}
		this->update(node);
		return this->balance(node);
	}

	T findMin(TreeNode* node) const {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node->val;
	}

	T findMax(TreeNode* node) const {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node->val;
	}

	void inOrderTraversal() {
		if (this->root_ == nullptr) {
			return;
		}
		this->traversals_.clear();

		TreeNode* trav = this->root_;
		std::stack<TreeNode*> hsh;

		while (trav != nullptr || !hsh.empty()) {
			while (trav != nullptr) {
				hsh.push(trav);
				trav = trav->left;
			}
			TreeNode* node = hsh.top();
			hsh.pop();
			this->traversals_.push_back(node->val);
			trav = node->right;
		}
	}

	void preOrderTraversal() {
		if (this->root_ == nullptr) {
			return;
		}
		this->traversals_.clear();

		TreeNode* trav = this->root_;
		std::stack<TreeNode*> hsh;
		hsh.push(trav);

		while (!hsh.empty()) {
			TreeNode* node = hsh.top();
			hsh.pop();
			this->traversals_.push_back(node->val);

			if (node->right != nullptr) {
				hsh.push(node->right);
			}

			if (node->left != nullptr) {
				hsh.push(node->left);
			}
		}
	}

	void postOrderTraversal() {
		if (this->root_ == nullptr) {
			return;
		}
		this->traversals_.clear();

		TreeNode* trav = this->root_;
		std::stack<TreeNode*> hsh;
		hsh.push(trav);

		while (!hsh.empty()) {
			TreeNode* node = hsh.top();
			hsh.pop();
			this->traversals_.push_back(node->val);

			if (node->left != nullptr) {
				hsh.push(node->left);
			}
			if (node->right != nullptr) {
				hsh.push(node->right);
			}
		}
		std::reverse(this->traversals_.begin(), this->traversals_.end());
	}

	void levelOrderTraversal() {
		if (this->root_ == nullptr) {
			return;
		}
		this->traversals_.clear();

		TreeNode* trav = this->root_;
		std::queue<TreeNode*> hsh;
		hsh.push(trav);

		while (!hsh.empty()) {
			TreeNode* node = hsh.front();
			hsh.pop();
			this->traversals_.push_back(node->val);

			if (node->left != nullptr) {
				hsh.push(node->left);
			}
			if (node->right != nullptr) {
				hsh.push(node->right);
			}
		}
	}

	bool bstInvariant(TreeNode* node) {
		if (node == nullptr) {
			return true;
		}
		T val = node->val;
		bool isValid = true;
		if (node->left != nullptr) {
			isValid = isValid && (node->left->val - val < 0);
		}
		if (node->right != nullptr) {
			isValid = isValid && (node->right->val - val > 0);
		}
		return isValid && this->bstInvariant(node->left) && this->bstInvariant(node->right);
	}

	size_t node_count_ = 0;
	TreeNode* root_ = nullptr;
	std::vector<T> traversals_;
};