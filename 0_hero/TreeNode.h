#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <numeric>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <random>
#include <stack>
#include <iterator>
#include <memory>

struct TreeNode {
	TreeNode() = default;
	TreeNode(int data) :val(data) {
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
	};
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

	int val = 0;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

void print_tree(TreeNode* node, int start = 0) {
	if (node == nullptr) {
		return;
	}
	else {
		print_tree(node->left, ++start);
		for (int ptr = 0; ptr < start; ptr++) {
			std::cout << '|';
		}
		std::cout << node->val << std::endl;
		start--;
	}
	print_tree(node->right, ++start);
}

//BAD DESIGN
int rangeSumBST(TreeNode* root, int low, int high) {
	if (root == nullptr) {
		return 0;
	}

	int summ = root->val;
	if (summ < low) {
		return rangeSumBST(root->right, low, high);
	} else if (summ >= low && summ <= high) {
		return summ + rangeSumBST(root->right, low, high) + rangeSumBST(root->left, low, high);
	} else {
		return rangeSumBST(root->left, low, high);
	}
}
//!!!!!!!!!!!!!
//GOOD DESIGN
int rangeSumBST_1(TreeNode* root, int low, int high) {
	int ans = 0;
	if (!root) return ans;
	if (root->val <= high && root->val >= low) {
		ans += root->val;
	}
	ans += rangeSumBST(root->left, low, high);
	ans += rangeSumBST(root->right, low, high);
	root->left = nullptr;
	root->right = nullptr;
	return ans;
}
//!!!!!!!!!!!!!

int height_subtree(TreeNode* node) {
	if (node == NULL) {
		return 0;
	}
	return 1 + std::max(height_subtree(node->left), height_subtree(node->right));
}

bool isBalanced(TreeNode* root) {
	if (root == nullptr) {
		return true;
	}
	int l_val = height_subtree(root->left);
	int r_val = height_subtree(root->right);
	if (std::abs(l_val - r_val) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
		return true;
	}
	return false;
}

void print_inorderBST(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	std::cout << root->val << " ";
	print_inorderBST(root->right);
}

TreeNode* prevN = nullptr;
TreeNode* headN = nullptr;

void recurs_incrBST(TreeNode* root) {
	if (root == nullptr) {
		return;
	}
	recurs_incrBST(root->left);
	TreeNode* rhs = root->right;
	TreeNode* lhs = root->left;
	if (headN == nullptr) {
		headN = root;
		root->left = nullptr;
		prevN = root;
	}
	else {
		prevN->right = root;
		root->left = nullptr;
		prevN = root;
	}
	recurs_incrBST(rhs);
}

TreeNode* increasingBST(TreeNode* root) {
	recurs_incrBST(root);
	return headN;
}

TreeNode* increasingBST_1(TreeNode* root) {
	if (root == nullptr) {
		return nullptr;
	}
	//STACK LIKE A HASH (filo)
	std::stack<TreeNode*> hsh;
	//RETURNED LIST
	TreeNode* head_ = nullptr;
	//CURRENT POSITION
	TreeNode* curr_ = nullptr;
	//TMP POSITION
	TreeNode* tmp_ = root;

	//GET ALL LEFT IN A HASH
	while (tmp_ != nullptr) {
		hsh.push(tmp_);
		tmp_ = tmp_->left;
	}

	//WHILE STACK NOT EMPTY
	while (!hsh.empty()) {
		//GET LAST NODE 
		TreeNode* tmp2_ = hsh.top();
		hsh.pop();

		//IF RETURN LIST == 0
		if (head_ == nullptr) {
			//GET NEW NODE(COPY BASICALLY ION RETURN ROOT)
			head_ = new TreeNode(tmp2_->val);
			//CURRENT POS IN RETURN TO HEAD
			curr_ = head_;
		} else {
			//PLASE NEXT TO THE RIGHT OF THE HEAD_ ROOT
			curr_->right = new TreeNode(tmp2_->val);
			//REPLACE CURRENT POSITION
			curr_ = curr_->right;
		}
		//IF WE GOT SOMETHING IN  RIGHT
		if (tmp2_->right != nullptr) {
			//PUSH IT TO HASH FIRST
			hsh.push(tmp2_->right);
			//AND ITERATE TO RIGHT
			tmp2_ = tmp2_->right;
			//AND WHILE LEFT IS HEAR PUSH IT TO HEAD
			while (tmp2_->left != nullptr) {
				hsh.push(tmp2_->left);
				tmp2_ = tmp2_->left;
			}
		}
	}
	return head_;
}

TreeNode* searchBST(TreeNode* root, int val) {
	if (root == nullptr) {
		return nullptr;
	}
	TreeNode* quoe = root;
	while (quoe) {
		if (quoe->val > val) {
			if (!quoe->left) {
				return nullptr;
			}
			quoe = quoe->left;
		}
		if (quoe->val < val) {
			if (!quoe->right) {
				return nullptr;
			}
			quoe = quoe->right;
		}
		if (quoe->val == val) {
			return quoe;
		}
	}
	return nullptr;
}

TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
	if (!root1) {
		return root2;
	}
	if (!root2) {
		return root1;
	}

	root1->val += root2->val;
	root1->left = mergeTrees(root1->left, root2->left);
	root1->right = mergeTrees(root1->right, root2->right);

	return root1;
}

void inorder_trav(TreeNode* node, std::vector<int>& hsh, int start = 0) {
	if (node == nullptr) {
		return;
	} else {
		inorder_trav(node->left, hsh, ++start);
		hsh.push_back(node->val);
		start--;
	}
	inorder_trav(node->right, hsh);
}

int getMinimumDifference(TreeNode* root) {
	std::vector<int> root_values;
	inorder_trav(root, root_values);
	int min = INT_MAX;
	for (size_t ptr = 0; ptr + 1 < root_values.size(); ptr++) {
		int tmp_min = root_values[ptr + 1] - root_values[ptr];
		if (min > tmp_min) {
			min = tmp_min;
		}
	}
	return min;
}