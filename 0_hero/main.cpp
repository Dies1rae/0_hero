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

bool isCousins(TreeNode* root, int x, int y) {
	queue<TreeNode*> queue_;
	queue_.push(root);
	queue_.push(nullptr);
	int found = 0; 
	while (!queue_.empty())
	{
		TreeNode* current = queue_.front();
		queue_.pop();
		if (current == nullptr) {
			if (!queue_.empty()) {
				queue_.push(nullptr);
			} 
			found = 0;
			continue;
		}

		if (current->left!=nullptr && (current->left->val == x || current->left->val == y)) {
			found ++;
		} else if (current->right!=nullptr && (current->right->val == x || current->right->val == y)) {
			found ++;
		}

		if (found == 2) {
			return true;
		} 

		if (current->left!=nullptr) {
			queue_.push(current->left);
		}
		if (current->right!=nullptr){
			queue_.push(current->right);
		} 
	}

	return false;
}

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

int main() {
	combine(4, 2);
	return 0;
}
