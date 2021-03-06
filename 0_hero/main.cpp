#include "TreeNode.h"
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"
#include "vector_full_test.h"
#include "vector_simple.h"
#include "SingleLinkedList_full.h"
#include "UnionFind.h"
#include "BST.h"
#include "FenwickBT.h"
#include "toDIgit.h"
#include "log_duration.h"
#include "AvlTree.h"

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
#include <variant>
#include <stdio.h>
#include <windows.h>
#include <cstdlib>
#include <memory>
#include <numeric>

using namespace std;



double getData(const char* buffer, size_t size) {
	int data_len = ((buffer[5] - '0') * 10) + ((buffer[6] - '0'));
	string s;
	string t;
	for (size_t ptr = 7; ptr <  7 + data_len; ptr++) {
		s += buffer[ptr];
	}
	for (size_t ptr = 7 + data_len; ptr <  9 + data_len; ptr++) {
		t += buffer[ptr];
	}
	double x = std::stoul(s, nullptr, 16);
	double z = ((double)std::stoul(t, nullptr, 16)) / 10;
	return x + z;
}

class A {
public:
	A() = default;
	A(const A&) = delete;
	A(const A&&) = delete;
	~A() {};

	int data_ = 50;
};

//bad
bool containsNearbyDuplicate(vector<int>& nums, int k) {
	map<int, vector<int>> hsh;
	for (int ptr = 0; ptr < nums.size(); ptr++) {
		hsh[nums[ptr]].push_back(ptr);
	}
	for (const auto& [num, position] : hsh) {
		if (position.size() > 1) {
			for (int ptr = 0; ptr + 1< position.size(); ptr++) {
				if (std::abs(position[ptr] - position[ptr + 1]) <= k) {
					return true;
				}
			}
		}
	}
	return false;
}

//good
bool containsNearbyDuplicate_1(vector<int>& nums, int k) {
	unordered_map<int, int> m;
	int s = nums.size();
	for(int i = 0; i < s; i++){
		if(m.find(nums[i]) != m.end() && (i - m[nums[i]] <= k))
			return true;
		m[nums[i]] = i;
	}
	return false;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int peakIndexInMountainArray(vector<int>& arr) {
	return  std::find(arr.begin(), arr.end(), *std::max_element(arr.begin(), arr.end())) - arr.begin();
}

int sizeLinkdLIst(ListNode* head) {
	int len = 0;
	while(head != nullptr) {
		head = head->next;
		len += 1;
	}
	return len;
}

int trailingZeroes(int n) {
	if (n > 0) {
		int ctr = 0;
		for (int ptr = 5; n / ptr >= 1; ptr *= 5) {
			ctr += n / ptr;
		}
		return ctr;
	}
	return 0;
}

ListNode* middleNode(ListNode* head) {
	ListNode* tmp = head;
	int len = sizeLinkdLIst(tmp);
	int ptr = 0;
	while (ptr < (len / 2)) {
		head = head->next;
		ptr++;
	}
	return head;
}

//int guessNumber(int n) {
//	if(n == 1) {
//		return n;
//	}
//	int middle = n / 2;
//	int guess_num = 0;
//	while ((guess_num = guess(middle)) != 0) {
//		if (guess_num < 0) {
//			if((middle / 2) > 0) {
//				(middle / 2) % 2 == 0 ? middle -= (middle / 2) :  middle -= (middle / 2) - 1;
//			} else {
//				middle --;
//			}
//		} else if (guess_num > 0) {
//			if((middle / 2) > 0) {
//				(middle / 2) % 2 == 0 ? middle += (middle / 2) :  middle += (middle / 2) + 1;
//			} else {
//				middle ++;
//			}
//		}
//	}
//	return middle;
//}

int findMaxConsecutiveOnes(vector<int>& nums) {
	int max = 0;
	int tmp_max = 0;
	for (const auto& num : nums) {
		if (num == 1) {
			tmp_max++;
		}
		if (num == 0) {
			max < tmp_max ? max = tmp_max : max;
			tmp_max = 0;
		}
	}
	max < tmp_max ? max = tmp_max : max;
	return max;
}

int findGCD(vector<int>& nums) {
	return std::gcd(*std::min_element(nums.begin(), nums.end()),  *std::max_element(nums.begin(), nums.end()));
}

static bool cmpFREQ(pair<int, int>& l, pair<int, int>& r) {
	if (l.second != r.second) {
		return l.second < r.second;
	}
	return l.first > r.first;
}

vector<int> frequencySort(vector<int>& nums) {
	map <int, int> cmprs;
	vector<pair<int, int>> pairs_num_ctr;
	vector<int> res;
	for (const int num : nums) {
		cmprs[num] += 1;
	}
	for (const auto& [nums, ctr] : cmprs) {
		pairs_num_ctr.push_back({nums, ctr});
	}
	std::sort(pairs_num_ctr.begin(), pairs_num_ctr.end(), cmpFREQ);
	for(size_t ptr = 0; ptr < pairs_num_ctr.size(); ptr ++) {
		size_t ctr_tmp = 0;
		while (ctr_tmp < pairs_num_ctr[ptr].second) {
			res.push_back(pairs_num_ctr[ptr].first);
			ctr_tmp++;
		}
	}
	return res;
}

bool strCMP(const string& lhs) {
	set<char> chtrs;
	for (char c : lhs) {
		if (chtrs.count(c)) {
			return false;
		}
		chtrs.insert(c);
	}
	return true;
}

vector<string> graph(vector<string>& arr, int ind) {
	if (ind == arr.size()) {
		return {""};
	}

	vector<string> tmp = graph(arr, ind + 1);

	vector<string> ret(tmp.begin(),	tmp.end());

	for (auto i : tmp) {
		string test = i + arr[ind];
		if (strCMP(test))
			ret.push_back(test);
	}

	return ret;
}

int maxLength(vector<string>& arr) {
	vector<string> tmpstr = graph(arr, 0);
	int max = 0;
	for (const auto& str : tmpstr) {
		max < str.size() ? max = str.size() : max;
	}
	return max;
}


int bitcount(unsigned x) {
	if (x == 0) {
		return 0;
	}
	int b = 1;
	while(x != 0) {
		if (x &= (x - 1)) {
			b++;
		}

	}
	return b;
}

vector<int> countBits(int n) {
	vector<int> res;
	for (unsigned int ptr = 1; ptr <= n; ptr++) {
		res.push_back(bitcount(ptr));
	}
	return res;
}

class MyQueue {
public:
	MyQueue(){}

	void push(const int& x) {
		this->synch(this->root_back, this->root_);
		this->root_.push(x);
	}

	int pop() {
		if(this->empty()) {
			return 0;
		}
		this->synch(this->root_, this->root_back);
		int elem = this->root_back.top();
		this->root_back.pop();
		return elem;
	}

	int peek() {
		if(this->empty()) {
			return 0;
		}
		this->synch(this->root_, this->root_back);
		return this->root_back.top();
	}

	bool empty() {
		this->synch(this->root_, this->root_back);
		return this->root_back.empty();
	}

private:
	void synch(stack<int>& lhs, stack<int>& rhs) {
		while(!lhs.empty()) {
			rhs.push(lhs.top());
			lhs.pop();
		}
	}

	std::stack<int> root_;
	std::stack<int> root_back; 
};

int main() {
	std::stack<int> test;
	test.push(1);
	test.push(2);
	cout << test.top() << ' ';
	test.pop();
	cout << test.top() << ' ';
	return 0;
}
