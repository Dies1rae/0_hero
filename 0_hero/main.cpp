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

using namespace std;

bool containsDuplicate(vector<int>& nums) {
    if(nums.size() == 0 || nums.empty()){
        return 0;
    }

    std::sort(nums.begin(), nums.end());
    for(size_t a = 0; a + 1 < nums.size(); a ++){
        if(nums[a] == nums[a+1]){
            return 1;
        }
    }
    return 0;
}

int maxProfit(vector<int>& prices) {
	bool zero = false;
	
	for (size_t ptr = 0; ptr + 1 < prices.size(); ptr ++) {
		if (prices[ptr] > prices[ptr + 1]) {
			zero = true;
		} else {
			
			zero = false;
			break;
		}
	}
	if (zero) {
		return 0;
	}

	int profit = 0;
	int min_prof = prices[0];
	for (size_t ptr = 0; ptr < prices.size(); ptr++) {
		if (prices[ptr] < min_prof) {
			min_prof = prices[ptr];
		}

		if (prices[ptr] - min_prof > profit) {
			profit = prices[ptr] - min_prof;
		}
	}
	return profit;
}

vector<vector<int>> Pascal_Triangle(int numRows) {
	vector<vector<int>> res;
	size_t sides = 1;
	for (size_t ptr = 0; ptr < numRows; ptr++) {
		vector<int> tmp;
		for (size_t ptr_one = 0; ptr_one < ptr; ptr_one++) {
			if (ptr == 0 || ptr_one == 0) {
				sides = 1;
			} else {
				sides = sides * (ptr - ptr_one + 1) / ptr_one;
			}
			tmp.push_back(sides);
		}
		tmp.push_back(1);
		res.push_back(tmp);
	}
	return res;
}

vector<int> getRow(int rowIndex) {
	return Pascal_Triangle(rowIndex + 1)[rowIndex];
}

int majorityElement(vector<int>& nums) {
	map<int, int> res;
	
	for (const int num : nums) {
		res[num]++;
	}

	auto pr = std::max_element
	(
		std::begin(res), std::end(res),
		[](const std::pair<int,int>& p1, const std::pair<int, int>& p2) {
			return p1.second < p2.second;
		}
	);

	return pr->first;
}

void moveZeroes(vector<int>& nums) {
	for (size_t ctr = 0; ctr < nums.size(); ctr++) {
		if (nums[ctr] == 0) {
			for (size_t ctr_n = ctr + 1; ctr_n < nums.size(); ctr_n++) {
				if (nums[ctr_n] != 0) {
					std::swap(nums[ctr], nums[ctr_n]);
					break;
				}
			}
		} else {
			continue;
		}
	}
}

int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
	int res = 0;
	if (ruleKey == "color") {
		for (size_t dev = 0; dev < items.size(); dev++) {
			if (items[dev][1] == ruleValue) {
				res++;
			}
		}
	}
	if (ruleKey == "type") {
		for (size_t dev = 0; dev < items.size(); dev++) {
			if (items[dev][0] == ruleValue) {
				res++;
			}
		}
	}
	if (ruleKey == "name") {
		for (size_t dev = 0; dev < items.size(); dev++) {
			if (items[dev][2] == ruleValue) {
				res++;
			}
		}
	}
	return res;
}

int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
	int res = INT_MAX;
	size_t pos = -1;
	for (size_t ptr = 0; ptr < points.size(); ptr++) {
		if (x == points[ptr][0] || y == points[ptr][1]) {
			int tmp = std::abs(points[ptr][0] - x) + std::abs(points[ptr][1] - y);
			if (tmp < res) {
				res = tmp;
				pos = ptr;
			}
		}
	}
	return pos;
}

int minOperations(const string& s) {
	if (s.size() == 1) {
		return 0;
	}
	int ctr_s = 0;
	int ctr_b = 0;
	for (size_t ptr = 0; ptr + 1 < s.size(); ptr += 2) {
		if (s[ptr] == '1') {
			if (s[ptr + 1] == '1') {
				ctr_s++;
			}
		}
		if (s[ptr] == '0') {
			ctr_s++;
			if (s[ptr + 1] == '1') {
				ctr_s++;
			}
		}

		if (s[ptr] == '1') {
			ctr_b++;
			if (s[ptr + 1] == '0') {
				ctr_b++;
			}
		}
		if (s[ptr] == '0') {
			if (s[ptr + 1] == '0') {
				ctr_b++;
			}
		}
	}
	if (s.size() % 2 != 0) {
		if (s[s.size() - 1] == '1') {
			ctr_b++;
		}
		if (s[s.size() - 1] == '0') {
			ctr_s++;
		}
	}
	return ctr_s < ctr_b ? ctr_s : ctr_b;
}

