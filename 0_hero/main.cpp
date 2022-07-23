#include "TreeNode.h"
//#include "queue.h"
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
#include "polish_not.h"

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
#include <queue>

using namespace std;
using namespace pclc;


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


int longestPalindrome(string s) {
	int res = 0;
	int max = 0;
	map<char, int> hsh;
	for (const char ch : s) {
		hsh[ch]++;
	}

	for (const auto& [ch, ctr] : hsh) {
		if (ctr % 2 == 0) {
			res += ctr;
		} else if (ctr % 2 != 0){
			if (max < ctr) {
				if (max > 0) {
					res -= 1;
				}
				res += ctr;
				max = ctr;
			} else {
				res += ctr - 1;
			}
		}
	}

	return res;
}

bool canBeEqual(vector<int>& target, vector<int>& arr) {
	map<int, int> hsh;
	for (const int num : target) {
		hsh[num] ++;
	}
	for (const int num : arr) {
		if (hsh.count(num) == 0) {
			return false;
		} else {
			hsh.at(num)--;
		}
	}
	for (const auto& [num, ctr] : hsh) {
		if (ctr != 0) {
			return false;
		}
	}
	return true;
}

string sortString(string s) {
	string res;
	map<char, int> hsh;
	for(const char ch : s) {
		hsh[ch]++;
	}
	while (res.size() != s.size()) {
		for (auto ptr = hsh.begin(); ptr != hsh.end(); ptr++) {
			if (ptr->second > 0) {
				res += ptr->first;
				ptr->second--;
			}
		}
		for (auto ptr = hsh.rbegin(); ptr != hsh.rend(); ptr++) {
			if (ptr->second > 0) {
				res += ptr->first;
				ptr->second--;
			}
		}
	}
	return res;
}

vector<ListNode*> splitListToParts(ListNode* head, int k) {
	int res_ctr = 0;
	int len =  sizeLinkdLIst(head);
	int big_parts_ctr = 0;
	int new_len = 1;
	if(k <= len) {
		big_parts_ctr = len % k;
		new_len = len / k;
	}

	cout << len << ' ' << new_len << ' ' << big_parts_ctr << endl;

	vector<ListNode*> res;
	res.resize(k);
	while (big_parts_ctr != 0 && head != nullptr) {
		int ctr = new_len + 1;
		ListNode* tmp = new ListNode();
		res[res_ctr] = tmp;
		res_ctr++;
		while (ctr != 0 && head != nullptr) {
			tmp->val = head->val;
			head = head->next;
			ctr--;
			if (ctr != 0 && head != nullptr) {
				tmp->next = new ListNode();
				tmp = tmp->next;
			}
		}
		big_parts_ctr--;
	}

	while (head != nullptr) {
		int ctr = new_len;
		ListNode* tmp = new ListNode();
		res[res_ctr] = tmp;
		res_ctr++;
		while (ctr != 0 && head != nullptr) {
			tmp->val = head->val;
			head = head->next;
			ctr--;
			if (ctr != 0 && head != nullptr) {
				tmp->next = new ListNode();
				tmp = tmp->next;
			}
		}
	}
	if (res.size() < k - 1) {
		ListNode* tmp = nullptr;
		res[res_ctr] = tmp;
		res_ctr++;
	}
	return res;
}

bool hasCycle(ListNode *head) {
	map<ListNode *, int> hsh;
	while (head) {
		if (hsh.count(head) >= 1) {
			return true;
		} else {
			hsh[head]++;
			head = head->next;
		}
	}
	return false;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	set<ListNode *> hsh;
	while (headA) {
		hsh.insert(headA);
		headA = headA->next;
	}
	while (headB) {
		if (hsh.count(headB)) {
			return headB;
		}
		headB = headB->next;
	}
	return nullptr;
}

int titleToNumber(string columnTitle) {
	unsigned long res = 0;
	while (!columnTitle.empty()) {
		res = (res * 26) + (columnTitle[0] - 64);    
		columnTitle = columnTitle.substr(1);
	}
	return res;
}

string freqAlphabets(string s) {
	string res;
	for (int ptr = s.size() - 1; ptr >= 0; ptr--) {
		if (s[ptr] == '#') {
			string tmp;
			tmp += s[ptr - 2];
			tmp += s[ptr - 1];
			res += (std::stoi(tmp) + 96);
			ptr -= 2;
		} else {
			res += (s[ptr] - 48) + 96;
		}
	}
	std::reverse(res.begin(), res.end());
	return res;
}


string destCity(vector<vector<string>>& paths) {
	map<string, std::vector<string>> hsh;
	for (const auto& cities : paths) {
		hsh[cities[0]].push_back(cities[1]);
	}
	for (const auto& [cityIN, citiesOUT] : hsh) {
		for (const auto& city : citiesOUT) {
			if (hsh.count(city) == 0) {
				return city;
			}
		}
	}
	return {};
}

vector<int> finalPrices(vector<int>& prices) {
	vector<int> res;

	for (size_t ptr = 0; ptr < prices.size(); ptr++) {
		bool in = false;
		for (size_t j = ptr + 1; j < prices.size(); j++) {
			if (prices[j] <= prices[ptr]) {
				in = true;
				res.push_back((prices[ptr] - prices[j]));
				break;
			}
		}
		if (!in) {
			res.push_back(prices[ptr]);
		}
	}

	return res;
}

int search(vector<int>& nums, int target) {
	if(nums.size() == 1) {
		return nums[0] == target ? 0 : -1;
	}
	long long int middle = 0;
	long long int start = 0;
	long long int end = nums.size();
	while (start <= end) {
		middle = start + ((end - start) / 2);
		if(nums[middle] == target) {
			return middle;
		} else if (nums[middle] < target) {
			start = middle + 1;
		} else {
			end = middle - 1;
		}
	}
	return -1;
}

int firstBadVersion(int n) {
	int left = 1, right = n;
	int mid = (left + (right - left) / 2);
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		//return isBadVersion(n) ? n : 0;
	}
	while (left < right) {
		//isBadVersion(mid) ? right = mid - 1 : left = mid + 1;
		mid = (left + (right - left) / 2);
	}
	//return isBadVersion(left) ? left : left + 1;
}

//bad
int searchInsert(vector<int>& nums, int target) {
	set<int> res;   
	for(const auto& a : nums) {
		res.insert(a);
		if(res.count(target)) {
			auto it = res.find(target);
			return std::distance(res.begin(), it);
		}
	}
	res.insert(target);
	auto it = res.find(target);
	return std::distance(res.begin(), it);
}

////good
//int searchInsert(vector<int>& nums, int target) {
//	return (std::lower_bound(nums.begin(), nums.end(), target)) - nums.begin();
//}


vector<int> sortedSquares(vector<int>& nums) {
	vector<int> res;
	res.resize(nums.size());
	int ptrMinus = std::distance(nums.begin(), std::lower_bound(nums.begin(), nums.end(), 0)) - 1;
	int ptrPlus = ptrMinus  + 1;
	int ptrRes = 0;
	while (ptrMinus >= 0 && ptrPlus < res.size()) {
		int elemM = nums[ptrMinus] * nums[ptrMinus];
		int elemP = nums[ptrPlus] * nums[ptrPlus];
		if (elemM < elemP) {
			res[ptrRes] = elemM;
			ptrMinus--;
		} else {
			res[ptrRes] = elemP;
			ptrPlus++;
		}
		ptrRes++;
	}

	while (ptrMinus >= 0) {
		res[ptrRes] = nums[ptrMinus] * nums[ptrMinus];
		ptrMinus--;
		ptrRes++;
	}

	while (ptrPlus < res.size()) {
		res[ptrRes] = nums[ptrPlus] * nums[ptrPlus];
		ptrPlus++;
		ptrRes++;
	}

	return res;
}

