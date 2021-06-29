#include "TreeNode.h"
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"
#include "vector_full_test.h"
#include "vector_simple.h"
#include "SingleLinkedList_full.h"
#include "UnionFind.h"
#include "BST.h"

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
#include <cassert>
#include <exception>
#include <time.h>
#include <ctime>
#include <sstream>
#include <queue>

using namespace std;

int recBT(TreeNode* root, int& res) {
	if (root == nullptr) {
		return 0;
	}
	int left = recBT(root->left, res);
	int right = recBT(root->right, res);
	res = max(res, 1 + left + right);
	return 1 + max(left, right);
}

int diameterOfBinaryTree(TreeNode* root) {
	int res = 1;
	recBT(root, res);
	return res - 1;
}

int longestOnes(vector<int>& nums, int k) {
	int max_ctr = 0;
	int curr_ctr = 0;
	size_t start_pos = 0;
	size_t end_pos = 0;
	while (end_pos < nums.size()) {
		if (nums[end_pos] == 1) {
			curr_ctr++;
			end_pos++;
		} else if (nums[end_pos] == 0 && k > 0) {
			k--;
			curr_ctr++;
			end_pos++;
		} else {
			if (max_ctr < curr_ctr) {
				max_ctr = curr_ctr;
			}
			while (nums[start_pos] == 1) {
				start_pos++;
			}
			start_pos++;
			end_pos++;
			curr_ctr = end_pos - start_pos;
		}
	}
	return max(max_ctr, curr_ctr);
}

int thirdMax(vector<int>& nums) {
	if (nums.size() < 3) {
		return *max_element(nums.begin(), nums.end());
	}
	sort(nums.rbegin(), nums.rend());
	int ctr = 2;
	int thr_max = 0;
	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		if (nums[ptr] > nums[ptr + 1]) {
			ctr--;
		}
		if (ctr == 0) {
			return nums[ptr + 1];
		}
	}

	return *(nums.begin());
}

class ParkingSystem {
public:
	ParkingSystem(int big, int medium, int small) : big_(big), mid_(medium), sml_(small) {}

	bool addCar(int carType) {
		switch (carType) {
		case 1:
			if (this->big_ > 0) {
				this->big_--;
				return true;
			} else {
				return false;
			}
			break;
		case 2:
			if (this->mid_ > 0) {
				this->mid_--;
				return true;
			} else {
				return false;
			}
			break;
		case 3:
			if (this->sml_ > 0) {
				this->sml_--;
				return true;
			} else {
				return false;
			}
			break;
		default:
			return false;
			break;
		}
		return false;
	}

private:
	int big_ = 0;
	int mid_ = 0;
	int sml_ = 0;
};

int countPrimes(int n) {
	if (n < 2) {
		return 0;
	}
	if (n == 3) {
		return 1;
	}

	int ctr = n;
	vector<bool> res(n, true);
	
	for (size_t ptr = 2; pow(ptr, 2) < n; ptr++) {
		if (!res[ptr]) {
			continue;
		}
		for (int j = pow(ptr, 2); j < n; j += ptr) {
			res[j] = false;
		}
	}
	for (size_t ptr = 2; ptr < n; ptr++) {
		if (res[ptr]) ctr++;
	}
	return ctr;
}

int main() {
	cout << countPrimes(10) << endl;

	return 0;
}