int sumOfUnique(vector<int>& nums) {
	map<int, int> res;
	int ctr = 0;
	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
		res[nums[ptr]] += 1;
	}
	for (const auto& [elem, ct] : res) {
		if (ct == 1) {
			ctr += elem;
		}
	}
	return ctr;
}

int countBalls(int lowLimit, int highLimit) {
	map<int, int> res;
	int ctr = -1;
	for (int l = lowLimit; l <= highLimit; l++) {
		int box_num = 0;
		int tmp_ptr = l;
		while (tmp_ptr > 0) {
			box_num = box_num + (tmp_ptr % 10);
			tmp_ptr = tmp_ptr / 10;
		}
		res[box_num] = res[box_num] + 1;
	}
	for (const auto& [box_num, balls_ctr] : res) {
		if (ctr < balls_ctr) {
			ctr = balls_ctr;
		}
	}
	return ctr;
}

int largestAltitude(vector<int>& gain) {
	int hight = 0;
	for (size_t ptr = 0; ptr < gain.size(); ptr++) {
		int tmp = 0;
		for (size_t ptr_prev = 0; ptr_prev <= ptr; ptr_prev++) {
			tmp += gain[ptr_prev];
		}
		if (hight < tmp) {
			hight = tmp;
		}
	}
	return hight;
}

int maximumWealth(vector<vector<int>>& accounts) {
	int health_max = 0;
	for (size_t ptr = 0; ptr < accounts.size(); ptr++) {
		int helth_tmp = std::accumulate(accounts[ptr].begin(), accounts[ptr].end(), 0);
		if (helth_tmp > health_max) {
			health_max = helth_tmp;
		}
	}
	return health_max;
}

vector<int> decrypt(vector<int>& code, int k) {
	vector<int> res(code.size());
	std::fill(res.begin(), res.end(), 0);
	if (k == 0) {
		return res;
	}

	if (k > 0) {
		for (size_t ptr = 0; ptr < code.size(); ptr++) {
			int next_elem = ptr + 1;
			int sum = 0;
			int pos = 0;
			while (pos < k) {
				sum += code[next_elem % code.size()];
				pos++;
				next_elem++;
			}

			res[ptr] = sum;
		}
	} else {
		reverse(code.begin(), code.end());
		k *= -1;
		for (size_t ptr = 0; ptr < code.size(); ptr++) {
			int next_elem = ptr + 1;
			int sum = 0;
			int pos = 0;
			while (pos < k) {
				sum += code[next_elem % code.size()];
				pos++;
				next_elem++;
			}

			res[ptr] = sum;
		}
		reverse(res.begin(), res.end());
	}
	return res;
}

string mergeAlternately(string word1, string word2) {
	string res;
	auto w1_ = word1.begin(), w2_ = word2.begin();
	while (w1_ != word1.end() || w2_ != word2.end()) {
		if (w1_ != word1.end()) {
			res += *w1_;
			w1_++;
		}
		if (w2_ != word2.end()) {
			res += *w2_;
			w2_++;
		}
	}
	return res;
}

bool buddyStrings(string A, string B) {
	if (A.size() != B.size()) {
		return 0;
	}
	string tmp_sa = A;
	string tmp_sb = B;
	sort(tmp_sa.begin(), tmp_sa.end());
	sort(tmp_sb.begin(), tmp_sb.end());
	if (tmp_sa != tmp_sb) {
		return 0;
	}
	set<char> tmp_a;
	for (auto c : A) {
		tmp_a.insert(c);
	}
	if (A == B && tmp_a.size() == A.size()) {
		return 0;
	} else {
		int cnt = 0;
		for (size_t ptr = 0; ptr < A.size(); ptr++) {
			if (A[ptr] != B[ptr]) {
				cnt++;
				if (cnt == 3) {
					return 0;
				}
			}
		}
	}
	
	return 1;
}

int romanToInt(string s) {
	if (s.empty()) {
		return 0;
	}
	map<char, int> romanic{ {'I', 1}, {'V', 5}, {'X', 10},  {'L', 50},  {'C', 100},  {'D', 500},  {'M', 1000} };
	int res = 0;
	for (size_t ptr = 0; ptr < s.size(); ptr ++) {
		if (romanic[s[ptr]] < romanic[s[ptr + 1]]) {
			res += romanic[s[ptr + 1]] - romanic[s[ptr]];
			ptr++;
		} else {
			res += romanic[s[ptr]];
		}
	}
	return res;
}

static string bin(unsigned n) {
	string res;
	unsigned i;
	for (i = 1 << 31; i > 0; i = i / 2) {
		(n & i) ? res += '1' : res += '0';
	}
	return res;
}

