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

int guessNumber(int n) {
	if(n == 1) {
		return n;
	}
	int middle = n / 2;
	int guess_num = 0;
	while ((guess_num = guess(middle)) != 0) {
		if (guess_num < 0) {
			if((middle / 2) > 0) {
				(middle / 2) % 2 == 0 ? middle -= (middle / 2) :  middle -= (middle / 2) - 1;
			} else {
				middle --;
			}
		} else if (guess_num > 0) {
			if((middle / 2) > 0) {
				(middle / 2) % 2 == 0 ? middle += (middle / 2) :  middle += (middle / 2) + 1;
			} else {
				middle ++;
			}
		}
	}
	return middle;
}

int main() {
	cout << 6 / 2;

	return 0;
}
