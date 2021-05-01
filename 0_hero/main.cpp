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
#include <memory>
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

struct point {
	point() = default;
	point(const double x_, const double y_) : x(x_), y(y_) {};
	point(double&& x_, double&& y_){
		std::swap(this->x, x_);
		std::swap(this->y, y_);
	};

	double x = 0;
	double y = 0;
};

point create_point(double x, double y) {
	point* tmp_pnt = new point(x, y);
	return *tmp_pnt;
}

vector<point> generate_points(size_t size) {
	vector<point> prescision;

	for (size_t ptr = 0; ptr < size; ptr++) {
		double x_ = ((double)rand() / (RAND_MAX));
		double y_ = ((double)rand() / (RAND_MAX));
		prescision.push_back(create_point(std::move(x_), std::move(y_)));
	}

	return prescision;
}

double calculate_pi(vector<point> points_) {
	int before_one = 0;
	int total_one = 0;
	double PI = 0.0;
	for (const auto point : points_) {
		if (((point.x * point.x) + (point.y * point.y)) < 1.0) {
			before_one += 1;
		}
		total_one += 1;
	}

	PI = 4.0 * (before_one) / (total_one);
	cout << before_one << " " << total_one << endl;
	return PI;
}


int compare_elem(vector<int>::iterator begin, vector<int>::iterator end) {
	int res = *begin;
	++begin;
	while (begin <= end) {
		res += *begin;
		++ begin;
	}
	return res;
}

vector<int> runningSum(vector<int>& nums) {
	vector<int> res;
	auto iter_first = nums.begin();
	auto iter_second = nums.begin();

	while (iter_first < nums.end()) {
		int elem = compare_elem(iter_second, iter_first);
		res.push_back(elem);
		++iter_first;
	}

	return res;
}

int xorOperation(int n, int start) {
	if (n == 1) {
		return start;
	}
	vector<int> arr;
	arr.resize(n);
	for (size_t ptr = 0; ptr < n; ptr++) {
		arr[ptr] = start + 2 * ptr;
	}
	int res = 0;
	for (const auto& elem : arr) {
		res = res ^ elem;
	}
	return res;
}

int maximumProduct(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());
    int size = nums.size();
    int first = nums[0] * nums[1] * nums[size - 1];
    int second = nums[size - 1] * nums[size - 2] * nums[size - 3];
    return first > second ? first : second;
}

int digits_num(int elem) {
	int res = 0;
	while (elem) {
		elem /= 10;
		res++;
	}
	return res;
}

int findNumbers(vector<int>& nums) {
	int even_ctr = 0;
	for (auto elem : nums) {
		if (digits_num(elem) % 2 == 0 && digits_num(elem) > 0) {
			even_ctr++;
		}
	}
	return even_ctr;
}

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
	vector<bool> res(candies.size());
	int max = *std::max_element(candies.begin(), candies.end());
	for (size_t ptr = 0; ptr < candies.size(); ptr ++) {
		if (candies[ptr] + extraCandies >= max) {
			res[ptr] = true;
		} else {
			res[ptr] = false;
		}
	}
	return res;
}

bool isOneBitCharacter(vector<int>& bits) {
	if (bits[bits.size() - 1] == 1) {
		return false;
	}
	for (size_t ptr = 0; ptr < bits.size(); ptr++) {
		if (ptr == bits.size() - 1) {
			return true;
		}
		if (bits[ptr] == 1) {
			ptr++;
		}
	}

	return false;
}

struct freqcmp {
	bool operator()(const pair<char, int>& lhs, const pair<char, int>& rhs) const     {
		return lhs.second < rhs.second;
	}
};



int getMin(map<char, int> mymap) {
	std::pair<char, int> min = *min_element(mymap.begin(), mymap.end(), freqcmp());
	return min.second;
}

int maxNumberOfBalloons(string text) {
	if (text.size() < 7) {
		return 0;
	}

	map<char, int> naebolko{ {'b', 0}, {'a', 0}, {'l', 0}, {'o', 0}, {'n', 0} };
	for (const auto& c : text) {
		if (naebolko.find(c) != naebolko.end()) {
			naebolko.at(c)++;
		}
	}

	naebolko['l'] /= 2;
	naebolko['o'] /= 2;

	return getMin(naebolko);
}

vector<string> separate_spaces(string& text) {
	vector<string> res;
	string word;
	for (size_t ptr = 0; ptr < text.size(); ptr++) {
		if (text[ptr] == 32) {
			res.push_back(word);
			word.clear();
		} else {
			word += text[ptr];
		}
	}
	res.push_back(word);
	return res;
}