void rotate(vector<int>& nums, int k) {
	while (k) {
		int tmpl = *(nums.rbegin());
		nums.pop_back();
		nums.insert(nums.begin(), tmpl);
		k--;
	}
}

//1
//void rotate(vector<int>& nums, int k) {
//	vector<int>res;
//	res.resize(nums.size());
//	size_t len = nums.size();
//	for(size_t ptr = 0; ptr < len; ptr++) {
//		res[(ptr + k) % len] = nums[ptr];
//	}
//	nums = res;
//}

//2
//void rotate(vector<int>& nums, int k) {
//	while (k) {
//		int tmpl = *(nums.rbegin());
//		nums.pop_back();
//		nums.insert(nums.begin(), tmpl);
//		k--;
//	}
//	for (auto now : nums) {
//		cout << now << ' ';
//	}
//}

void reverseString(vector<char>& s) {
	for (size_t beg = 0, end = s.size() - 1; beg < s.size() / 2; beg++, end--) {
		std::swap(s[beg], s[end]);
	}
}

std::vector<std::string> SplitIntoWords(const std::string_view& text) {
	std::vector<std::string> words;
	std::string word;
	for (const char c : text) {
		if (c == ' ') {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		} else {
			word += c;
		}
	}
	if (!word.empty()) {
		words.push_back(word);
	}
	return words;
}

string reverseWords_vec(string s) {
	std::vector<std::string> res = SplitIntoWords(s);
	std::string res_str; 
	for (int ptr = res.size() - 1; ptr >= 0; ptr--) {
		res_str += res[ptr] + ' ';
	}
	res_str.pop_back();
	return res_str;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    int len = sizeLinkdLIst(head) - n;
    ListNode* curr = head;
    if(len == 0) {
        return head = head->next;
    }
    while(--len) {
        curr = curr->next;
    }
    curr->next = curr->next->next;
    return head;
}

int lengthOfLongestSubstring(string s) {
	int longestsubstr = 0;
	map<char, size_t> hsh;
	for (size_t ptr = 0; ptr < s.size(); ptr++) {
		if (hsh.count(s[ptr]) == 0) {
			hsh[s[ptr]] = ptr;
			longestsubstr < hsh.size() ? longestsubstr = hsh.size() : longestsubstr;
		} else {
			ptr = hsh.at(s[ptr]);
			hsh.clear();
		}
	}

	return longestsubstr;
}

bool match(const std::vector<int>& s1, const std::vector<int>& s2) {
	for (size_t ptr = 0; ptr < 26; ptr++) {
		if (s1[ptr] != s2[ptr]) {
			return false;
		}
	}
	return true;
}

bool checkInclusion(string s1, string s2) {
	if(s1.size() > s2.size()){
		return false;
	}
	std::vector<int> s_1(26, 0);
	std::vector<int> s_2(26, 0);
	for (size_t ptr = 0; ptr < s1.size(); ptr++) {
		s_1[s1[ptr] - 'a']++;
		s_2[s2[ptr] - 'a']++;
	}

	size_t ptrB = 0;
	size_t ptrE = s1.size();

	while (ptrE < s2.size()) {
		if (match(s_1, s_2)) {
			return true;
		}
		s_2[s2[ptrE] - 'a']++;
		s_2[s2[ptrB] - 'a']--;
		ptrB++;
		ptrE++;
	}
	if (match(s_1, s_2)) {
		return true;
	}
	return false;
}

void fillNeighboringiPxl(vector<vector<int>>& image, int sr, int sc, int newColor, int tmpColor) {
    if(sr < 0 || sr > image.size() - 1 || sc < 0 || sc > image[sr].size() - 1) {
        return;
    }
    if(image[sr][sc] != tmpColor) {
        return;
    }
    if(image[sr][sc] == newColor) {
        return;
    }
    image[sr][sc] = newColor;
    fillNeighboringiPxl(image, sr + 1, sc, newColor, tmpColor);
    fillNeighboringiPxl(image, sr - 1, sc, newColor, tmpColor);
    fillNeighboringiPxl(image, sr, sc - 1, newColor, tmpColor);
    fillNeighboringiPxl(image, sr, sc + 1, newColor, tmpColor);
}

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int tmp_color = image[sr][sc];
    fillNeighboringiPxl(image, sr, sc, newColor, tmp_color);
    return image;
}

int trav_island(size_t row, size_t column, vector<vector<int>>& grid) {
    if(row < 0 || row > grid.size() - 1 || column < 0 || column > grid[0].size() - 1 || grid[row][column] == 0) {
        return 0;
    }
    grid[row][column] = 0;
    return 1 + trav_island(row - 1, column, grid) + trav_island(row + 1, column, grid) + trav_island(row, column - 1, grid) + trav_island(row, column + 1, grid);
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int max_ = 0;
    size_t R = grid.size();
    size_t C = grid[0].size();
    for(size_t ptr = 0; ptr < R; ptr++) {
        for(size_t ptr1 = 0; ptr1 < C; ptr1++) {
            if(grid[ptr][ptr1] == 1) {
				max_ = max(max_, trav_island(ptr, ptr1, grid));
            }
        }
    }
    return max_;
}



//int singleNumber(vector<int>& nums) {
//	if(nums.size() == 0) {
//		return nums[0];
//	}
//	std::sort(nums.begin(), nums.end());
//	for(size_t ptr = 0; ptr + 1< nums.size(); ptr++) {
//		if(nums[ptr] == nums[ptr + 1]) {
//			ptr++;
//		} else {
//			return nums[ptr];
//		}
//	}
//	return nums[nums.size() - 1];
//}