struct bin_comparator {
	bool operator() (const int lhs, const int rhs) const {
		int ctr_lhs = 0;
		int ctr_rhs = 0;
		for (const auto& bit : bin(lhs)) {
			if (bit == '1') {
				ctr_lhs++;
			}
		}
		for (const auto& bit : bin(rhs)) {
			if (bit == '1') {
				ctr_rhs++;
			}
		}
		if (ctr_lhs == ctr_rhs) {
			return lhs < rhs;
		} else {
			return ctr_lhs < ctr_rhs;
		}
	}
};

vector<int> sortByBits(vector<int>& arr) {
	std::sort(arr.begin(), arr.end(), bin_comparator());
	return arr;
}

int diagonalSum(vector<vector<int>>& mat) {
	if (mat.empty()) {
		return 0;
	}
	int res = 0;
	for (size_t ptr = 0; ptr < mat.size(); ptr++) {
		for (size_t ptr1 = 0; ptr1 < mat[ptr].size(); ptr1++) {
			if (ptr == ptr1) {
				res += mat[ptr][ptr1];
				continue;
			}
			if (ptr + ptr1 == mat[ptr].size() - 1) {
				res += mat[ptr][ptr1];
				continue;
			}
		}
	}

	return res;
}

//
//bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
//	if (nums.size() <= 1 || t < 0 || k < 0) {
//		return 0;
//	}
//	map<long long, long long> hash_;
//	size_t n = nums.size();
//
//	for (size_t ptr = 0; ptr <n; ptr++) {
//		int basic = floor(1.0 * nums[ptr] / ((long long)t + 1));
//		if (hash_.count(basic)) {
//			return 1;
//		} else if (hash_.count(basic + 1) && (hash_[basic + 1] - nums[ptr] <= t)) {
//			return 1;
//		} else if (hash_.count(basic - 1) && (-hash_[basic - 1] + nums[ptr] <= t)) {
//			return 1;
//		} else {
//			hash_[basic] = nums[ptr];
//			if (size(hash_) > k) {
//				int tmp_bas = floor(1.0 * nums[ptr - k] / ((long long)t + 1));
//				hash_.erase(tmp_bas);
//			}
//		}
//
//	}
//	
//	return 0;
//}

struct cmp {
	bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const {
		return lhs.second == rhs.second;
	}
};
bool containsnearbyalmostduplicate(vector<int>& nums, int k, int t) {
	if (nums.size() <= 1 || t < 0) {
		return 0;
	}
	map<int, int> hash_;
	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
		for (size_t ptr1 = ptr + 1; ptr1 < nums.size(); ptr1++) {
			if (nums[ptr] == nums[ptr1]) {
				hash_[ptr] = nums[ptr];
				hash_[ptr1] = nums[ptr];
			}
		}
	}

	vector<std::pair<int, int>> tmp_vec;
	tmp_vec.reserve(hash_.size());
	std::for_each(hash_.begin(), hash_.end(), [&tmp_vec](const std::map<int, int>::value_type& p) { tmp_vec.push_back({ p.first, p.second }); });
	std::sort(tmp_vec.begin(), tmp_vec.end(), cmp());

	auto pt_first = tmp_vec.begin();
	auto pt_second = ++tmp_vec.begin();

	while (pt_second != tmp_vec.end()) {
		if (pt_first->second == pt_second->second) {
			if ((std::abs(pt_second->second - pt_first->second) <= t) && (std::abs(pt_second->first - pt_first->first) <= k)) {
				return 1;
			}
			pt_first++;
			pt_second++;
		} else {
			pt_first++;
			pt_second++;
		}
	}
	for (const auto& [pos, elem] : tmp_vec) {
		cout << "POSITION: " << pos << " ELEM: " << elem << endl;
	}
	return 0;
}


int numIdenticalPairs(vector<int>& nums) {
	int ctr = 0;
	map <int, int> res;
	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
		res[nums[ptr]]++;
	}
	for (const auto& [num, ctrs] : res) {
		if (ctrs > 1) {
			ctr += ctrs * (ctrs - 1) / 2;
		}
	}
	return ctr;
}

int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
	if (arr.size() < 3) {
		return 0;
	}
	int ctr = 0;
	for (size_t i = 0; i < arr.size(); i ++) {
		for (size_t j = i + 1; j < arr.size(); j++) {
			for (size_t k = j + 1; k < arr.size(); k++) {
				int a_ = std::abs(arr[i] - arr[j]);
				int b_ = std::abs(arr[j] - arr[k]);
				int c_ = std::abs(arr[i] - arr[k]);
				if (a_ <= a && b_ <= b && c_ <= c) {
					ctr++;
				}
			}
		}
	}
	return ctr;
}

class Solution {
public:
	struct ListNode {
		int val;
		ListNode* next;
		ListNode(int x) : val(x), next(NULL) {}

	};

	Solution() :head(NULL) {}

	Solution(const int val) {
		head = new ListNode(val);
	}