vector<string> uncommonFromSentences(string A, string B) {
	vector<string> res;
	map<string, int> ctr_map;
	for (auto& w : separate_spaces(A)) {
		ctr_map[w] ++;
	}
	for (auto& w : separate_spaces(B)) {
		ctr_map[w] ++;
	}
	for (const auto [word, ctr] : ctr_map) {
		if (ctr == 1) {
			res.push_back(word);
		}
	}
	return res;
}

vector<string> findOcurrences(string text, string first, string second) {
	vector<string> res;
	vector<string> separate = separate_spaces(text);
	for (size_t ptr = 0; ptr + 2 < separate.size(); ptr++) {
		if (separate[ptr] == first && separate[ptr + 1] == second) {
			res.push_back(separate[ptr + 2]);
		}
	}

	return res;
}

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};


// BAD DESIGN
int getDecimalValue(ListNode* head) {
	int res = 0;
	vector<int>bytes;
	while (head != nullptr) {
		bytes.push_back(head->val);
		head = head->next;
	}

	for (int ptr_end = bytes.size() - 1, ptr_begin = 0; ptr_end > -1; ptr_end--, ptr_begin++) {
		res += bytes[ptr_begin] * (1 << ptr_end);
	}

	return res;
}

int getDecimalValue_2(ListNode* head) {
	ListNode* cur = head;
	int len = 0;
	while (cur) {
		len++;
		cur = cur->next;
	}

	cur = head;
	int res = 0;
	len = len - 1;
	while (cur) {
		res += cur->val * (1 << (len--));
		cur = cur->next;
	}
	return res;
}
//-----------

int maxPower(string s) {
	int max = 1, tmp_max = 1;

	for (size_t ptr = 0; ptr + 1 < s.size(); ptr++) {
		if (s[ptr] == s[ptr + 1]) {
			tmp_max++;
		}
		if (s[ptr] != s[ptr + 1]) {
			if (tmp_max >= max) {
				max = tmp_max;
			}
			tmp_max = 1;
		}
	}

	if (tmp_max >= max) {
		max = tmp_max;
	}

	return max;
}

vector<string> commonChars(vector<string>& A) {
	vector<string> res;
	int first[26];
	int tmp[26];
	fill(first, first + 26, 1000);
	for (const auto& str : A) {
		fill(tmp, tmp + 26, 0);
		for (size_t ptr = 0; ptr < str.size(); ptr++) {
			tmp[str[ptr] - 'a'] += 1;
		}
		for (size_t ptr = 0; ptr < 26; ptr++) {
			first[ptr] = min(first[ptr], tmp[ptr]);
		}
	}
	for (size_t ptr = 0; ptr < 26; ptr++) {
		while (first[ptr]) {
			string tmp{ (char)('a' + ptr) };
			res.push_back(tmp);
			first[ptr]--;
		}
	}
	return res;
}

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
	vector<int>res;
	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
		int tmp_ctr = 0;
		for (size_t ptr1 = 0; ptr1 < nums.size(); ptr1++) {
			if (nums[ptr] > nums[ptr1] && ptr != ptr1) {
				tmp_ctr++;
			}
		}
		res.push_back(tmp_ctr);
	}
	return res;
}

bool isHappy(int n) {
	if (n == 1) {
		return 1;
	}
	if (n == 2) {
		return 0;
	}

	set<int> hsh;

	while (n != 1) {
		int tmp_n = 0;
		
		if (hsh.find(n) != hsh.end()) {
			return 0;
		}
		hsh.insert(n);
		while (n > 0) {
			tmp_n += pow((n % 10), 2);
			n /= 10;
		}
		
		n = tmp_n;
	}
	return 1;
}

bool canMakeArithmeticProgression(vector<int>& arr) {
	std::sort(arr.begin(), arr.end());
	int diff = arr[1] - arr[0];
	for (size_t ptr = 0; ptr + 1 < arr.size(); ptr++) {
		if (arr[ptr + 1] - arr[ptr] != diff) {
			return false;
		}
	}
	return true;
}

double average(vector<int>& salary) {
	std::sort(salary.begin(), salary.end());
	double avr = 0.0;
	for (size_t ptr = 1; ptr < salary.size() - 1; ptr++) {
		avr += salary[ptr];
	}
	return (avr / (double)(salary.size() - 2));
}

string restoreString(string s, vector<int>& indices) {
	map<int, char> order;
	for (size_t ptr = 0; ptr < indices.size(); ptr++) {
		order[indices[ptr]] = s[ptr];
	}
	s.clear();
	for (const auto& [pos, ch] : order) {
		s += ch;
	}
	return s;
}
string restoreString_1(string s, vector<int>& indices) {
	string res(s);
	for (size_t ptr = 0; ptr < indices.size(); ptr++) {
		res[indices[ptr]] = s[ptr];
	}
	return res;
}