int binsearch(const int x, const int v[], const int n) {
	int low = 0;
	int hight = n - 1;
	int mid = 0;
	while (low < hight && x != v[mid]) {
		mid = (low + hight) / 2;
		if (x < v[mid]) {
			hight = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return low == hight ? (x == v[mid + 1] ? mid + 1 : -1) : mid;
}

//bool isCousins(TreeNode* root, int x, int y) {
//	queue<TreeNode*> queue_;
//	queue_.push(root);
//	queue_.push(nullptr);
//	int found = 0; 
//	while (!queue_.empty())
//	{
//		TreeNode* current = queue_.front();
//		queue_.pop();
//		if (current == nullptr) {
//			if (!queue_.empty()) {
//				queue_.push(nullptr);
//			} 
//			found = 0;
//			continue;
//		}
//
//		if (current->left!=nullptr && (current->left->val == x || current->left->val == y)) {
//			found ++;
//		} else if (current->right!=nullptr && (current->right->val == x || current->right->val == y)) {
//			found ++;
//		}
//
//		if (found == 2) {
//			return true;
//		} 
//
//		if (current->left!=nullptr) {
//			queue_.push(current->left);
//		}
//		if (current->right!=nullptr){
//			queue_.push(current->right);
//		} 
//	}
//
//	return false;
//}

void clean(char s[], char to_delete) {
	size_t ptrN = 0;
	size_t ptrB = 0;
	for (; s[ptrB] != '\0'; ptrB++) {
		if (s[ptrB] != to_delete) {
			s[ptrN++] = s[ptrB];
			if (s[ptrB + 1] == '-') {
				s[ptrN++] = '-';
			}

		}
	}
	s[ptrN - 1] == '-' ? s[ptrN - 1] = '\0' : s[ptrN] = '\0';
}

void expand(char s1[], char s2[]) {
	clean(s1, '-');
	size_t ptrS2 = 0;
	for (size_t ptr = 0; s1[ptr] != '\0'; ptr++) {
		if(s1[ptr] == '-') {
			char begin = s1[ptr - 1];
			while (begin <= s1[ptr + 1]) {
				s2[ptrS2++] = begin;
				begin++;
			}
		}
	}
	s2[ptrS2] = '\0';
	printf("%s\n", s2);
}

template <typename RIter>
RIter removeMultiplyWhiteSpaces(RIter it, RIter it_end) {
	return unique(it, it_end, [](const auto& a, const auto& b) {
		return a == 32 && b == 32;
		});
}

string reverseWords(string& s) {
	s.erase(removeMultiplyWhiteSpaces(begin(s), end(s)), end(s));
	return reverseWords_vec(s);
}

class RandomizedSet {
public:
    RandomizedSet() = default;
    
    bool insert(int val) {
        if(this->base_.count(val)) {
            return false;
        }
        this->base_.insert(val);
        return true;
    }
    
    bool remove(int val) {
        if(this->base_.count(val)) {
            this->base_.erase(this->base_.find(val));
            return true;
        }     
        return false;
    }
    
    int getRandom() {
        std::random_device rd{};
        mt19937 mt_rand(rd());
        std::uniform_int_distribution<int> uni(0, (this->base_.size() - 1));
        return *(next(this->base_.begin(), uni(mt_rand)));
    }
private:
    set<int> base_;
};

//int findMin(vector<int>& nums) {
//	return *std::min_element(nums.begin(), nums.end());
//}

string reverseOnlyLetters(string s) {
	auto itB = s.begin();
	auto itE = s.end() - 1;
	for (; itB < itE; ) {
		if (!std::isalpha(*itB)) {
			itB++;
		}
		if (!std::isalpha(*itE)) {
			itE--;
		}
		if (std::isalpha(*itB) && std::isalpha(*itE)) {
			std::swap(*itB, *itE);
			itE--;
			itB++;
		}
	}
	return s;
}

vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
	map<int, set<int>> hsh;
	for (size_t ptr = 0; ptr < nums1.size(); ptr++) {
		hsh[nums1[ptr]].insert(1);
	}
	for (size_t ptr = 0; ptr < nums2.size(); ptr++) {
		hsh[nums2[ptr]].insert(2);
	}
	for (size_t ptr = 0; ptr < nums3.size(); ptr++) {
		hsh[nums3[ptr]].insert(3);
	}
	std::vector<int> res;
	for (const auto& [num, sets] : hsh) {
		if (sets.size() >= 2) {
			res.push_back(num);
		}
	}
	return res;
}


int checkPointerPos(int pos, int size) 
{ 
	int lastElem = size - 1; 
	int result = pos; 

	if(pos > lastElem) result = pos - lastElem; 
	if(pos < 0) result = lastElem - std::abs(pos); 
	return result; 
} 

int findMin(vector<int>& nums) { 
	int result; 
	int n1 = 0, n2 = 0; 
	int position = 0; 
	int n1pos, n2pos; 
	while(n1 == n2) 
	{ 
		n1pos = checkPointerPos(position, nums.size()); 
		n2pos = checkPointerPos((position + 1), nums.size()); 
		n1 = nums[n1pos]; 
		n2 = nums[n2pos]; 


		position++; 
	} 

	while(n2 > n1) 
	{ 
		n1pos = checkPointerPos(position, nums.size()); 
		n2pos = checkPointerPos((position + 1), nums.size()); 
		n1 = nums[n1pos]; 
		n2 = nums[n2pos]; 
		position--; 
	} 

	return n2;    
} 

#define MXXXXX 99999
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
	int R = mat.size();
	int C = mat[0].size();
	vector<vector<int>> res(R, vector<int>(C, MXXXXX));
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			if (mat[i][j] == 0) {
				res[i][j] = 0;
			}
		}
	}


	for (int ptr = 0; ptr < R; ptr++) {
		for (int ptr1 = 0; ptr1 < C; ptr1++) {
			if (res[ptr][ptr1] != 0) {
				int min_dist = MXXXXX;
				for (int x = 0; x < R; x++) {
					for (int y = 0; y < C; y++) {
						if (mat[x][y] == 0) {
							min_dist = min(min_dist, abs(ptr - x) + abs(ptr1 - y));
						}
					}
				}
				res[ptr][ptr1] = min_dist;
			}
		}
	}
	return res;
} 

vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> res;
	std::string bitmask(k, 1);
	bitmask.resize(n, 0);
	do {
		vector<int> tmp;
		for (int i = 0; i < n + 1; ++i) {
			if (bitmask[i]) {
				tmp.push_back(i + 1);
			}
		}
		res.push_back(tmp);
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
	return res;
}

vector<vector<int>> permute(vector<int>& nums) {
	std::sort(nums.begin(), nums.end());
	std::vector<vector<int>> res;
	do {
		res.push_back(nums);
	} while (std::next_permutation(nums.begin(), nums.end()));
	return res;
}

vector<string> letterCasePermutation(string s) {
	set<string> res;
	int max = 1 << s.size();
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	for (int ptrm = 0; ptrm < max; ptrm++) {
		string tmp = s;
		for (int ptr = 0; ptr < s.size(); ptr++) {
			if (!std::isdigit(tmp[ptr]) && ((ptrm >> ptr) & 1) == 1) {
				tmp[ptr] = std::toupper(s.at(ptr));
			}
		}
		res.insert(tmp);
	}
	return {res.begin(), res.end()};
}

vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> result;

	sort(begin(nums), end(nums));

	for (size_t firstIdx = 0; firstIdx < nums.size(); ++firstIdx) {
		if (firstIdx > 0 && nums[firstIdx] == nums[firstIdx - 1]) {
			continue;
		}

		size_t secondIdx = firstIdx + 1;
		size_t thirdIdx = nums.size() - 1;

		int requiredSum = 0 - nums[firstIdx];

		while (secondIdx < thirdIdx) {
			int currentSum = nums[secondIdx] + nums[thirdIdx];

			if (currentSum < requiredSum) {
				++secondIdx;
			} else if (currentSum > requiredSum) {
				--thirdIdx;
			} else {
				result.push_back(vector<int>{nums[firstIdx], nums[secondIdx], nums[thirdIdx]});
				++secondIdx;
				while (secondIdx < thirdIdx && nums[secondIdx] == nums[secondIdx - 1]) {
					++secondIdx;
				}
			}
		}
	}

	return result;
}

int minimumTotal(vector<vector<int>>& triangle) {
    vector<int> memo(triangle.size(), 0);
    size_t n = triangle.size() - 1;
 
    for (size_t i = 0; i < triangle[n].size(); i++) {
        memo[i] = triangle[n][i];   
    }
 
    for (int i = triangle.size() - 2; i >= 0; i--)
        for (size_t j = 0; j < triangle[i].size(); j++)
            memo[j] = triangle[i][j] + min(memo[j], memo[j + 1]);
 
    return memo[0];
}

int rob(vector<int>& nums) {
	if (nums.size() == 0) {
		return 0;
	}
	if (nums.size() == 1) {
		return nums[0];
	}
	if (nums.size() == 2) {
		return max(nums[0], nums[1]);
	}
	vector<int> dp(nums.size(), 0);

	dp[0] = nums[0];
	dp[1] = max(nums[0], nums[1]);

	for (int i = 2; i < nums.size(); i++) {
		dp[i] = max(nums[i] + dp[i - 2], dp[i - 1]);
	}
	return dp[nums.size()-1];
}

int minMovesToSeat(vector<int>& seats, vector<int>& students) {
	int moves = 0;
	std::sort(begin(seats), end(seats));
	std::sort(begin(students), end(students));
	for (size_t ptr = 0; ptr < seats.size(); ptr++) {
		moves += std::abs(seats[ptr] - students[ptr]);
	}
	return moves;
}

void don_t(int i, int j, vector<vector<char>>& board) {
    if(i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != 'O') {
        return;
    }
    board[i][j] = '#';
    don_t(i + 1, j, board);
    don_t(i - 1, j, board);
    don_t(i, j + 1, board);
    don_t(i, j - 1, board);
}

