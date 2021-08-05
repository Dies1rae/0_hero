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

vector<int> getConcatenation(vector<int>& nums) {
	size_t S = nums.size();
	vector<int> res(S * 2, 0);
	for (size_t ptr = 0; ptr < S; ptr++) {
		res[ptr] = nums[ptr];
		res[ptr + S] = nums[ptr];
	}
	return res;
}

vector<int> buildArray(vector<int>& nums) {
	size_t S = nums.size();
	vector<int> res(S, 0);
	for (size_t ptr = 0; ptr < S; ptr++) {
		res[ptr] = nums[nums[ptr]];
	}
	return res;
}


int digitsSumProduct(int elem, bool typo) {
	int res = 0;
	if (typo) {
		while (elem) {
			res += elem % 10;
			elem /= 10;
		
		}
	} else {
		res = elem % 10;
		elem /= 10;
		while (elem) {
			res *= elem % 10;
			elem /= 10;

		}
	}
	return res;
}

int subtractProductAndSum(const int n) {
	return digitsSumProduct(n, 0) - digitsSumProduct(n, 1);
}


template <typename T>
class num_it {
public:
	explicit num_it(const T pos = 0) : i_(pos) {}
	T operator*() const {
		return this->i_;
	}
	num_it& operator++() {
		this->i_++;
		return *this;
	}
	bool operator==(const num_it& other) const {
		return this->i_ == other.i_;
	}
	bool operator!=(const num_it& other) const {
		return !(*this == other);
	}
private:
	T i_;
};

template <typename T>
class num_range {
public:
	num_range(const T from, const T to) : a_(from), b_(to) {}
	num_it<T> begin() const {
		return num_it(this->a_);
	}

	num_it<T> end() const {
		return num_it(this->b_);
	}
private:
	T a_;
	T b_;
};

bool areOccurrencesEqual(string s) {
vector<int> chars(26, 0);
for (const char& ch : s) {
	chars[ch - 97]++;
}

int max_char = *max_element(chars.begin(), chars.end());
for (size_t ptr = 0; ptr < 26; ptr++) {
	if (chars[ptr] != max_char) {
		return false;
	}
}
return true;
}

int countGoodSubstrings(const string& s) {
	set<string> good;
	size_t ptrB = 0;
	while (ptrB < s.size()) {
		good.insert(s.substr(ptrB, 3));
		ptrB += 3;
	}
	int res = 0;
	for (const auto& str : good) {
		if (str.size() == 3) {
			res++;
		}
	}
	return res;
}

void selection_sort_(std::vector<int>& main, std::size_t S) {
	std::size_t min_indx;
	for (std::size_t ptr = 0; ptr < S - 1; ptr++) {
		min_indx = ptr;
		for (std::size_t ptr2 = ptr + 1; ptr2 < S; ptr2++) {
			if (main[ptr2] < main[min_indx]) {
				min_indx = ptr2;
			}
			std::swap(main[min_indx], main[ptr]);
		}
	}
}

double trimMean(vector<int>& arr) {
	selection_sort_(arr, arr.size());
	size_t deleted = (arr.size() / 10) / 2;
	double res = 0;
	for (size_t ptr = deleted; ptr < arr.size() - deleted; ptr++) {
		res += arr[ptr];
	}
	return res / (arr.size() - (2 * deleted));
}

int getLucky(string s, int k) {
	int res = 0;
	vector<int> data;
	for (char& ch : s) {
		data.push_back(ch - 25);
	}
	while (k-- > 0) {
		int data_tmp = accumulate(data.begin(), data.end(), 0);
		data.clear();
		while (data_tmp > 0) {
			int data_tmptmp = data_tmp % 10;
			data.push_back(data_tmptmp);
		}
	}
	return accumulate(data.begin(), data.end(), 0);
}

int maxRepeating(string& sequence, string& word) {
	int res = 0;
	string tmp = word;
	while (sequence.find(tmp) != std::string::npos) {
		cout << sequence.find(tmp) << endl;
		res++;
		tmp += word;
	}
	return res;
}

vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
	vector<int> res;
	auto splice([&res] (const vector<int>& num, const vector<int>& ind) {
		for (size_t I = 0; I < ind.size(); I++) {
			res.insert(res.begin() + ind[I], num[I]);
		}
		});
	splice(nums, index);
	return res;
}