ListNode* removeElements(ListNode* head, int val) {
	if (head == nullptr) {
		return {};
	}
	ListNode* new_root = head;
	ListNode* head_next = head->next;
	
	while (head_next != nullptr) {
		if (head_next->val == val) {
			head->next = head_next->next;
			head_next = head->next;
			continue;
		}
		head = head->next;
		head_next = head_next->next;
	}
	if (new_root->val == val) {
		return new_root = new_root->next;
	}
	return new_root;
}

void print_node(ListNode* node) {
	if (node == NULL) {
		cout << "EMPTY" << endl;
	} else {
		while (node != nullptr){
			cout << node->val << " ";
			node = node->next;
		}
		cout << "FIN" << endl;
		cout << endl;
	}
}

vector<string> buildArray(vector<int>& target, int n) {
	vector<string> moving;
	for (int ptr = 0, ctr = 1; ptr < target.size(); ptr++, ctr++) {
		if (ctr == target[ptr]) {
			moving.push_back("Push"s);
		} else {
			ptr--;
			moving.push_back("Push"s);
			moving.push_back("Pop"s);
		}
	}

	return moving;
}

vector<int> decode(vector<int>& encoded, int first) {
	vector<int> decoded;
	decoded.resize(encoded.size() + 1);
	decoded[0] = first;
	for (size_t ptr = 0; ptr < encoded.size(); ptr++) {
		decoded[ptr + 1] = encoded[ptr] xor decoded[ptr];
	}
	return decoded;
}

bool isPalindrome(int x) {
	vector<int>res;
	if (x < 0) {
		return false;
	}
	if (x == 0) {
		return true;
	}
	while (x >= 10) {
		int tmp = x % 10;
		x /= 10;
		res.push_back(tmp);
	}
	res.push_back(x);
	for (size_t btr = 0, ept = res.size() - 1; btr < res.size() / 2; btr++, ept --) {
		if (res[btr] != res[ept]) {
			return false;
		}
	}
	return true;
}

bool isPalindrome_1(int x) {
	if (x < 0) {
		return false;
	}
	long revX = 0;
	long tmp_val = x;
	while (tmp_val > 0) {
		revX = revX * 10 + tmp_val % 10;
		tmp_val /= 10;
	}
	return x == revX ? true : false;
}

bool isPalindrome(ListNode* head) {
	vector<int> vec;
	while (head != nullptr) {
		vec.push_back(head->val);
		head = head->next;
	}
	for (size_t btr = 0, ept = vec.size() - 1; btr < vec.size() / 2; btr++, ept--) {
		if (vec[btr] != vec[ept]) {
			return false;
		}
	}
	return true;
}

bool checkIfPangram(string sentence) {
	set<char> alphabet = { sentence.begin(), sentence.end() };
	return alphabet.size() >= 26 ? true : false;
}

void delete_restricted(string& number) {
	for (size_t ptr = 0; ptr < number.size(); ptr++) {
		if (number[ptr] == 32 || number[ptr] == '-') {
			number.erase(ptr, 1);
			ptr--;
		}
	}
}

string reformatNumber(string number) {
	delete_restricted(number);
	if (number.size() < 4) {
		return number;
	}
	size_t tel_size = number.size();
	size_t ptr = 0;

	while (tel_size > 0) {
		if (tel_size > 4) {
			ptr += 3;
			number.insert(ptr, "-");
			ptr += 1;
			tel_size -= 3;
		} else if (tel_size == 4) {
			ptr += 2;
			number.insert(ptr, "-");
			ptr += 1;
			tel_size -= 2;
		} else {
			break;
		}
	}
	return number;
}