void solve(vector<vector<char>>& board) {
    if(board.size() == 0){  
            return;
    }
    for(int i = 0; i < board[0].size(); i++){
        if(board[0][i] == 'O') {
            don_t(0, i, board);
        }
        if(board[board.size() - 1][i] == 'O')
            don_t(board.size() - 1, i, board);
    }
    for(int i = 0; i < board.size(); i++) {
        if(board[i][0] == 'O') {
            don_t(i, 0, board);
        }
        if(board[i][board[0].size() - 1] == 'O') {
            don_t(i, board[0].size() - 1, board);
        }
    }
    for(int i =0; i <board.size(); i++){
        for(int j =0; j <board[0].size(); j++){
            if(board[i][j] == '#') {
                board[i][j] = 'O';
            } else if(board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }
}

bool isThree(int n) {
	if (n <= 2) {
		return false;
	}
	int ctr_div = 0;
	for (int ctr = 1; ctr <= n; ctr++) {
		if (n % ctr == 0) {
			ctr_div++;
		}
	}
	return ctr_div == 3 ? true : false;
}

TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
	if (cloned == nullptr) {
		return {};
	}

	TreeNode* trav = cloned;
	std::queue<TreeNode*> hsh;
	hsh.push(trav);

	while (!hsh.empty()) {
		TreeNode* node = hsh.front();
		hsh.pop();
		if (target->val == node->val) {
			return node;
		}

		if (node->left != nullptr) {
			hsh.push(node->left);
		}
		if (node->right != nullptr) {
			hsh.push(node->right);
		}
	}
}

std::vector<int> leaf_nums {};

void sumLeafNodes(TreeNode *root, int leaf_num) {
    if (!root) {
        return;
    }
    leaf_num += root->val;
    if (!root->left && !root->right) {
        leaf_nums.push_back(leaf_num);
        leaf_num = 0;
        return;
    }
    leaf_num *= 10;
    if (root->left) {
       sumLeafNodes(root->left, leaf_num);
    }
    if (root->right) {
       sumLeafNodes(root->right, leaf_num);
    }
}


int sumNumbers(TreeNode* root) {
    int leaf_num = 0;
    sumLeafNodes(root, leaf_num);
    return std::accumulate(begin(leaf_nums), end(leaf_nums), 0);
}

void reverse(char s[]) {
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[]) {
	int i, sign;
	if ((sign = n) < 0) {
		if (sign == MININT) {
			n += 1;
		}
		n = -n;
	}
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0) {
		if (sign == MININT) {
			s[0] = '8';
		}
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

void itob(int n, char s[], unsigned short base) {
	int i, sign;
	if ((sign = n) < 0) {
		if (sign == MININT) {
			n += 1;
		}
		n = -n;
	}
	i = 0;
	do {
		int tmp_delim = n % base;
		int ch = 0;
		if (tmp_delim >= 0 && tmp_delim <= 9) {
			ch = tmp_delim + '0';
		} else {
			ch = tmp_delim + 55;
		}
		s[i++] = ch;
	} while ((n /= base) > 0);
	if (sign < 0) {
		if (sign == MININT) {
			s[0] = '8';
		}
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}

void itoa_s(int n, char s[], unsigned short spaces) {
	int i, sign;
	if ((sign = n) < 0) {
		if (sign == MININT) {
			n += 1;
		}
		n = -n;
	}
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0) {
		if (sign == MININT) {
			s[0] = '8';
		}
		s[i++] = '-';
	}
	if (i < spaces) {
		while (i < spaces) {
			s[i++] = 32;
		}
	} else if (i > spaces) {
		for (int ptr = 0, ptrb = i - spaces; ptrb <= i; ptr++, ptrb++) {
			s[ptr] = s[ptrb];
		}
	}
	s[spaces] = '\0';
	reverse(s);
}

int sumOfLeftLeaves(TreeNode* root) {
	stack<TreeNode*> hsh;
	hsh.push(root);
	int sum = 0;
	while (!hsh.empty()) {
		TreeNode* tmp = hsh.top();
		hsh.pop();
		if (tmp->right) {
			hsh.push(tmp->right);
		}
		if (tmp->left) {
			hsh.push(tmp->left);
			if (!tmp->left->left && !tmp->left->right) {
				sum += tmp->left->val;
			}
		}
	}
	return sum;
}

int finalValueAfterOperations(vector<string>& operations) {
	int res = 0x00;
	for (const auto& str : operations) {
		switch (str[0]) {
		case '+' :
			++res;
			break;
		case '-':
			--res;
			break;
		case 'X':
			switch (str[1]) {
			case '+' :
				res++;
				break;
			case '-':
				res--;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	return res;
}

int sumEvenGrandparent(TreeNode* root) {
	stack<TreeNode*> hsh;
	hsh.push(root);
	int sum = 0;
	while (!hsh.empty()) {
		TreeNode* tmp = hsh.top();
		hsh.pop();
		if (tmp->val % 2 == 0) {
			if (tmp->left && tmp->left->left) {
				sum += tmp->left->left->val;
			}
			if (tmp->left && tmp->left->right) {
				sum += tmp->left->right->val;
			}
			if (tmp->right && tmp->right->left) {
				sum += tmp->right->left->val;
			}
			if (tmp->right && tmp->right->right) {
				sum += tmp->right->right->val;
			}
		}
		if (tmp->left) {
			hsh.push(tmp->left);
		}
		if (tmp->right) {
			hsh.push(tmp->right);
		}
	}
	return sum;
}

vector<int> singleNumber(vector<int>& nums) {
	map<int, int> hsh;
	vector<int> res;
	for(const auto& num : nums) {
		hsh[num] ++;
	}
	for(const auto& [num, ctr] : hsh) {
		if (ctr == 1) {
			res.push_back(num);
		}
	}
	return res;
}

std::string intToRoman(int num) {
    std::map<int, std::string> rom {{1, "I"}, {4, "IV"}, {5, "V"}, {9, "IX"}, {10, "X"},
     {40, "XL"}, {50, "L"}, {90, "XC"}, {100, "C"}, {400, "CD"}, {500, "D"},
     {900, "CM"}, {1000, "M"}};
    std::string roman;
    int reminder = num;
    for(auto it = rom.rbegin(); it != rom.rend() || reminder > 0; it++) {
        int quotient = reminder / it->first;
        reminder -= (quotient * it->first);
        while(quotient--) {
           roman += it->second;     
        }
    }
    return roman;
}

int minStartValue(vector<int>& nums) {
    int min_res = 1;
    bool YES = false;
    while(!YES) {
        int tmp_min_res = min_res;
        for(size_t ptr = 0; ptr < nums.size(); ptr++ ) {
            tmp_min_res += nums[ptr];
            if(tmp_min_res >= 1) {
                YES = true;
            } else {
                YES = false;
                min_res++;
                break;
            }
        }
    }
    return min_res;
}

vector<int> dailyTemperatures(vector<int>& temperatures) {
	vector<int> res(temperatures.size(), 0);
	stack<int> stk;
	for (int ptr = 0; ptr < temperatures.size(); ptr++) {
		while (!stk.empty() && temperatures[stk.top()] < temperatures[ptr]) {
			const auto idx = stk.top();
			stk.pop();
			res[idx] = ptr - idx;
		}
		stk.emplace(ptr);
	}
	return res;
}

int deepestLeavesSum(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}
	vector<vector<int>> lvls;
	TreeNode* trav = root;
	std::queue<TreeNode*> hsh;
	hsh.push(trav);
	while (!hsh.empty()) {
		vector<int> tmp;
		size_t level = hsh.size();
		while (level > 0) {
			TreeNode* node = hsh.front();
			hsh.pop();
			tmp.push_back(node->val);
			if (node->left) {
				hsh.push(node->left);
			}
			if (node->right) {
				hsh.push(node->right);
			}
			level--;
		}
		lvls.push_back(tmp);
	}
	int res = 0;
	for (const auto& val : lvls[lvls.size() - 1]) {
		res += val;
	}
	return res;
}

TreeNode* nuilder(vector<int>& nums, int start, int end) {
	if (start < 0 || start >= end || end > nums.size()) {
		return nullptr;
	}
	auto max = max_element(nums.begin() + start,nums.begin() + end);
	TreeNode* root = new TreeNode(*max);
	root->left = nuilder(nums, start, std::distance(nums.begin(), max));
	root->right = nuilder(nums,  std::distance(nums.begin(), max + 1), end);
	return root;
}

TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
	if (nums.empty()) {
		return {};
	}
	return nuilder(nums, 0, nums.size() - 1);
}

vector<int> minOperations(string boxes) {
    vector<int> res(boxes.size(), 0);
    for(int ptr = 0; ptr < res.size(); ptr++) {
        for(int ch = 0; ch < boxes.size(); ch++) {
            if(ptr != ch && boxes[ch] == '1') {
                res[ptr] += std::abs(ptr - ch);
            }
        }
    }
            
    return res;
}

vector<int> largestDivisibleSubset(vector<int>& nums) {
    vector<int> result;
    sort(nums.begin(),nums.end());
    vector<int> dp(nums.size(),0);
    vector<int> parent(nums.size(),0);
    int mx=0;
    int mx_idx=0;
    for(int i=nums.size()-1;i>=0;i--){
        for(int j=i;j<nums.size();j++){
            if(nums[j]%nums[i]==0&&dp[i]<dp[j]+1){
                dp[i]=dp[j]+1;
                parent[i]=j;
                if(mx<dp[i]){
                    mx=dp[i];
                    mx_idx=i;
                }
            }
        }
    }
    for(int i=0;i<mx;i++){
        result.push_back(nums[mx_idx]);
        mx_idx=parent[mx_idx];
    }
    return result;
}

string simplifyPath(string path) {
	std::string path_res;
	size_t pos = 0;
	while ((pos = path.find("//", pos)) != std::string::npos) {
		path.replace(pos, 2, "/");
	}
	pos = 0;
	while ((pos = path.find("/./", pos)) != std::string::npos) {
		path.replace(pos, 3, "/");
	}
	stringstream tok_strem(path);
	deque<string>buff;
	string tmp_token;
	while(getline(tok_strem, tmp_token, '/')) {
		if(tmp_token == "..") {
			if(!buff.empty()) {
				buff.pop_back();
			} else {
				continue;
			}
		} else if (tmp_token == ".") {
			continue;    
		} else {
			buff.push_back(tmp_token);
		}
	}

	for(const auto& elem : buff) {
		path_res += elem + '/';
	}
	path_res.empty() ? path_res += '/' : path_res;
	path_res[0] == '/'? path_res : path_res.insert(0, 1, '/');
	if(path_res[path_res.size() - 1] == '/' && path_res.size() > 1) {
		path_res.pop_back();
	}
	return path_res;
}

bool canWinNim(int n) {
	return n % 4 != 0; 
}

string Sum(string a, string b) {
    if(a.size() < b.size()) {
        swap(a, b);
    }
    int j = a.size()-1;
    for(int i=b.size()-1; i>=0; i--, j--) {
        a[j]+=(b[i]-'0');
    }
    for(int i=a.size()-1; i>0; i--) {
        if(a[i] > '9') {
            int d = a[i]-'0';
            a[i-1] = ((a[i-1]-'0') + d/10) + '0';
            a[i] = (d%10)+'0';
        }
    }
    if(a[0] > '9') {
        string k;
        k+=a[0];
        a[0] = ((a[0]-'0')%10)+'0';
        k[0] = ((k[0]-'0')/10)+'0';
        a = k+a;
    }
    return a;
}
    
string getNumFromListNode(ListNode* l1) {
    string num;
    while(l1 != nullptr) {
        num.insert(0, 1, '0' + l1->val);
        l1 = l1->next;
    }
    return num;
}
    
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    string a = getNumFromListNode(l1);
    string b = getNumFromListNode(l2);
    string str_res = Sum(a, b);
        
    ListNode * l3 = new ListNode();
    ListNode * tmp = l3;
    while(!str_res.empty()) {
        int tmp_val = str_res.back() - '0';
        str_res.pop_back();
        tmp->val = tmp_val;
        if(!str_res.empty()) {
            tmp->next = new ListNode();
        }
        tmp = tmp->next;
    }
    return l3;
}

int threeSumClosest(vector<int>& nums, int target) {
    int min_dist = INT_MAX;
    int min_summ = 0;
    std::sort(nums.begin(), nums.end());
    for(int ptr = 0; ptr < nums.size(); ++ptr) {
        int left = ptr + 1;
        int right = nums.size() - 1;
        while(left < right) {
            int summ = nums[ptr] + nums[left] + nums[right];
            int dist = std::abs(target - summ);
            if(dist < min_dist) {
                min_dist = dist;
                min_summ = summ;
            }
            if(min_summ == target) {
                return min_summ;
            } else if(summ > target) {
                right--;
            } else {
                left++;
            }
        }
    }
    return min_summ;
}

vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
	if ((r * c) != (mat.size() * mat[0].size())) {
		return mat;
	}
	size_t rCol = 0;
	size_t rRow = 0;
	vector<vector<int>> res(r, vector<int>(c, 0)); 
	for(size_t ptr = 0; ptr < mat.size(); ptr++) {
		for(size_t ptr1 = 0; ptr1 < mat[0].size(); ptr1++) {
			res[rRow][rCol++] = mat[ptr][ptr1];
			if(rCol >= c) {
				rRow ++;
				rCol = 0;
			}
		}
	}

	return res;
}

int singleNonDuplicate(vector<int>& nums) {
	for(size_t ptr = 0; ptr + 1 < nums.size(); ptr += 2) {
		if(nums[ptr] - nums[ptr + 1] != 0) {
			return nums[ptr];
		}    
	}
	return nums[nums.size() - 1];
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
	int m = matrix.size();
	int n = matrix[0].size();
	for (int ptr = 0; ptr < m; ++ptr) {
		if (matrix[ptr][n - 1] == target) {
			return true;
		} else if (matrix[ptr][n - 1] > target) {
			auto it = std::find(matrix[ptr].begin(), matrix[ptr].end(), target);
			return it != matrix[ptr].end();
		}
	}
	return false;
}

bool checkSudokuColumn(const vector<vector<char>>& board) {
	for (size_t row = 0; row < 9; ++row) {
		vector<int> hsh(9, 0);
		for (size_t col = 0; col < 9; ++col) {
			if (std::isdigit(board[row][col])) {
				hsh[(board[row][col] - '0') - 1] += 1;
			}
		}
		for (size_t ctr = 0; ctr < 9; ++ctr) {
			if (hsh[ctr] > 1) {
				return false;
			}
		}
	}
	return true;
}

bool checkSudokuRow(const vector<vector<char>>& board) {
	vector<int> hsh(10, 0);
	for (size_t row = 0, col = 0; row < 9 && col < 9; ++row) {
		if (std::isdigit(board[row][col])) {
			hsh[(board[row][col] - '0')] += 1;
		}
		if (row == 8) {
			row = -1;
			col++;
			for (size_t ctr = 0; ctr < 10; ++ctr) {
				if (hsh[ctr] > 1) {
					return false;
				} else {
					hsh[ctr] = 0;
				}
			}
		}
	}
	return true;
}

bool checkSudoku9x9(const vector<vector<char>>& board, int start, int end) {
	set<char> hsh;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (board[i + start][j + end] != '.') {
				if (hsh.find(board[i + start][j + end]) != hsh.end()) {
					return false;
				}
				hsh.insert(board[i + start][j + end]);
			}
		}
	}
	return true;
}