	void deleteNode(ListNode* node) {
		while (node != NULL && node->next != NULL) {
			if (node->next == node) {
				node->next->val = node->next->next->val;
				node->next = node->next->next;
				return;
			}
		}
	}

private:
	ListNode* head;
};

int findKthPositive(vector<int>& arr, int k) {
	for (int i = 0; i < arr.size(); i++) {
		int x = arr[i] - (i + 1);
		if (x >= k)
			return i + k;
	}
	return arr.size() + k;
}

int sumOddLengthSubarrays(vector<int>& arr) {
	if (arr.empty()) {
		return 0;
	}
	int res = 0;
	std::count_if(arr.begin(), arr.end(), [&res](const int& val) { return res += val; });
	if (arr.size() < 3) {
		return res;
	}
	size_t ctr = 2;
	while (ctr < arr.size()) {
		for (size_t ptr = 0; ptr + ctr < arr.size(); ptr++) {
			size_t tmp_iter = ptr;
			while (tmp_iter != ptr + ctr + 1) {
				res += arr[tmp_iter];
				tmp_iter++;
			}
		}
		ctr += 2;
	}
	return res;
}

vector<string> stringMatching(vector<string>& words) {
	set<string> res;
	for (size_t ptr = 0; ptr< words.size(); ptr++) {
		for (size_t ptr1 = 0; ptr1 < words.size(); ptr1++) {
			if (words[ptr].find(words[ptr1]) != std::string::npos && words[ptr1].size() < words[ptr].size()) {
				res.insert(words[ptr1]);
			}
		}
	}
	return {res.begin(), res.end()};
}


struct TreeNode {
	TreeNode() = default;
	TreeNode(int data) :val(data) {
		TreeNode* l_leaf = NULL;
		TreeNode* r_leaf = NULL;
	};

	int val = 0;
	TreeNode* l_leaf = NULL;
	TreeNode* r_leaf = NULL;
};

TreeNode* NewNode(int data) {
	TreeNode* res = new TreeNode(data);
	return res;
}

vector<TreeNode *> Create_TreeNodeSet_From_File(const string& path) {
	ifstream src(path, ios::binary);
	vector<TreeNode*> data;
	while (src.good()) {
		int val;
		src >> val;
		data.push_back(NewNode(val));
	}
	src.close();
	return data;
}

TreeNode* create_balanced_tree(vector<TreeNode*>& nodes, int pos_start, int pos_end) {
	if (pos_start > pos_end) {
		return NULL;
	}
	int pos_mid = (pos_start + pos_end) / 2;
	TreeNode* root = nodes[pos_mid];
	root->l_leaf = create_balanced_tree(nodes, pos_start, pos_mid - 1);
	root->r_leaf = create_balanced_tree(nodes, pos_mid + 1, pos_end);

	return root;
}

//GOVNO NA PALKE
void avl_push(int val, TreeNode** root) {
	if ((*root) == NULL) {
		(*root) = new TreeNode(val);
		return;
	}
	if (val > (*root)->val) {
		avl_push(val, &(*root)->r_leaf);
		return;
	} else {
		avl_push(val, &(*root)->l_leaf);
		return;
	}
}

TreeNode* create_ideal_balanced_tree(vector<TreeNode*> nodes) {
	if (nodes.empty()) {
		return new TreeNode();
	}
	TreeNode* root = NULL;
	for (TreeNode* node : nodes) {
		avl_push(node->val, &root);
	}
	return root;
}

void PreOrder_Tree(TreeNode* root) {
	if (root == NULL) {
		return;
	}
	cout << root->val << " -> ";
	PreOrder_Tree(root->l_leaf);
	PreOrder_Tree(root->r_leaf);
}

void print_tree(TreeNode* node, int start = 0) {
	if (node == NULL) {
		return;
	} else {
		print_tree(node->l_leaf, ++start);
		for (int ptr = 0; ptr < start; ptr++) {
			cout << '|';
		}
		cout << node->val << endl;
		start--;
	}
	print_tree(node->r_leaf, ++start);
}

int floid_tortoise_hare(vector<int>& elems) {
	int res = INT_MIN;
	int tortoise = elems[0];
	int hare = elems[0];
	
	while (true) {
		if (tortoise > elems.size() - 1) {
			return res;
		}
		tortoise = elems[tortoise];
		hare = elems[elems[hare]];
		if (tortoise == hare) {
			break;
		}
	}
	
	tortoise = elems[0];
	while (tortoise != hare) {
		tortoise = elems[tortoise];
		hare = elems[hare];
	}
	res = tortoise;
	return res;
}

int main() {
	vector<int> arr{ 9, 8, 9, 7, 6, 5, 2, 4, 3, 1 };
	cout << floid_tortoise_hare(arr) << endl;
	return 0;
}