bool isVowel(char c) {
	return (c == 'a' || c == 'A' || c == 'e' ||	c == 'E' || c == 'i' || c == 'I' ||
		c == 'o' || c == 'O' || c == 'u' ||	c == 'U');
}
//!!!!!!!!!!!!!!
string reverseVowels(string s) {
	size_t beg = 0;
	size_t end = s.size() - 1;

	while (beg < end) {
		if (isVowel(s[beg]) && isVowel(s[end])) {
			std::swap(s[beg++], s[end--]);
		} else if (!isVowel(s[beg])) {
			beg++;
		} else if (!isVowel(s[end])) {
			end--;
		}
	}
	return s;
}
//!!!!!!!!!!!!!!

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
	} else {
		print_tree(node->left, ++start);
		for (int ptr = 0; ptr < start; ptr++) {
			cout << '|';
		}
		cout << node->val << endl;
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
	return 1 + max(height_subtree(node->left), height_subtree(node->right));
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
	cout << root->val << " ";
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
	} else {
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
	stack<TreeNode*> hsh;
	//RETURNED LIST
	TreeNode* head_ = nullptr;
	//CURRENT POSITION
	TreeNode* curr_ = nullptr;
	//TMP POSITION
	TreeNode* tmp_ = root;

	//GET ALL LEFT IN A HASH
	while (tmp_ != nullptr)	{
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

void clear_zeros(string& num) {
	if (num.size() == 1) {
		return;
	}
	while (num[0] == 48) {
		num.erase(0, 1);
	}
	if (!std::isdigit(num[0])) {
		num += '0';
	}
}

int numDifferentIntegers(string word) {
	set<string> strings_;
	string tmp_num;
	for (size_t ptr = 0; ptr < word.size(); ptr++) {
		if (word[ptr] >= '0' && word[ptr] <= '9') {
			tmp_num += word[ptr];
			if (ptr == word.size() - 1) {
				clear_zeros(tmp_num);
				strings_.insert(tmp_num);
				tmp_num.clear();
			}
		}
		if ((word[ptr] < '0' || word[ptr] > '9') && !tmp_num.empty()) {
			clear_zeros(tmp_num);
			strings_.insert(tmp_num);
			tmp_num.clear();
		}
	}

	return strings_.size();
}


//bad design
bool isAnagram(string s, string t) {
	std::sort(s.begin(), s.end());
	std::sort(t.begin(), t.end());
	return s == t;
}
//good design
bool isAnagram_1(string s, string t) {
	vector<int> c1(26, 0);
	for (char c : s) {
		c1[c - 'a'] ++;
	}
	for (char c : t) {
		c1[c - 'a'] --;
	}

	for (int i = 0; i < 26; ++i) {
		if (c1[i]) {
			return false;
		}
	}
	return true;
}

int totalMoney(int n) {
	int monday_pay = 1;
	int total_sum = 0;
	int weekend_ctr = 0;
	while (n > 0) {
		total_sum += monday_pay + weekend_ctr;
		weekend_ctr++;
		if (weekend_ctr == 7) {
			monday_pay += 1;
			weekend_ctr = 0;
		}
		n--;
	}

	return total_sum;
}

//Prototype design pattern

class dog {
public:
	explicit dog() = default;
	dog(string name) : name_(name) {
		this->age_ = 1;
	}
	dog(string name, size_t age) : name_(name), age_(age) {}

	void set_name(string name) {
		this->name_ = name;
	}
	void set_age(size_t age) {
		this->age_ = age;
	}
	string* name_mutable() {
		return &this->name_;
	}
	size_t* age_mutable() {
		return &this->age_;
	}
	virtual dog clone() const = delete;

	virtual void wow() {
		cout << "WOW WOW" << endl;
	}
private:
	string name_ = "";
	size_t age_ = 0;
};

class fight_dog: public dog {
public:
	explicit fight_dog() = default;
	fight_dog(string name) : name_(name) {
		this->age_ = 1;
		this->power_ = 1;
	}
	fight_dog(string name, size_t age) {
		this->name_  = name;
		this->age_ = age;
		this->power_ = 1;
	}
	fight_dog(string name, size_t age, size_t pow) : name_(name), age_(age), power_(pow) {}

	void set_pow(size_t pow) {
		this->power_ = pow;
	}
	
	size_t* power_mutable() {
		return &this->power_;
	}

	

	void wow() override {
		cout << "HEY MOTHERFUCKER! YOU BETTER RUN!" << endl;
	}

private:
	string name_ = "";
	size_t age_ = 0;
	size_t power_ = 0;
};

int tribonacci(int n) {
	int res = 0;
	vector<size_t> F_(41);
	F_[0] = 0;
	F_[1] = 1;
	F_[2] = 1;

	for (size_t ptr = 0; ptr < F_.size(); ptr++) {
		if (n == ptr) {
			return F_[ptr];
		}
		F_[ptr + 3] = F_[ptr] + F_[ptr + 1] + F_[ptr + 2];
	}
	return 0;
}

int maxAscendingSum(vector<int>& nums) {
	int max_asc = 0;
	int max_tmp = 0;
	if (nums.empty()) {
		return 0;
	}
	if (nums.size() == 1) {
		return nums[0];
	}
	for (size_t ptr = 1; ptr  < nums.size(); ptr++) {
		if (nums[ptr] > nums[ptr - 1]) {
			max_tmp += nums[ptr - 1];
			if (ptr == nums.size() - 1) {
				max_tmp += nums[ptr];
			}
		} else {
			max_tmp += nums[ptr - 1];
			max_asc = std::max(max_asc, max_tmp);
			max_tmp = 0;
		}
	}
	max_asc = std::max(max_asc, max_tmp);
	return max_asc;
}



int main() {
	TreeNode* root = new TreeNode(5);
	root->left = new TreeNode(3);
	root->right = new TreeNode(6);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->left->left->left = new TreeNode(1);
	root->right->right = new TreeNode(8);
	root->right->right->right = new TreeNode(9);
	root->right->right->left = new TreeNode(7);
	TreeNode* test = increasingBST_1(root);
	print_inorderBST(test);

	return 0;
}

 