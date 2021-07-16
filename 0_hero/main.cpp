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
#include <random>

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

int knut_1E1(int A, int B) {
	int ctr = 0;
	while (A > 0 && B > 0) {
		ctr++;
		A = A % B;
		if (A == 0) {
			return ctr;
			//return B;
		}
		B = B % A;
		ctr++;
		if (B == 0) {
			return ctr;
			//return A;
		}
	}
	return 0;
}

int findLHS(vector<int>& nums) {
	map<int, int> hsh;
	int size_max = 0;
	for (const auto& num : nums) {
		hsh[num]++;
	}
	for (const auto& [num, ctr] : hsh) {
		if (hsh.count(num+1) > 0) {
			int tmp_max = ctr + hsh.at(num + 1);
			if (size_max < tmp_max) {
				size_max = tmp_max;
			}
		}
	}
	return size_max;
}

bool isPalindrome(const string& x) {
	int ctr = 0;
	for (size_t btr = 0, ept = x.size() - 1; btr < ept;) {
		if (x[btr] != x[ept]) {
			if(ctr == 0){
				btr++;
				ctr = 1;
				continue;
			} else if (ctr == 1) {
				btr--;
				ept--;
				ctr++;
				continue;
			} else {
				return false;
			}
		}
		btr++;
		ept--;

	}
	return true;
}

bool validPalindrome(string s) {
	return isPalindrome(s);
}

double NormalRandAlgo(const int min, const int max) {
	random_device some_dev; //seed for rnd
	mt19937 rng(some_dev()); //Mersenne-Twister normilized rnd
	uniform_real_distribution<> nrmlzer_min_max(1.0 * min, 1.0 * max); //Gauss normilize
	return nrmlzer_min_max(rng);
}

bool halvesAreAlike(string s) {
	set <char> word_one{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	int ctr_1 = 0;
	int ctr_2 = 0;
	for (size_t ptrb = 0, ptre = s.size() - 1; ptrb < s.size() / 2; ptrb++, ptre--) {
		ctr_1 += word_one.count(s[ptre]);
		ctr_2 += word_one.count(s[ptrb]);
	}
	return ctr_1 == ctr_2;
}


string addStrings(string num1, string num2) {
	string res_str;
	int tmp = 0;

	while (!num1.empty() || !num2.empty()) {
		int num_1 = 0;
		int num_2 = 0;
		if (!num1.empty()) {
			num_1 = num1.back() - 48;
			num1.pop_back();
		}
		if (!num2.empty()) {
			num_2 = num2.back() - 48;
			num2.pop_back();
		}

		tmp += (num_1 + num_2);
		res_str.push_back((tmp % 10) + 48);
		tmp /= 10;
	}
	if (tmp > 0) {
		res_str.push_back((tmp % 10) + 48);
	}
	std::reverse(res_str.begin(), res_str.end());
	return res_str;
}

int firstUniqChar(string s) {
	size_t pos = INT_MAX;
	map<char, int> ctr;
	for (const auto& ch : s) {
		ctr[ch]++;
	}
	for (const auto& [ch, ctr] : ctr) {
		if (ctr == 1) {
			size_t pos_tmp = s.find(ch);
			if (pos > pos_tmp) {
				pos = pos_tmp;
			}
		}
	}
	if (pos == INT_MAX) {
		return -1;
	}
	return pos;
}

vector<vector<int>> groupThePeople(const vector<int>& groupSizes) {
	vector<vector<int>> res;
	unordered_map<size_t, vector<int>> res_hsh;
	for (size_t ptr = 0; ptr < groupSizes.size(); ptr++) {
		if (res_hsh.count(groupSizes[ptr]) == 0) {
			vector<int> tmp;
			tmp.push_back(ptr);
			res_hsh[groupSizes[ptr]] = tmp;
		} else {
			res_hsh[groupSizes[ptr]].push_back(ptr);
		}
	}
	for (const auto& [sz, vctrs] : res_hsh) {
		if (sz >= vctrs.size()) {
			res.push_back(vctrs);
		} else {
			vector<int> tmp;
			for (const auto& elem : vctrs) {
				if (tmp.size() < sz) {
					tmp.push_back(elem);
				} else {
					res.push_back(tmp);
					tmp.clear();
					tmp.push_back(elem);
				}
			}
			if (!tmp.empty()) {
				res.push_back(tmp);
				tmp.clear();
			}
		}
		
	}
	return res;
}

int countConsistentStrings(const string& allowed, const vector<string>& words) {
	int cntr = 0;
	bool ptr = false;
	map<char, int> allow;
	map<char, int> wrdCnt;
	for (const char& ch : allowed) {
		allow[ch]++;
	}
	for (const auto& word : words) {
		for (const char& ch : word) {
			wrdCnt[ch]++;
			if (allow.count(ch) == 0) {
				wrdCnt.clear();
				ptr = false;
				break;
			}
		}
		if (wrdCnt.size() <= allow.size()) {
			for (const auto& [ch, cnt] : wrdCnt) {
				if (cnt >= allow.at(ch)) {
					ptr = true;
				} else {
					ptr = false;
					break;
				}
			}
		} else {
			ptr = false;
		}
		if (ptr) {
			cntr++;
		}
		wrdCnt.clear();
	}
	return cntr;
}

int main() {
	
	return 0;
}

 