bool isValidSudoku(vector<vector<char>>& board) {
	for (size_t i = 0; i < 9; ++i) {
		for (size_t j = 0; j < 9; ++j) {
			if (!checkSudoku9x9(board, i - i % 3, j - j % 3)) {
				return false;
			}
		}
	}
	return checkSudokuRow(board) && checkSudokuColumn(board);
}

bool incr(const vector<int>& nums) {
	for(size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		if(nums[ptr] > nums[ptr + 1]) {
			return false;
		}
	}
	return true;
}
bool decr(const vector<int>& nums) {
	for(size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		if(nums[ptr] < nums[ptr + 1]) {
			return false;
		}
	}
	return true;
}
bool isMonotonic(vector<int>& nums) {
	return incr(nums) || decr(nums);
}

TreeNode * Add(TreeNode * node, int elem) {
	if (node == nullptr) {
		node = new TreeNode(elem);
	} else {
		if (elem < node->val) {
			node->left = Add(node->left, elem);
		} else {
			node->right = Add(node->right, elem);
		}
	}

	return node;
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
	return Add(root, val);
}

TreeNode* LCARecursive(TreeNode* root, TreeNode* x, TreeNode* y) {
if (root == nullptr) {
    return nullptr;
}
 
if (root->val > max(x->val, y->val)) {
    return LCARecursive(root->left, x, y);
}
 
else if (root->val < min(x->val, y->val)) {
    return LCARecursive(root->right, x, y);
}
 
return root;
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return LCARecursive(root, p, q);
}