bool isSorted(const vector<int>& nums) {
	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		if (nums[ptr] >= nums[ptr + 1]) {
			return false;
		}
	}
	return true;
}

pair<size_t, size_t> minmax(const vector<int>& nums) {
	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		if (nums[ptr] >= nums[ptr + 1]) {
			return {ptr, ptr + 1};
		}
	}
	return {-1,-1};
}

bool canBeIncreasing(vector<int>& nums) {
	int incr = 0;
	if (isSorted(nums)) {
		return true;
	} else {
		vector<int> tmp = nums;
		pair<size_t, size_t> removers = minmax(nums);
		if (removers.first != -1 && removers.second != -1) {
			tmp.erase(tmp.begin() + removers.first);
			if (isSorted(tmp)) {
				return true;
			} else {
				nums.erase(nums.begin() + removers.second);
				return isSorted(nums);
			}
		}
	}
	return false;
}

using namespace digcnv;

int uniqueMorseRepresentations(vector<string>& words) {
	vector<string> morze {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
	set<string> origin;
	for (const auto& word : words) {
		string translated;
		for (const char ch : word) {
			translated += morze[ch - 97];
		}
		origin.insert(translated);
	}
	return origin.size();
}

void simpMathProb(int fV) { //3N + 1 problem\HILLSTONE prob
	while (fV > 0) {
		if (fV % 2 != 0) {
			fV *= 3;
			fV++;
		} else {
			fV /= 2;
		}
		cout << fV << endl;
		system("PAUSE");
	}
}

bool isPerfectSquare(int num) {
	size_t sr = sqrt(num);
	return (sr * sr) == num;
}

string reverseStr(string s, int k) {
	int len = s.length();
	string builder = "";
	int left = 0;
	bool rev = false;
	for (int i = 0; i < len; i++) {
		if (i % k == 0) {
			string subStr = s.substr(left, i - left);
			if (rev) {
				reverse(subStr.begin(), subStr.end());
			}
			builder += subStr;
			left = i;
			rev = !rev;
		}
	}
	string subStr = s.substr(left, len - left);
	if (rev) {
		reverse(subStr.begin(), subStr.end());
	}
	builder += subStr;
	return builder;
}

TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr) {
		return root;
	}
	TreeNode* tmp_root = root;
	TreeNode* trav = root;
	std::queue<TreeNode*> hsh;
	hsh.push(trav);

	while (!hsh.empty()) {
		TreeNode* node = hsh.front();
		hsh.pop();


		if (node->left != nullptr && node->right == nullptr) {
			TreeNode* tmp = node->left;
			node->left = nullptr;
			node->right = tmp;
			hsh.push(node->right);
			continue;
		}
		if (node->left == nullptr && node->right != nullptr) {
			TreeNode* tmp = node->right;
			node->right = nullptr;
			node->left = tmp;
			hsh.push(node->left);
			continue;
		}
		if (node->left != nullptr && node->right != nullptr) {
			TreeNode* tmp = node->left;
			node->left = node->right;
			node->right = tmp;
			hsh.push(node->left);
			hsh.push(node->right);
			continue;
		}
	}
	return tmp_root;
}

bool stoneGame(vector<int>& piles) {
	int stones_all = std::accumulate(piles.begin(), piles.end(), 0);
	int summ_Ale = 0;
	int summ_Lee = 0;
	while (!piles.empty()) {
		if (piles[0] > piles[piles.size() - 1]) {
			summ_Ale += piles[0];
			stones_all -= piles[0];
			piles.erase(piles.begin());
		} else {
			summ_Ale += piles[piles.size() - 1];
			stones_all -= piles[piles.size() - 1];
			piles.erase(piles.begin() + piles.size() - 1);
		}
		if (piles[0] > piles[piles.size() - 1]) {
			summ_Lee += piles[0];
			stones_all -= piles[0];
			piles.erase(piles.begin());
		} else {
			summ_Lee += piles[piles.size() - 1];
			stones_all -= piles[piles.size() - 1];
			piles.erase(piles.begin() + piles.size() - 1);
		}
		if (summ_Ale > stones_all / 2) {
			return true;
		}
	}
	return false;
}

int main() {
	TreeNode* test = new TreeNode(1);
	test->left = new TreeNode(2);
	invertTree(test);
	return 0;
}




 