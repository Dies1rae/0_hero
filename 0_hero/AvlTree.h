#pragma once

#include "TreeNode.h"


class AvlTree {
public:
	explicit AvlTree() = default;
	explicit AvlTree(const int value) {
		this->root_ = new TreeNode(value);
		this->size_++;
		base_.push_back(this->root_);
	}
	explicit AvlTree(int&& value) {
		this->root_ = new TreeNode(std::move(value));
		this->size_++;
		base_.push_back(this->root_);
	}
	explicit AvlTree(const TreeNode* head) {
		TreeNode* tmp = new TreeNode(head->val);
		this->InorderTravAdd(tmp);
	}

	~AvlTree() {
		this->root_ = nullptr;
		this->size_ = NULL;
		for (auto& node : this->base_) {
			delete node;
		}
	}

	AvlTree& Add(const int value) {
		TreeNode* new_node = new TreeNode(value);
		TreeNode* ptr = this->root_;
		InorderAdd(ptr, new_node);
		ptr = this->root_;
		InorderTravBaseFill(ptr);
		this->size_++;
		return *this;
	}

	size_t Size() const {
		return this->size_;
	}

	std::vector<TreeNode*> InorderTrav() const {
		return this->base_;
	}

	void Clear() {
		this->size_ = 0;
		this->base_.clear();
		this->root_ == nullptr;
	}

private:
	void InorderAdd(TreeNode* ptr_node, const TreeNode* new_node) {
		if (ptr_node->val <= new_node->val) {
			if (ptr_node->left) {
				InorderAdd(ptr_node->left, new_node);
			} else {
				ptr_node->left =  new TreeNode(new_node->val);
			}
		} else {
			if (ptr_node->right) {
				InorderAdd(ptr_node->right, new_node);
			} else {
				ptr_node->right =  new TreeNode(new_node->val);
			}
		}
	}

	void InorderTravAdd(TreeNode* node, int start = 0) {
		if (node == nullptr) {
			return;
		} else {
			InorderTravAdd(node->left, ++start);
			this->Add(node->val);
			start--;
		}
		InorderTravAdd(node->right);
	}

	void InorderTravBaseFill(TreeNode* node, size_t start = 0) {
		//need to write AVL index checking
		if (node == nullptr) {
			return;
		} else {
			InorderTravBaseFill(node->left, ++start);
			this->base_.push_back(node);
			start--;
		}
		InorderTravBaseFill(node->right);
	}

	void AVLBubling() {
		//rebuilding tree by indexes
	}

	size_t size_ = 0;
	TreeNode* root_ = new TreeNode();
	std::vector<TreeNode*> base_;
};