bool isValidBST(TreeNode* root) {
    if (root == nullptr) {
		return false;
	}

	TreeNode* trav = root;
	std::stack<TreeNode*> hsh;
	std::vector<int> traversals_;
	while (trav != nullptr || !hsh.empty()) {
		while (trav != nullptr) {
			hsh.push(trav);
			trav = trav->left;
		}
		TreeNode* node = hsh.top();
		hsh.pop();
		traversals_.push_back(node->val);
		trav = node->right;
	}
    for(size_t ptr = 0; ptr + 1 < traversals_.size(); ptr++) {
        if(traversals_[ptr] >= traversals_[ptr + 1]) {
            return false;
        }
    }
    return true;
}

ListNode* oddEvenList(ListNode* head) {
	if (!head || !head->next) {
		return head;
	}
	ListNode* root_ = head;
	std::vector<ListNode*> hsh;
	while (root_) {
		hsh.push_back(root_);
		root_ = root_->next;
	}
	ListNode* odd = head->next;
	ListNode* even = head;
	ListNode* tmp_odd = odd;
	ListNode* tmp_even = even;
	for(size_t ptr = 2; ptr < hsh.size(); ptr+=2){
		if(ptr+1 < hsh.size()) {
			tmp_odd->next = hsh[ptr+1];
		} else {
			tmp_odd->next = nullptr;
		}

		if(ptr < hsh.size() - 2) {
			tmp_even->next = hsh[ptr];
		} else {
			tmp_even->next = hsh[ptr];
			tmp_even->next->next = nullptr;
		}
		tmp_even = tmp_even->next; 
		tmp_odd = tmp_odd->next;    

	}
	tmp_even->next = odd;
	return even;
}

class MyStack {
public:
	MyStack() = default;

	void push(int x) {
		this->base_.push(x);
	}

	int pop() {
		int res = this->base_.back();
		queue<int> tmp;
		while (!this->base_.empty()) {
			int val = this->base_.front();
			this->base_.pop();
			if (!this->base_.empty()) {
				tmp.push(val);
			}
		}
		this->base_ = tmp;
		return res;
	}

	int top() {
		return this->base_.back();
	}

	bool empty() {
		return this->base_.empty();
	}
private:
	queue<int> base_;
};

void AoC() {
	ifstream chiferki("./num.txt");
	std::string tmp;
	std::vector<int> numbers;
	std::vector<int> numbers_1;
	while(std::getline(chiferki, tmp)) {
	numbers.push_back(std::stoi(tmp));
	}
	int ctr = 0;
	for(size_t ptr = 1; ptr + 1 < numbers.size(); ptr ++) {
	numbers_1.push_back((numbers[ptr - 1] + numbers[ptr] + numbers[ptr + 1])); 
	}
	for(size_t ptr = 1; ptr < numbers_1.size(); ptr ++) {
	if(numbers_1[ptr] > numbers_1[ptr - 1]) {
	    ctr++;
	}
	}
	std::cout << ctr << std::endl;
}

int maxProduct(vector<int>& nums) {
	if (nums.size() == 1) {
		return nums[0];
	}
	int max1 = nums[0];
	for(size_t ptr = 0; ptr < nums.size(); ++ptr) {
		int tmp_max = nums[ptr];
		size_t ptr1 = ptr + 1;
		max1 = max(max1, tmp_max);
		while(ptr1 < nums.size()) {
			tmp_max *= nums[ptr1];
			max1 = max(max1, tmp_max);
			++ptr1;
		}          
	}
	return max1;
}

void AoC_2() {
	ifstream chiferki("./submarine.txt");
	std::string tmp;
	int hor_pos = 0;
	int depth_pos = 0;
	int aim = 0;
	while(std::getline(chiferki, tmp)) {
		std::string number = tmp.substr(tmp.find_last_of(32));
		cout << tmp << ' ' << number << std::endl;
		switch (tmp[0]) {
		case 'f':
			hor_pos += std::stoi(number);
			depth_pos += (aim * std::stoi(number));
			break;
		case 'u':
			aim -= std::stoi(number);
			break;
		case 'd':
			aim += std::stoi(number);
			break;
		default:
			break;
		}

	}
	std::cout << hor_pos << '|' << depth_pos << std::endl;
	std::cout << hor_pos*depth_pos << std::endl;
}

void AoC_3() {
	ifstream chiferki("./binAOC.txt");
	std::string tmp;
	std::string hamma_2d;
	std::string epsilon_2d;
	vector<int> hsh_1(12, 0);
	vector<int> hsh_0(12, 0);
	while(std::getline(chiferki, tmp)) {
		for (size_t ptr = 0; ptr < tmp.size(); ++ptr) {
			switch (tmp[ptr]) {
			case '1':
				++hsh_1[ptr];
				break;
			case '0':
				++hsh_0[ptr];
				break;
			default:
				break;
			}
		}
	}
	for (size_t ptr = 0; ptr < 12; ++ptr) {
		if (hsh_1[ptr] > hsh_0[ptr]) {
			hamma_2d += '1';
			epsilon_2d += '0';
		} else {
			hamma_2d += '0';
			epsilon_2d += '1';
		}
	}

	std::cout << std::stoi(hamma_2d, nullptr, 2) * std::stoi(epsilon_2d, nullptr, 2) << std::endl;
}

void AoC_3_1() {
	ifstream chiferki("./binAOC.txt");
	std::string tmp;
	std::vector<std::string> whole_numbers;
	while (std::getline(chiferki, tmp)) {
		whole_numbers.push_back(tmp);
	}
	chiferki.close();
	std::vector<std::string> oxy = whole_numbers;
	for (size_t ptr = 0; ptr < 12; ++ptr) {
		if (oxy.size() == 1) {
			break;
		}
		int ctr = 0;
		std::vector<std::string> oxy_tmp;
		for (size_t ptr1 = 0; ptr1 < oxy.size(); ++ptr1) {
			if (oxy[ptr1][ptr] == '1') {
				ctr++;
			} else {
				ctr--;
			}
		}
		if (ctr >= 0) {
			for (size_t ptr1 = 0; ptr1 < oxy.size(); ++ptr1) {
				if (oxy[ptr1][ptr] == '1') {
					oxy_tmp.push_back(oxy[ptr1]);
				}
			}
		} else {
			for (size_t ptr1 = 0; ptr1 < oxy.size(); ++ptr1) {
				if (oxy[ptr1][ptr] == '0') {
					oxy_tmp.push_back(oxy[ptr1]);
				}
			}
		}
		oxy = oxy_tmp;
	}
	std::vector<std::string> CO2 = whole_numbers;
	for (size_t ptr = 0; ptr < 12; ++ptr) {
		if (CO2.size() == 1) {
			break;
		}
		int ctr = 0;
		std::vector<std::string> co2_tmp;
		for (size_t ptr1 = 0; ptr1 < CO2.size(); ++ptr1) {
			if (CO2[ptr1][ptr] == '1') {
				ctr++;
			} else {
				ctr--;
			}
		}
		if (ctr >= 0) {
			for (size_t ptr1 = 0; ptr1 < CO2.size(); ++ptr1) {
				if (CO2[ptr1][ptr] == '0') {
					co2_tmp.push_back(CO2[ptr1]);
				}
			}
		} else {
			for (size_t ptr1 = 0; ptr1 < CO2.size(); ++ptr1) {
				if (CO2[ptr1][ptr] == '1') {
					co2_tmp.push_back(CO2[ptr1]);
				}
			}
		}
		CO2 = co2_tmp;
	}
	cout << oxy[0] << ' ' << CO2[0] << endl;
	if (CO2.size() == 1 && oxy.size() == 1) {
		std::cout << std::stoi(CO2[0], nullptr, 2) * std::stoi(oxy[0], nullptr, 2) << std::endl;
	}
}

void AoC_4_1() {
	ifstream chiferki("./binAOC.txt");
	vector<int> numbers;
	vector<vector<vector<int>>> boards;
	vector<vector<int>> board;
	std::string tmp;
	std::getline(chiferki, tmp);
	std::stringstream ss(tmp);
	while (std::getline(ss, tmp, ',')) {
		numbers.push_back(std::stoi(tmp));
	}
	std::getline(chiferki, tmp);
	vector<int> line;
	while (std::getline(chiferki, tmp)) {
		if (!tmp.empty()) {
			line.clear();
			std::stringstream xx(tmp);
			while (std::getline(xx, tmp, ' ')) {
				if (std::isdigit(tmp[0])) {
					line.push_back(std::stoi(tmp));
				}
			}
			board.push_back(line);
		} else {
			if (!board.empty()) {
				boards.push_back(board);
				line.clear();
				board.clear();
			}
		}
	}
	chiferki.close();
	boards.push_back(board);

	//for (const auto& board : boards) {
	//	for (const auto& line : board) {
	//		for (const auto& num : line) {
	//			cout << num << ' ';
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}


}

int numTrees(int n) {
    vector<int> dp(n + 1, 1);
    for (int i = 1; i <= n; ++i)
    {
        int sum = 0;
        for (int j = 0; j < i; ++j)
        {
            sum += dp[j] * dp[i - 1 - j];
        }
        
        dp[i] = sum;
    }
    return dp[n];
}


int minCostClimbingStairs(vector<int>& cost) {
	if (cost.size() == 2) {
		return min(cost[0], cost[1]);
	}

	std::vector<int> floors(cost.size(), 0);
	floors[0] = cost[0];
	floors[1] = cost[1];
	for (int ptr = 2; ptr < cost.size(); ptr++) {
		floors[ptr] = min(floors[ptr - 1], floors[ptr - 2]) + cost[ptr];
	}
	return min(floors[floors.size() - 1], floors[floors.size() - 2]);
}

int findContentChildren(vector<int>& g, vector<int>& s) {
	std::sort(g.begin(), g.end());
	std::sort(s.begin(), s.end());
	auto g_p = g.begin();
	auto s_p = s.begin();
	int res = 0;
	while (g_p != g.end() && s_p != s.end()) {
		if (*s_p >= *g_p) {
			res++;
		} else {
			while (s_p != s.end()) {
				if (*s_p >= *g_p) {
					res++;
					break;
				}
				s_p++;
			}
		}
		if (g_p != g.end()) {
			g_p++;
		}
		if (s_p != s.end()) {
			s_p++;
		}
	}
	return res;
}

int arrayPairSum(vector<int>& nums) {
	std::sort(std::begin(nums), std::end(nums));
	int res = 0;
	auto b_n = std::begin(nums);
	for (; b_n != std::end(nums); ++b_n) {
		res += min(*b_n, *(++b_n));
	}
	return res;
}

class Solution_listnode {
public:
	Solution_listnode(ListNode* head) {
		while (head != nullptr) {
			this->base_.push_back(head->val);
			head = head->next;
		}
	}

	int getRandom() {
		return this->base_[rand() % this->base_.size()];
	}
private:
	std::vector<int> base_;
};

void hashFill(std::set<int>& hsh, TreeNode* root) {
	if (!root) {
		return;
	}
	hsh.insert(root->val);
	hashFill(hsh, root->left);
	hashFill(hsh, root->right);
}

bool isUnivalTree(TreeNode* root) {
	if (!root) {
		return true;
	}
	std::set<int> hsh;
	hashFill(hsh, root);
	return hsh.size() == 1 ? 1 : 0;
}

int mostWordsFound(vector<string>& sentences) {
    int res = 0;
    for(const auto& sentence : sentences) {
        int tmp = count(sentence.begin(), sentence.end(), 32) + 1;
        res < tmp ? res = tmp : res = res;
    }
    return res;
}

bool isPalindrome(const string& x) {
	if (x.size() == 0) {
		return true;
	}
	for (size_t btr = 0, ept = x.size() - 1; btr < x.size() / 2; btr++, ept--) {
		if (x[btr] != x[ept]) {
			return false;
		}
	}
	return true;
}

string firstPalindrome(vector<string>& words) {
    for(const auto& word : words) {
        if(isPalindrome(word)) {
            return word;
        }
    }
    return {};
}

vector<string> summaryRanges(vector<int>& nums) {
	vector<string> buff;
	if (nums.size() == 1) {
		return { std::to_string(nums[0]) };
	}
	for (size_t ptr = 0; ptr + 1 < nums.size(); ++ptr) {
		std::string tmp_range = std::to_string(nums[ptr]);
		if (nums[ptr] != (nums[ptr + 1] - 1)) {
			buff.push_back(tmp_range);
			if ((ptr + 1) == nums.size() - 1) {
				buff.push_back(std::to_string(nums[ptr + 1]));
			}
		}
		else if (nums[ptr] == (nums[ptr + 1] - 1)) {
			tmp_range += "->";
			while ((ptr + 1 < nums.size()) && (nums[ptr] == (nums[ptr + 1] - 1))) {
				++ptr;
			}
			tmp_range += std::to_string(nums[ptr]);
			buff.push_back(tmp_range);
			if ((ptr + 1) == nums.size() - 1) {
				buff.push_back(std::to_string(nums[ptr + 1]));
			}
		}
	}
	return buff;
}

vector<int> countBits_1(int n) {
	vector<int> res;
	res.push_back(0);
	for (unsigned int ptr = 1; ptr <= n; ptr++) {
		res.push_back(bitcount(ptr));
	}
	return res;
}

int numberOfArithmeticSlices(vector<int>& nums) {
	int subar = 0;
	vector<int> hsh(nums.size());

	for (size_t ptr = 2; ptr < nums.size(); ++ptr) {
		int distance_1 = (nums[ptr] - nums[ptr - 1]);
		int distance_2 = (nums[ptr - 1] - nums[ptr - 2]);
		if (distance_1 == distance_2) {
			hsh[ptr] = hsh[ptr - 1] + 1;
			subar += hsh[ptr];
		}
	}
	return subar;
}

int deleteAndEarn(vector<int>& nums) {
    map<int, int> hsh;
    int ctr = 0;
    int cnt = 0;
    for(size_t ptr = 0; ptr < nums.size(); ++ptr) {
        ++hsh[nums[ptr]];
    }

    auto ptr = hsh.begin();
    
    for(; ptr != hsh.end(); ++ptr, ++cnt) {
        int x = ptr->first;
        int temp = x * ptr->second;
        auto it1 = std::prev(ptr);
        auto it2 = std::prev(it1);
        
        if(cnt >= 1 && ((x - it1->first) > 1)) {
            temp += hsh[it1->first];
        } else if( cnt >= 2 ) {
            temp += hsh[it2->first];
        }
        hsh[ptr->first] = max(temp, cnt >= 1 ? hsh[it1->first] : 0);
        ctr = max(ctr, temp);
    }
    
    return ctr;
}

ListNode* deleteDuplicates(ListNode* head) {
	if (!head || !head->next) {
		return head;
	}
	map<int, int> hsh;
	while (head) {
		++hsh[head->val];
		head = head->next;
	}
	ListNode* returned = nullptr;
	for (const auto& [val, ctr] : hsh) {
		if (ctr == 1) {
			ListNode* tmp = new ListNode(val, nullptr);
			ListNode* tmp_ptr = nullptr;
			if (!returned && tmp) {
				returned = tmp;
			}
			else {
				tmp_ptr = returned;
				while (tmp_ptr->next) {
					tmp_ptr = tmp_ptr->next;
				}
				tmp_ptr->next = tmp;
			}
		}
	}
	return returned;
}


class cl {
public:
	char c[1024];
};

double ShannonEntropy(vector<int> data) {
	double entropy = 0;
	std::map<int, long> counts;
	typename std::map<int, long>::iterator it;
	//
	for (int dataIndex = 0; dataIndex < data.size(); ++dataIndex) {
		counts[data[dataIndex]]++;
	}
	//
	it = counts.begin();
	while (it != counts.end()) {
		float p_x = (float)it->second / data.size();
		if (p_x > 0) entropy -= p_x * log(p_x) / log(2);
		it++;
	}
	return entropy;
}

bool key_prepare(std::string& key, const std::string& plain_text) {
	size_t tmp_len = key.size();
	size_t text_length = plain_text.size();
	if (tmp_len >= text_length) {
		return true;
	}
	for (size_t ptr = 0, ptr1 = 0; ; ++ptr, ++ptr1) {
		if (plain_text[ptr1] != 32) {
			if (ptr == tmp_len) {
				ptr = 0;
			}
			if (text_length == key.size()) {
				return true;
			}
			key += key[ptr];
		} else {
			key += 32;
		}
	}
	return false;
}

std::string vegenere_enc(const std::string& plaint_text, const std::string& key) {
	std::string result;
	for (size_t ptr = 0; ptr < plaint_text.size(); ++ptr) {
		if (plaint_text[ptr] != 32) {
			char tmp = (plaint_text[ptr] + key[ptr]) % 26;
			tmp += 65;
			result += tmp;
		} else {
			result += 32;
		}
	}
	return result;
}

std::string vegenere_dec(const std::string& cipher_text, const std::string& key) {
	std::string result;
	for (size_t ptr = 0; ptr < cipher_text.size(); ++ptr) {
		if (cipher_text[ptr] != 32) {
			char tmp = (cipher_text[ptr] - key[ptr] + 26) % 26;
			tmp += 65;
			result += tmp;
		} else {
			result += 32;
		}
	}
	return result;
}

void veg_text_prep(std::string& text) {
	for (auto& ch : text) {
		ch = std::toupper(ch);
	}
}

    template <typename T>
    void swap_(T& a, T& b) {
        T tmp_ = a;
        a = b;
        b = tmp_;
    }
    template <typename T>
    void merge(std::vector<T>& main, size_t B, size_t S, size_t Q) {
        std::size_t b1 = B, e1 = Q, b2 = e1;
        std::vector<T> tmp_array;
        while (tmp_array.size() < S - B) {
            if (b1 >= e1 || (b2 < S && main[b2] <= main[b1])) {
                tmp_array.push_back(main[b2]);
                ++b2;
            }
            else {
                tmp_array.push_back(main[b1]);
                ++b1;
            }
        }
        for (size_t ptr = B; ptr < S; ++ptr) {
            main[ptr] = tmp_array[ptr-B];
        }
    }
    void merge_sort_(std::vector<int>& main, size_t B, size_t S) {
        if (S - B < 2) {
            return;
        }
        if (S - B == 2) {
            if (main[B] > main[B+1]) {
                swap_(main[B], main[B+1]);
            }
            return;
        }

        merge_sort_(main, B, B + (S - B ) / 2);
        merge_sort_(main, B + (S - B) / 2, S);
        merge(main, B, S, B + (S - B) / 2);
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        merge_sort_(nums, 0, nums.size());
        return nums[nums.size() - k];
    }

    string convert(string s, int numRows) {
        string result;
        vector<vector<char>> matrix;
        matrix.resize(numRows);
        bool direction = false;
        int fact_row = 0;
        int len = s.size();
        while (len > 0) {
            matrix[fact_row].push_back(s[s.size() - len]);
            
            direction ? fact_row-- : fact_row++;    
    
            if(fact_row == numRows) {
                fact_row -= 2;
                direction = true;  
            } else if(fact_row == -1) {
                fact_row += 2;
                direction = false;
            }
            if(numRows == 1) {
                fact_row = 0;
            }
            --len;
        }
        
        for(const auto& vec : matrix) {
            for(const auto& ch : vec) {
                result += ch;
            }   
        }
        
        return result;
    }


ListNode* reverseLL(ListNode* head) {
        if(!head || !head->next) {
            return head;
        }
        ListNode* result = reverseLL(head->next);
        head->next->next = head;
        head->next = nullptr;
        return result;
    }
    size_t lenLL(ListNode* head) {
        if(!head) {
            return 0;
        }
        size_t res = 0;
        while(head) {
            res++;
            head = head->next;
        }
        return res;
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(!head || !head->next || right == 1 || left == right) {
            return head;
        }
        int ll_len = lenLL(head);
        
        ListNode* curr = head;
        ListNode* prev = nullptr;
        
        size_t ptr = 1;
        while(ptr < left && curr) {
            prev = curr;
            curr = curr->next;
            ptr++;
        }
        
        ListNode* END = curr;
        ListNode* BEGIN = nullptr;
        
        while(ptr <= right && curr) {
            ListNode* next_1 = curr->next;
            curr->next = BEGIN;
            BEGIN = curr;
            curr = next_1;
            ++ptr;
        }
        if(prev != nullptr) {
            prev->next = BEGIN;
        } else {
            head = BEGIN;
        }
        if(END) {
            END->next = curr;
        }
        
        return head;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k == 1) {
            return head;
        }
        int len = lenLL(head);
        if (len / k == 1) {
            return reverseBetween(head, 1, k);
        }
        int left = 1;
        int right = 1;
        while(right < len) {
            right++;
            if(right % k == 0 && left <= right) {
                head =  reverseBetween(head, left, right);
                right++;
                left = right;
            }
        }
        return head;
    }

int main(int argc, char* argv[]) {
	std::string PT = "CIPHER TEXT";
	std::string key = "XO";
	veg_text_prep(key);
	veg_text_prep(PT);
	if (!key_prepare(key, PT)) {
		std::cout << "something wrong with key\n";
		return -1;
	}
	std::cout << "Prepeared in UPPER CASE PT: " << PT << std::endl;
	std::cout << "Prepeared in UPPER CASE KEY: " << key << std::endl;

	std::string CT = vegenere_enc(PT, key);
	std::cout << "Prepeared CT: " << CT << std::endl;
	std::cout << "DECRIPTION CT RESULT: " << vegenere_dec(CT, key) << std::endl;
	return 0;
}

