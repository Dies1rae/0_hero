//bool containsDuplicate(vector<int>& nums) {
//	if (nums.size() == 0 || nums.empty()) {
//		return 0;
//	}
//
//	std::sort(nums.begin(), nums.end());
//	for (size_t a = 0; a + 1 < nums.size(); a++) {
//		if (nums[a] == nums[a + 1]) {
//			return 1;
//		}
//	}
//	return 0;
//}
//
//int maxProfit(vector<int>& prices) {
//	bool zero = false;
//
//	for (size_t ptr = 0; ptr + 1 < prices.size(); ptr++) {
//		if (prices[ptr] > prices[ptr + 1]) {
//			zero = true;
//		} else {
//
//			zero = false;
//			break;
//		}
//	}
//	if (zero) {
//		return 0;
//	}
//
//	int profit = 0;
//	int min_prof = prices[0];
//	for (size_t ptr = 0; ptr < prices.size(); ptr++) {
//		if (prices[ptr] < min_prof) {
//			min_prof = prices[ptr];
//		}
//
//		if (prices[ptr] - min_prof > profit) {
//			profit = prices[ptr] - min_prof;
//		}
//	}
//	return profit;
//}
//
//vector<vector<int>> Pascal_Triangle(int numRows) {
//	vector<vector<int>> res;
//	size_t sides = 1;
//	for (size_t ptr = 0; ptr < numRows; ptr++) {
//		vector<int> tmp;
//		for (size_t ptr_one = 0; ptr_one < ptr; ptr_one++) {
//			if (ptr == 0 || ptr_one == 0) {
//				sides = 1;
//			} else {
//				sides = sides * (ptr - ptr_one + 1) / ptr_one;
//			}
//			tmp.push_back(sides);
//		}
//		tmp.push_back(1);
//		res.push_back(tmp);
//	}
//	return res;
//}
//
//vector<int> getRow(int rowIndex) {
//	return Pascal_Triangle(rowIndex + 1)[rowIndex];
//}
//
//int majorityElement(vector<int>& nums) {
//	map<int, int> res;
//
//	for (const int num : nums) {
//		res[num]++;
//	}
//
//	auto pr = std::max_element
//	(
//		std::begin(res), std::end(res),
//		[](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
//			return p1.second < p2.second;
//		}
//	);
//
//	return pr->first;
//}
//
//void moveZeroes(vector<int>& nums) {
//	for (size_t ctr = 0; ctr < nums.size(); ctr++) {
//		if (nums[ctr] == 0) {
//			for (size_t ctr_n = ctr + 1; ctr_n < nums.size(); ctr_n++) {
//				if (nums[ctr_n] != 0) {
//					std::swap(nums[ctr], nums[ctr_n]);
//					break;
//				}
//			}
//		} else {
//			continue;
//		}
//	}
//}
//
//int countMatches(vector<vector<string>>& items, string ruleKey, string ruleValue) {
//	int res = 0;
//	if (ruleKey == "color") {
//		for (size_t dev = 0; dev < items.size(); dev++) {
//			if (items[dev][1] == ruleValue) {
//				res++;
//			}
//		}
//	}
//	if (ruleKey == "type") {
//		for (size_t dev = 0; dev < items.size(); dev++) {
//			if (items[dev][0] == ruleValue) {
//				res++;
//			}
//		}
//	}
//	if (ruleKey == "name") {
//		for (size_t dev = 0; dev < items.size(); dev++) {
//			if (items[dev][2] == ruleValue) {
//				res++;
//			}
//		}
//	}
//	return res;
//}
//
//int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
//	int res = INT_MAX;
//	size_t pos = -1;
//	for (size_t ptr = 0; ptr < points.size(); ptr++) {
//		if (x == points[ptr][0] || y == points[ptr][1]) {
//			int tmp = std::abs(points[ptr][0] - x) + std::abs(points[ptr][1] - y);
//			if (tmp < res) {
//				res = tmp;
//				pos = ptr;
//			}
//		}
//	}
//	return pos;
//}
//
//int minOperations(const string& s) {
//	if (s.size() == 1) {
//		return 0;
//	}
//	int ctr_s = 0;
//	int ctr_b = 0;
//	for (size_t ptr = 0; ptr + 1 < s.size(); ptr += 2) {
//		if (s[ptr] == '1') {
//			if (s[ptr + 1] == '1') {
//				ctr_s++;
//			}
//		}
//		if (s[ptr] == '0') {
//			ctr_s++;
//			if (s[ptr + 1] == '1') {
//				ctr_s++;
//			}
//		}
//
//		if (s[ptr] == '1') {
//			ctr_b++;
//			if (s[ptr + 1] == '0') {
//				ctr_b++;
//			}
//		}
//		if (s[ptr] == '0') {
//			if (s[ptr + 1] == '0') {
//				ctr_b++;
//			}
//		}
//	}
//	if (s.size() % 2 != 0) {
//		if (s[s.size() - 1] == '1') {
//			ctr_b++;
//		}
//		if (s[s.size() - 1] == '0') {
//			ctr_s++;
//		}
//	}
//	return ctr_s < ctr_b ? ctr_s : ctr_b;
//}
//
//int sumOfUnique(vector<int>& nums) {
//	map<int, int> res;
//	int ctr = 0;
//	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
//		res[nums[ptr]] += 1;
//	}
//	for (const auto& [elem, ct] : res) {
//		if (ct == 1) {
//			ctr += elem;
//		}
//	}
//	return ctr;
//}
//
//int countBalls(int lowLimit, int highLimit) {
//	map<int, int> res;
//	int ctr = -1;
//	for (int l = lowLimit; l <= highLimit; l++) {
//		int box_num = 0;
//		int tmp_ptr = l;
//		while (tmp_ptr > 0) {
//			box_num = box_num + (tmp_ptr % 10);
//			tmp_ptr = tmp_ptr / 10;
//		}
//		res[box_num] = res[box_num] + 1;
//	}
//	for (const auto& [box_num, balls_ctr] : res) {
//		if (ctr < balls_ctr) {
//			ctr = balls_ctr;
//		}
//	}
//	return ctr;
//}
//
//int largestAltitude(vector<int>& gain) {
//	int hight = 0;
//	for (size_t ptr = 0; ptr < gain.size(); ptr++) {
//		int tmp = 0;
//		for (size_t ptr_prev = 0; ptr_prev <= ptr; ptr_prev++) {
//			tmp += gain[ptr_prev];
//		}
//		if (hight < tmp) {
//			hight = tmp;
//		}
//	}
//	return hight;
//}
//
//int maximumWealth(vector<vector<int>>& accounts) {
//	int health_max = 0;
//	for (size_t ptr = 0; ptr < accounts.size(); ptr++) {
//		int helth_tmp = std::accumulate(accounts[ptr].begin(), accounts[ptr].end(), 0);
//		if (helth_tmp > health_max) {
//			health_max = helth_tmp;
//		}
//	}
//	return health_max;
//}
//
//vector<int> decrypt(vector<int>& code, int k) {
//	vector<int> res(code.size());
//	std::fill(res.begin(), res.end(), 0);
//	if (k == 0) {
//		return res;
//	}
//
//	if (k > 0) {
//		for (size_t ptr = 0; ptr < code.size(); ptr++) {
//			int next_elem = ptr + 1;
//			int sum = 0;
//			int pos = 0;
//			while (pos < k) {
//				sum += code[next_elem % code.size()];
//				pos++;
//				next_elem++;
//			}
//
//			res[ptr] = sum;
//		}
//	} else {
//		reverse(code.begin(), code.end());
//		k *= -1;
//		for (size_t ptr = 0; ptr < code.size(); ptr++) {
//			int next_elem = ptr + 1;
//			int sum = 0;
//			int pos = 0;
//			while (pos < k) {
//				sum += code[next_elem % code.size()];
//				pos++;
//				next_elem++;
//			}
//
//			res[ptr] = sum;
//		}
//		reverse(res.begin(), res.end());
//	}
//	return res;
//}
//
//string mergeAlternately(string word1, string word2) {
//	string res;
//	auto w1_ = word1.begin(), w2_ = word2.begin();
//	while (w1_ != word1.end() || w2_ != word2.end()) {
//		if (w1_ != word1.end()) {
//			res += *w1_;
//			w1_++;
//		}
//		if (w2_ != word2.end()) {
//			res += *w2_;
//			w2_++;
//		}
//	}
//	return res;
//}
//
//bool buddyStrings(string A, string B) {
//	if (A.size() != B.size()) {
//		return 0;
//	}
//	string tmp_sa = A;
//	string tmp_sb = B;
//	sort(tmp_sa.begin(), tmp_sa.end());
//	sort(tmp_sb.begin(), tmp_sb.end());
//	if (tmp_sa != tmp_sb) {
//		return 0;
//	}
//	set<char> tmp_a;
//	for (auto c : A) {
//		tmp_a.insert(c);
//	}
//	if (A == B && tmp_a.size() == A.size()) {
//		return 0;
//	} else {
//		int cnt = 0;
//		for (size_t ptr = 0; ptr < A.size(); ptr++) {
//			if (A[ptr] != B[ptr]) {
//				cnt++;
//				if (cnt == 3) {
//					return 0;
//				}
//			}
//		}
//	}
//
//	return 1;
//}
//
//int romanToInt(string s) {
//	if (s.empty()) {
//		return 0;
//	}
//	map<char, int> romanic{ {'I', 1}, {'V', 5}, {'X', 10},  {'L', 50},  {'C', 100},  {'D', 500},  {'M', 1000} };
//	int res = 0;
//	for (size_t ptr = 0; ptr < s.size(); ptr++) {
//		if (romanic[s[ptr]] < romanic[s[ptr + 1]]) {
//			res += romanic[s[ptr + 1]] - romanic[s[ptr]];
//			ptr++;
//		} else {
//			res += romanic[s[ptr]];
//		}
//	}
//	return res;
//}
//
//static string bin(unsigned n) {
//	string res;
//	unsigned i;
//	for (i = 1 << 31; i > 0; i = i / 2) {
//		(n & i) ? res += '1' : res += '0';
//	}
//	return res;
//}
//
//struct bin_comparator {
//	bool operator() (const int lhs, const int rhs) const {
//		int ctr_lhs = 0;
//		int ctr_rhs = 0;
//		for (const auto& bit : bin(lhs)) {
//			if (bit == '1') {
//				ctr_lhs++;
//			}
//		}
//		for (const auto& bit : bin(rhs)) {
//			if (bit == '1') {
//				ctr_rhs++;
//			}
//		}
//		if (ctr_lhs == ctr_rhs) {
//			return lhs < rhs;
//		} else {
//			return ctr_lhs < ctr_rhs;
//		}
//	}
//};
//
//vector<int> sortByBits(vector<int>& arr) {
//	std::sort(arr.begin(), arr.end(), bin_comparator());
//	return arr;
//}
//
//int diagonalSum(vector<vector<int>>& mat) {
//	if (mat.empty()) {
//		return 0;
//	}
//	int res = 0;
//	for (size_t ptr = 0; ptr < mat.size(); ptr++) {
//		for (size_t ptr1 = 0; ptr1 < mat[ptr].size(); ptr1++) {
//			if (ptr == ptr1) {
//				res += mat[ptr][ptr1];
//				continue;
//			}
//			if (ptr + ptr1 == mat[ptr].size() - 1) {
//				res += mat[ptr][ptr1];
//				continue;
//			}
//		}
//	}
//
//	return res;
//}
//
////
////bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
////	if (nums.size() <= 1 || t < 0 || k < 0) {
////		return 0;
////	}
////	map<long long, long long> hash_;
////	size_t n = nums.size();
////
////	for (size_t ptr = 0; ptr <n; ptr++) {
////		int basic = floor(1.0 * nums[ptr] / ((long long)t + 1));
////		if (hash_.count(basic)) {
////			return 1;
////		} else if (hash_.count(basic + 1) && (hash_[basic + 1] - nums[ptr] <= t)) {
////			return 1;
////		} else if (hash_.count(basic - 1) && (-hash_[basic - 1] + nums[ptr] <= t)) {
////			return 1;
////		} else {
////			hash_[basic] = nums[ptr];
////			if (size(hash_) > k) {
////				int tmp_bas = floor(1.0 * nums[ptr - k] / ((long long)t + 1));
////				hash_.erase(tmp_bas);
////			}
////		}
////
////	}
////	
////	return 0;
////}
//
//struct cmp {
//	bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) const {
//		return lhs.second == rhs.second;
//	}
//};
//bool containsnearbyalmostduplicate(vector<int>& nums, int k, int t) {
//	if (nums.size() <= 1 || t < 0) {
//		return 0;
//	}
//	map<int, int> hash_;
//	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
//		for (size_t ptr1 = ptr + 1; ptr1 < nums.size(); ptr1++) {
//			if (nums[ptr] == nums[ptr1]) {
//				hash_[ptr] = nums[ptr];
//				hash_[ptr1] = nums[ptr];
//			}
//		}
//	}
//
//	vector<std::pair<int, int>> tmp_vec;
//	tmp_vec.reserve(hash_.size());
//	std::for_each(hash_.begin(), hash_.end(), [&tmp_vec](const std::map<int, int>::value_type& p) { tmp_vec.push_back({ p.first, p.second }); });
//	std::sort(tmp_vec.begin(), tmp_vec.end(), cmp());
//
//	auto pt_first = tmp_vec.begin();
//	auto pt_second = ++tmp_vec.begin();
//
//	while (pt_second != tmp_vec.end()) {
//		if (pt_first->second == pt_second->second) {
//			if ((std::abs(pt_second->second - pt_first->second) <= t) && (std::abs(pt_second->first - pt_first->first) <= k)) {
//				return 1;
//			}
//			pt_first++;
//			pt_second++;
//		} else {
//			pt_first++;
//			pt_second++;
//		}
//	}
//	for (const auto& [pos, elem] : tmp_vec) {
//		cout << "POSITION: " << pos << " ELEM: " << elem << endl;
//	}
//	return 0;
//}
//
//
//int numIdenticalPairs(vector<int>& nums) {
//	int ctr = 0;
//	map <int, int> res;
//	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
//		res[nums[ptr]]++;
//	}
//	for (const auto& [num, ctrs] : res) {
//		if (ctrs > 1) {
//			ctr += ctrs * (ctrs - 1) / 2;
//		}
//	}
//	return ctr;
//}
//
//int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
//	if (arr.size() < 3) {
//		return 0;
//	}
//	int ctr = 0;
//	for (size_t i = 0; i < arr.size(); i++) {
//		for (size_t j = i + 1; j < arr.size(); j++) {
//			for (size_t k = j + 1; k < arr.size(); k++) {
//				int a_ = std::abs(arr[i] - arr[j]);
//				int b_ = std::abs(arr[j] - arr[k]);
//				int c_ = std::abs(arr[i] - arr[k]);
//				if (a_ <= a && b_ <= b && c_ <= c) {
//					ctr++;
//				}
//			}
//		}
//	}
//	return ctr;
//}
//
//int findKthPositive(vector<int>& arr, int k) {
//	for (int i = 0; i < arr.size(); i++) {
//		int x = arr[i] - (i + 1);
//		if (x >= k)
//			return i + k;
//	}
//	return arr.size() + k;
//}
//
//int sumOddLengthSubarrays(vector<int>& arr) {
//	if (arr.empty()) {
//		return 0;
//	}
//	int res = 0;
//	std::count_if(arr.begin(), arr.end(), [&res](const int& val) { return res += val; });
//	if (arr.size() < 3) {
//		return res;
//	}
//	size_t ctr = 2;
//	while (ctr < arr.size()) {
//		for (size_t ptr = 0; ptr + ctr < arr.size(); ptr++) {
//			size_t tmp_iter = ptr;
//			while (tmp_iter != ptr + ctr + 1) {
//				res += arr[tmp_iter];
//				tmp_iter++;
//			}
//		}
//		ctr += 2;
//	}
//	return res;
//}
//
//vector<string> stringMatching(vector<string>& words) {
//	set<string> res;
//	for (size_t ptr = 0; ptr < words.size(); ptr++) {
//		for (size_t ptr1 = 0; ptr1 < words.size(); ptr1++) {
//			if (words[ptr].find(words[ptr1]) != std::string::npos && words[ptr1].size() < words[ptr].size()) {
//				res.insert(words[ptr1]);
//			}
//		}
//	}
//	return { res.begin(), res.end() };
//}
//
//int floid_tortoise_hare(vector<int>& elems) {
//	int res = INT_MIN;
//	int tortoise = elems[0];
//	int hare = elems[0];
//
//	while (true) {
//		if (tortoise > elems.size() - 1) {
//			return res;
//		}
//		tortoise = elems[tortoise];
//		hare = elems[elems[hare]];
//		if (tortoise == hare) {
//			break;
//		}
//	}
//
//	tortoise = elems[0];
//	while (tortoise != hare) {
//		tortoise = elems[tortoise];
//		hare = elems[hare];
//	}
//	res = tortoise;
//	return res;
//}
//
//struct point {
//	point() = default;
//	point(const double x_, const double y_) : x(x_), y(y_) {};
//	point(double&& x_, double&& y_) {
//		std::swap(this->x, x_);
//		std::swap(this->y, y_);
//	};
//
//	double x = 0;
//	double y = 0;
//};
//
//point create_point(double x, double y) {
//	point* tmp_pnt = new point(x, y);
//	return *tmp_pnt;
//}
//
//vector<point> generate_points(size_t size) {
//	vector<point> prescision;
//
//	for (size_t ptr = 0; ptr < size; ptr++) {
//		double x_ = ((double)rand() / (RAND_MAX));
//		double y_ = ((double)rand() / (RAND_MAX));
//		prescision.push_back(create_point(std::move(x_), std::move(y_)));
//	}
//
//	return prescision;
//}
//
//double calculate_pi(vector<point> points_) {
//	int before_one = 0;
//	int total_one = 0;
//	double PI = 0.0;
//	for (const auto point : points_) {
//		if (((point.x * point.x) + (point.y * point.y)) < 1.0) {
//			before_one += 1;
//		}
//		total_one += 1;
//	}
//
//	PI = 4.0 * (before_one) / (total_one);
//	cout << before_one << " " << total_one << endl;
//	return PI;
//}
//
//
//int compare_elem(vector<int>::iterator begin, vector<int>::iterator end) {
//	int res = *begin;
//	++begin;
//	while (begin <= end) {
//		res += *begin;
//		++begin;
//	}
//	return res;
//}
//
//vector<int> runningSum(vector<int>& nums) {
//	vector<int> res;
//	auto iter_first = nums.begin();
//	auto iter_second = nums.begin();
//
//	while (iter_first < nums.end()) {
//		int elem = compare_elem(iter_second, iter_first);
//		res.push_back(elem);
//		++iter_first;
//	}
//
//	return res;
//}
//
//int xorOperation(int n, int start) {
//	if (n == 1) {
//		return start;
//	}
//	vector<int> arr;
//	arr.resize(n);
//	for (size_t ptr = 0; ptr < n; ptr++) {
//		arr[ptr] = start + 2 * ptr;
//	}
//	int res = 0;
//	for (const auto& elem : arr) {
//		res = res ^ elem;
//	}
//	return res;
//}
//
//int maximumProduct(vector<int>& nums) {
//	std::sort(nums.begin(), nums.end());
//	int size = nums.size();
//	int first = nums[0] * nums[1] * nums[size - 1];
//	int second = nums[size - 1] * nums[size - 2] * nums[size - 3];
//	return first > second ? first : second;
//}
//
//int digits_num(int elem) {
//	int res = 0;
//	while (elem) {
//		elem /= 10;
//		res++;
//	}
//	return res;
//}
//
//int findNumbers(vector<int>& nums) {
//	int even_ctr = 0;
//	for (auto elem : nums) {
//		if (digits_num(elem) % 2 == 0 && digits_num(elem) > 0) {
//			even_ctr++;
//		}
//	}
//	return even_ctr;
//}
//
//vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
//	vector<bool> res(candies.size());
//	int max = *std::max_element(candies.begin(), candies.end());
//	for (size_t ptr = 0; ptr < candies.size(); ptr++) {
//		if (candies[ptr] + extraCandies >= max) {
//			res[ptr] = true;
//		} else {
//			res[ptr] = false;
//		}
//	}
//	return res;
//}
//
//bool isOneBitCharacter(vector<int>& bits) {
//	if (bits[bits.size() - 1] == 1) {
//		return false;
//	}
//	for (size_t ptr = 0; ptr < bits.size(); ptr++) {
//		if (ptr == bits.size() - 1) {
//			return true;
//		}
//		if (bits[ptr] == 1) {
//			ptr++;
//		}
//	}
//
//	return false;
//}
//
//struct freqcmp {
//	bool operator()(const pair<char, int>& lhs, const pair<char, int>& rhs) const {
//		return lhs.second < rhs.second;
//	}
//};
//
//
//
//int getMin(map<char, int> mymap) {
//	std::pair<char, int> min = *min_element(mymap.begin(), mymap.end(), freqcmp());
//	return min.second;
//}
//
//int maxNumberOfBalloons(string text) {
//	if (text.size() < 7) {
//		return 0;
//	}
//
//	map<char, int> naebolko{ {'b', 0}, {'a', 0}, {'l', 0}, {'o', 0}, {'n', 0} };
//	for (const auto& c : text) {
//		if (naebolko.find(c) != naebolko.end()) {
//			naebolko.at(c)++;
//		}
//	}
//
//	naebolko['l'] /= 2;
//	naebolko['o'] /= 2;
//
//	return getMin(naebolko);
//}
//
//vector<string> separate_spaces(string& text) {
//	vector<string> res;
//	string word;
//	for (size_t ptr = 0; ptr < text.size(); ptr++) {
//		if (text[ptr] == 32) {
//			res.push_back(word);
//			word.clear();
//		} else {
//			word += text[ptr];
//		}
//	}
//	res.push_back(word);
//	return res;
//}
//
//vector<string> uncommonFromSentences(string A, string B) {
//	vector<string> res;
//	map<string, int> ctr_map;
//	for (auto& w : separate_spaces(A)) {
//		ctr_map[w] ++;
//	}
//	for (auto& w : separate_spaces(B)) {
//		ctr_map[w] ++;
//	}
//	for (const auto [word, ctr] : ctr_map) {
//		if (ctr == 1) {
//			res.push_back(word);
//		}
//	}
//	return res;
//}
//
//vector<string> findOcurrences(string text, string first, string second) {
//	vector<string> res;
//	vector<string> separate = separate_spaces(text);
//	for (size_t ptr = 0; ptr + 2 < separate.size(); ptr++) {
//		if (separate[ptr] == first && separate[ptr + 1] == second) {
//			res.push_back(separate[ptr + 2]);
//		}
//	}
//
//	return res;
//}
//
//struct ListNode {
//	int val;
//	ListNode* next;
//	ListNode() : val(0), next(nullptr) {}
//	ListNode(int x) : val(x), next(nullptr) {}
//	ListNode(int x, ListNode* next) : val(x), next(next) {}
//};
//
//
//// BAD DESIGN
//int getDecimalValue(ListNode* head) {
//	int res = 0;
//	vector<int>bytes;
//	while (head != nullptr) {
//		bytes.push_back(head->val);
//		head = head->next;
//	}
//
//	for (int ptr_end = bytes.size() - 1, ptr_begin = 0; ptr_end > -1; ptr_end--, ptr_begin++) {
//		res += bytes[ptr_begin] * (1 << ptr_end);
//	}
//
//	return res;
//}
//
//int getDecimalValue_2(ListNode* head) {
//	ListNode* cur = head;
//	int len = 0;
//	while (cur) {
//		len++;
//		cur = cur->next;
//	}
//
//	cur = head;
//	int res = 0;
//	len = len - 1;
//	while (cur) {
//		res += cur->val * (1 << (len--));
//		cur = cur->next;
//	}
//	return res;
//}
////-----------
//
//int maxPower(string s) {
//	int max = 1, tmp_max = 1;
//
//	for (size_t ptr = 0; ptr + 1 < s.size(); ptr++) {
//		if (s[ptr] == s[ptr + 1]) {
//			tmp_max++;
//		}
//		if (s[ptr] != s[ptr + 1]) {
//			if (tmp_max >= max) {
//				max = tmp_max;
//			}
//			tmp_max = 1;
//		}
//	}
//
//	if (tmp_max >= max) {
//		max = tmp_max;
//	}
//
//	return max;
//}
//
//vector<string> commonChars(vector<string>& A) {
//	vector<string> res;
//	int first[26];
//	int tmp[26];
//	fill(first, first + 26, 1000);
//	for (const auto& str : A) {
//		fill(tmp, tmp + 26, 0);
//		for (size_t ptr = 0; ptr < str.size(); ptr++) {
//			tmp[str[ptr] - 'a'] += 1;
//		}
//		for (size_t ptr = 0; ptr < 26; ptr++) {
//			first[ptr] = min(first[ptr], tmp[ptr]);
//		}
//	}
//	for (size_t ptr = 0; ptr < 26; ptr++) {
//		while (first[ptr]) {
//			string tmp{ (char)('a' + ptr) };
//			res.push_back(tmp);
//			first[ptr]--;
//		}
//	}
//	return res;
//}
//
//int findLucky(vector<int>& arr) {
//	int ptrmax = 0;
//	map<int, int> duplicates;
//	sort(arr.begin(), arr.end());
//	for_each(arr.begin(), arr.end(), [&duplicates](int value) {duplicates[value]++; });
//	for (auto ptr : duplicates) {
//		if (ptr.first == ptr.second) {
//			if (ptrmax < ptr.first) {
//				ptrmax = ptr.first;
//			}
//		}
//	}
//	return ptrmax ? ptrmax : -1;
//}
//
//vector<int> sortedSquares(vector<int>& A) {
//	for (int ptr = 0; ptr < A.size(); ptr++) {
//		A[ptr] = A[ptr] * A[ptr];
//	}
//	sort(A.begin(), A.end());
//	return A;
//}
//
//uint32_t reverseBits(uint32_t n) {
//	uint32_t res;
//	string bin;
//
//	for (int i = 31; i >= 0; i--) {
//		int k = n >> i;
//		if (k & 1)
//			bin += "1";
//		else
//			bin += "0";
//	}
//	cout << bin << endl;
//	reverse(bin.begin(), bin.end());
//	res = stoll(bin, nullptr, 2);
//	return res;
//}
//
//int heightChecker(vector<int>& heights) {
//	int res = 0;
//	vector <int> tmp(heights);
//	sort(tmp.begin(), tmp.end());
//	for (int ptr = 0; ptr < heights.size(); ptr++) {
//		if (tmp[ptr] != heights[ptr]) {
//			res++;
//		}
//	}
//
//	return res;
//}
//
//bool judgeCircle(string moves) {
//	int X = 0, Y = 0;
//	for (int ptr = 0; ptr < moves.size(); ptr++) {
//		if (moves[ptr] == 'U') {
//			X++;
//		}
//		if (moves[ptr] == 'D') {
//			X--;
//		}
//		if (moves[ptr] == 'L') {
//			Y--;
//		}
//		if (moves[ptr] == 'R') {
//			Y++;
//		}
//	}
//	if (X == 0 && Y == 0) {
//		return 1;
//	} else {
//		return 0;
//	}
//}
//
//
//vector<int> sortArrayByParity(vector<int>& A) {
//	vector <int> res;
//	for (int ptr = 0; ptr < A.size(); ptr++) {
//		if (A[ptr] % 2 == 0) {
//			res.insert(res.begin(), A[ptr]);
//		} else if (A[ptr] % 2 != 0) {
//			res.insert(res.end(), A[ptr]);
//		}
//	}
//	return res;
//}
//
//string reverseWords(string s) {
//	int tmp = 0;
//	std::string::size_type pos = 0;
//	for (; (pos = s.find_first_of(" ", pos)) != std::string::npos; pos++) {
//		if (pos) {
//			reverse(s.begin() + tmp, s.begin() + pos);
//			tmp = pos + 1;
//		}
//	}
//	reverse(s.begin() + tmp, s.end());
//	return s;
//}
//
//int singleNumber(std::vector<int>& nums) {
//	std::unordered_map<int, int> mp;
//	for (int i = 0; i < nums.size(); i++) {
//		mp[nums[i]]++;
//	}
//	for (int i = 0; i < nums.size(); i++) {
//		if (mp[nums[i]] == 1) {
//			return nums[i];
//		}
//	}
//	return -1;
//}
//
//vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
//	vector<int>res;
//	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
//		int tmp_ctr = 0;
//		for (size_t ptr1 = 0; ptr1 < nums.size(); ptr1++) {
//			if (nums[ptr] > nums[ptr1] && ptr != ptr1) {
//				tmp_ctr++;
//			}
//		}
//		res.push_back(tmp_ctr);
//	}
//	return res;
//}
//
//bool isHappy(int n) {
//	if (n == 1) {
//		return 1;
//	}
//	if (n == 2) {
//		return 0;
//	}
//
//	set<int> hsh;
//
//	while (n != 1) {
//		int tmp_n = 0;
//
//		if (hsh.find(n) != hsh.end()) {
//			return 0;
//		}
//		hsh.insert(n);
//		while (n > 0) {
//			tmp_n += pow((n % 10), 2);
//			n /= 10;
//		}
//
//		n = tmp_n;
//	}
//	return 1;
//}
//
//bool canMakeArithmeticProgression(vector<int>& arr) {
//	std::sort(arr.begin(), arr.end());
//	int diff = arr[1] - arr[0];
//	for (size_t ptr = 0; ptr + 1 < arr.size(); ptr++) {
//		if (arr[ptr + 1] - arr[ptr] != diff) {
//			return false;
//		}
//	}
//	return true;
//}
//
//double average(vector<int>& salary) {
//	std::sort(salary.begin(), salary.end());
//	double avr = 0.0;
//	for (size_t ptr = 1; ptr < salary.size() - 1; ptr++) {
//		avr += salary[ptr];
//	}
//	return (avr / (double)(salary.size() - 2));
//}
//
//string restoreString(string s, vector<int>& indices) {
//	map<int, char> order;
//	for (size_t ptr = 0; ptr < indices.size(); ptr++) {
//		order[indices[ptr]] = s[ptr];
//	}
//	s.clear();
//	for (const auto& [pos, ch] : order) {
//		s += ch;
//	}
//	return s;
//}
//string restoreString_1(string s, vector<int>& indices) {
//	string res(s);
//	for (size_t ptr = 0; ptr < indices.size(); ptr++) {
//		res[indices[ptr]] = s[ptr];
//	}
//	return res;
//}
//
//
//ListNode* removeElements(ListNode* head, int val) {
//	if (head == nullptr) {
//		return {};
//	}
//	ListNode* new_root = head;
//	ListNode* head_next = head->next;
//
//	while (head_next != nullptr) {
//		if (head_next->val == val) {
//			head->next = head_next->next;
//			head_next = head->next;
//			continue;
//		}
//		head = head->next;
//		head_next = head_next->next;
//	}
//	if (new_root->val == val) {
//		return new_root = new_root->next;
//	}
//	return new_root;
//}
//
//void print_node(ListNode* node) {
//	if (node == NULL) {
//		cout << "EMPTY" << endl;
//	} else {
//		while (node != nullptr) {
//			cout << node->val << " ";
//			node = node->next;
//		}
//		cout << "FIN" << endl;
//		cout << endl;
//	}
//}
//
//vector<string> buildArray(vector<int>& target, int n) {
//	vector<string> moving;
//	for (int ptr = 0, ctr = 1; ptr < target.size(); ptr++, ctr++) {
//		if (ctr == target[ptr]) {
//			moving.push_back("Push"s);
//		} else {
//			ptr--;
//			moving.push_back("Push"s);
//			moving.push_back("Pop"s);
//		}
//	}
//
//	return moving;
//}
//
//vector<int> decode(vector<int>& encoded, int first) {
//	vector<int> decoded;
//	decoded.resize(encoded.size() + 1);
//	decoded[0] = first;
//	for (size_t ptr = 0; ptr < encoded.size(); ptr++) {
//		decoded[ptr + 1] = encoded[ptr] xor decoded[ptr];
//	}
//	return decoded;
//}
//
//bool isPalindrome(int x) {
//	vector<int>res;
//	if (x < 0) {
//		return false;
//	}
//	if (x == 0) {
//		return true;
//	}
//	while (x >= 10) {
//		int tmp = x % 10;
//		x /= 10;
//		res.push_back(tmp);
//	}
//	res.push_back(x);
//	for (size_t btr = 0, ept = res.size() - 1; btr < res.size() / 2; btr++, ept--) {
//		if (res[btr] != res[ept]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//bool isPalindrome_1(int x) {
//	if (x < 0) {
//		return false;
//	}
//	long revX = 0;
//	long tmp_val = x;
//	while (tmp_val > 0) {
//		revX = revX * 10 + tmp_val % 10;
//		tmp_val /= 10;
//	}
//	return x == revX ? true : false;
//}
//
//bool isPalindrome(ListNode* head) {
//	vector<int> vec;
//	while (head != nullptr) {
//		vec.push_back(head->val);
//		head = head->next;
//	}
//	for (size_t btr = 0, ept = vec.size() - 1; btr < vec.size() / 2; btr++, ept--) {
//		if (vec[btr] != vec[ept]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//bool checkIfPangram(string sentence) {
//	set<char> alphabet = { sentence.begin(), sentence.end() };
//	return alphabet.size() >= 26 ? true : false;
//}
//
//void delete_restricted(string& number) {
//	for (size_t ptr = 0; ptr < number.size(); ptr++) {
//		if (number[ptr] == 32 || number[ptr] == '-') {
//			number.erase(ptr, 1);
//			ptr--;
//		}
//	}
//}
//
//string reformatNumber(string number) {
//	delete_restricted(number);
//	if (number.size() < 4) {
//		return number;
//	}
//	size_t tel_size = number.size();
//	size_t ptr = 0;
//
//	while (tel_size > 0) {
//		if (tel_size > 4) {
//			ptr += 3;
//			number.insert(ptr, "-");
//			ptr += 1;
//			tel_size -= 3;
//		} else if (tel_size == 4) {
//			ptr += 2;
//			number.insert(ptr, "-");
//			ptr += 1;
//			tel_size -= 2;
//		} else {
//			break;
//		}
//	}
//	return number;
//}
//
//bool isVowel(char c) {
//	return (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' ||
//		c == 'o' || c == 'O' || c == 'u' || c == 'U');
//}
//
//string reverseVowels(string s) {
//	size_t beg = 0;
//	size_t end = s.size() - 1;
//
//	while (beg < end) {
//		if (isVowel(s[beg]) && isVowel(s[end])) {
//			std::swap(s[beg++], s[end--]);
//		} else if (!isVowel(s[beg])) {
//			beg++;
//		} else if (!isVowel(s[end])) {
//			end--;
//		}
//	}
//	return s;
//}
//
//void clear_zeros(string& num) {
//	if (num.size() == 1) {
//		return;
//	}
//	while (num[0] == 48) {
//		num.erase(0, 1);
//	}
//	if (!std::isdigit(num[0])) {
//		num += '0';
//	}
//}
//
//int numDifferentIntegers(string word) {
//	set<string> strings_;
//	string tmp_num;
//	for (size_t ptr = 0; ptr < word.size(); ptr++) {
//		if (word[ptr] >= '0' && word[ptr] <= '9') {
//			tmp_num += word[ptr];
//			if (ptr == word.size() - 1) {
//				clear_zeros(tmp_num);
//				strings_.insert(tmp_num);
//				tmp_num.clear();
//			}
//		}
//		if ((word[ptr] < '0' || word[ptr] > '9') && !tmp_num.empty()) {
//			clear_zeros(tmp_num);
//			strings_.insert(tmp_num);
//			tmp_num.clear();
//		}
//	}
//
//	return strings_.size();
//}
//
//
////bad design
//bool isAnagram(string s, string t) {
//	std::sort(s.begin(), s.end());
//	std::sort(t.begin(), t.end());
//	return s == t;
//}
////good design
//bool isAnagram_1(string s, string t) {
//	vector<int> c1(26, 0);
//	for (char c : s) {
//		c1[c - 'a'] ++;
//	}
//	for (char c : t) {
//		c1[c - 'a'] --;
//	}
//
//	for (int i = 0; i < 26; ++i) {
//		if (c1[i]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//int totalMoney(int n) {
//	int monday_pay = 1;
//	int total_sum = 0;
//	int weekend_ctr = 0;
//	while (n > 0) {
//		total_sum += monday_pay + weekend_ctr;
//		weekend_ctr++;
//		if (weekend_ctr == 7) {
//			monday_pay += 1;
//			weekend_ctr = 0;
//		}
//		n--;
//	}
//
//	return total_sum;
//}
//
////Prototype design pattern
//class dog {
//public:
//	explicit dog() = default;
//	dog(string name) : name_(name) {
//		this->age_ = 1;
//	}
//	dog(string name, size_t age) : name_(name), age_(age) {}
//
//	void set_name(string name) {
//		this->name_ = name;
//	}
//	void set_age(size_t age) {
//		this->age_ = age;
//	}
//	string* name_mutable() {
//		return &this->name_;
//	}
//	size_t* age_mutable() {
//		return &this->age_;
//	}
//	virtual dog clone() const = delete;
//
//	virtual void wow() {
//		cout << "WOW WOW" << endl;
//	}
//private:
//	string name_ = "";
//	size_t age_ = 0;
//};
//
//class fight_dog : public dog {
//public:
//	explicit fight_dog() = default;
//	fight_dog(string name) : name_(name) {
//		this->age_ = 1;
//		this->power_ = 1;
//	}
//	fight_dog(string name, size_t age) {
//		this->name_ = name;
//		this->age_ = age;
//		this->power_ = 1;
//	}
//	fight_dog(string name, size_t age, size_t pow) : name_(name), age_(age), power_(pow) {}
//
//	void set_pow(size_t pow) {
//		this->power_ = pow;
//	}
//
//	size_t* power_mutable() {
//		return &this->power_;
//	}
//
//
//
//	void wow() override {
//		cout << "HEY MOTHERFUCKER! YOU BETTER RUN!" << endl;
//	}
//
//private:
//	string name_ = "";
//	size_t age_ = 0;
//	size_t power_ = 0;
//};
//
//int tribonacci(int n) {
//	int res = 0;
//	vector<size_t> F_(41);
//	F_[0] = 0;
//	F_[1] = 1;
//	F_[2] = 1;
//
//	for (size_t ptr = 0; ptr < F_.size(); ptr++) {
//		if (n == ptr) {
//			return F_[ptr];
//		}
//		F_[ptr + 3] = F_[ptr] + F_[ptr + 1] + F_[ptr + 2];
//	}
//	return 0;
//}
//
//int maxAscendingSum(vector<int>& nums) {
//	int max_asc = 0;
//	int max_tmp = 0;
//	if (nums.empty()) {
//		return 0;
//	}
//	if (nums.size() == 1) {
//		return nums[0];
//	}
//	for (size_t ptr = 1; ptr < nums.size(); ptr++) {
//		if (nums[ptr] > nums[ptr - 1]) {
//			max_tmp += nums[ptr - 1];
//			if (ptr == nums.size() - 1) {
//				max_tmp += nums[ptr];
//			}
//		} else {
//			max_tmp += nums[ptr - 1];
//			max_asc = std::max(max_asc, max_tmp);
//			max_tmp = 0;
//		}
//	}
//	max_asc = std::max(max_asc, max_tmp);
//	return max_asc;
//}
//
//int sumBase(int n, int k) {
//	int converted = 0;
//	vector<int> res;
//	while (n > 0) {
//		converted = n % k;
//		res.push_back(converted);
//		n /= k;
//	}
//	converted = 0;
//	converted = accumulate(res.begin(), res.end(), converted);
//	return converted;
//}
//
//int getMinDistance(vector<int>& nums, int target, int start) {
//	int min_dist = INT_MAX;
//	for (size_t ptr_b = 0, ptr_e = nums.size() - 1; ptr_b < nums.size(); ptr_b++, ptr_e--) {
//		if (nums[ptr_b] == target) {
//			int tmp = ptr_b - start;
//			if ((std::abs(tmp)) < min_dist) {
//				min_dist = std::abs(tmp);
//			}
//		} else if (nums[ptr_e] == target) {
//			int tmp = ptr_e - start;
//			if ((std::abs(tmp)) < min_dist) {
//				min_dist = std::abs(tmp);
//			}
//		}
//	}
//	return min_dist;
//}
//
//bool count_number_set(unsigned n) {
//	int ctr = 0;
//	unsigned i;
//	for (i = 1 << 31; i > 0; i = i / 2) {
//		(n & i) ? ctr += 1 : ctr += 0;
//	}
//	if (ctr == 2 || ctr == 3 || ctr == 5 || ctr == 7 || ctr == 11 || ctr == 13 || ctr == 17 || ctr == 19) {
//		return true;
//	}
//	return false;
//}
//
//int countPrimeSetBits(int L, int R) {
//	int res = 0;
//	for (; L <= R; L++) {
//		if (count_number_set(L)) {
//			res++;
//		}
//	}
//	return res;
//}
//
//int count_number(uint32_t n) {
//	size_t ctr = 0;
//	unsigned i;
//	for (i = 1 << 31; i > 0; i = i / 2) {
//		(n & i) ? ctr += 1 : ctr += 0;
//	}
//	return ctr;
//}
//
//int hammingWeight(uint32_t n) {
//	return count_number(n);
//}
//
//int findTheWinner(int n, int k) {
//	vector<int> res;
//	for (size_t ptr = 0; ptr < n; ptr++) {
//		res.push_back(ptr + 1);
//	}
//	int ptr = 0;
//	int size = res.size();
//	while (size != 1) {
//		if ((ptr + (k - 1)) < size) {
//			ptr += (k - 1);
//			res.erase(res.begin() + ptr);
//		} else {
//			ptr = (ptr + (k - 1)) - res.size();
//			while (ptr >= res.size()) {
//				ptr -= res.size();
//			}
//
//			res.erase(res.begin() + ptr);
//		}
//		size = res.size();
//	}
//
//	return res[0];
//}
//
//int find_emerald(const string& J, const string& S) {
//	int res = 0;
//	for (const auto& s : S) {
//		if (J.find(s) != std::string::npos) {
//			res++;
//		}
//	}
//	return res;
//}
//
//bool check(vector<int>& nums) {
//	int x = 0;
//	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
//		if (nums[ptr] > nums[ptr + 1]) {
//			x = ptr + 1;
//		}
//	}
//	if (x == 0) {
//		return true;
//	}
//
//	vector<int> B = nums;
//	std::sort(B.begin(), B.end());
//	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
//		if (B[ptr] != nums[(ptr + x) % nums.size()]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//std::vector<std::string> SplitIntoWords(const std::string_view& text) {
//	std::vector<std::string> words;
//	std::string word;
//	for (const char c : text) {
//		if (c == ' ') {
//			if (!word.empty()) {
//				words.push_back(word);
//				word.clear();
//			}
//		} else {
//			word += c;
//		}
//	}
//	if (!word.empty()) {
//		words.push_back(word);
//	}
//	return words;
//}
//
//string reformatDate(string date) {
//	string res;
//	map <string, string> month{ {"Jan", "01"}, { "Feb", "02" }, { "Mar", "03" }, { "Apr", "04" }, { "May", "05" }, { "Jun", "06" }, { "Jul", "07" }, { "Aug", "08" },
//		{ "Sep", "09" }, { "Oct", "10" }, { "Nov", "11" }, { "Dec", "12" } };
//	vector<string> date_parsed = SplitIntoWords(date);
//
//	res += date_parsed[2] + '-';
//	res += month.at(date_parsed[1]) + '-';
//
//	string day_tmp = date_parsed[0].substr(0, date_parsed[0].size() - 2);
//	if (day_tmp.size() == 1) {
//		day_tmp.insert(0, "0");
//	}
//	res += day_tmp;
//	return res;
//}
//
//int maxIceCream(vector<int>& costs, int coins) {
//	std::sort(costs.begin(), costs.end());
//	if (coins < costs[0]) {
//		return 0;
//	}
//	int res = 0;
//	auto ice_ptr = costs.begin();
//	while (coins >= *ice_ptr) {
//		coins -= *ice_ptr;
//		res++;
//		if (ice_ptr + 1 == costs.end()) {
//			break;
//		}
//		ice_ptr++;
//	}
//	return res;
//}
//
//vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
//	vector<int>res;
//	for (auto const& n : nums1) {
//		auto n2 = std::find(nums2.begin(), nums2.end(), n);
//		if (n2 == nums2.end()) {
//			res.push_back(-1);
//		} else {
//			for (; n2 != nums2.end(); n2++) {
//				if (n < *n2) {
//					res.push_back(*n2);
//					break;
//				}
//			}
//			if (n2 == nums2.end()) {
//				res.push_back(-1);
//			}
//		}
//	}
//	return res;
//}
//
//bool kLengthApart(vector<int>& nums, int k) {
//	if (k == 0) {
//		return true;
//	}
//	size_t pos_first = 0;
//	size_t pos_end = 0;
//	for (size_t ptr = 0; ptr < nums.size(); ptr++) {
//		if (nums[ptr] == 1) {
//			pos_first = ptr;
//			for (size_t ptr2 = ptr + 1; ptr2 < nums.size(); ptr2++) {
//				if (nums[ptr2] == 1) {
//					pos_end = ptr2;
//					break;
//				}
//			}
//		}
//		if ((pos_end - pos_first) <= k && pos_first < pos_end) {
//			return false;
//		}
//	}
//	return true;
//}
//
//bool isSubsequence(string s, string t) {
//	if (s.empty()) {
//		return false;
//	}
//	size_t len_s = s.size();
//	size_t ptr = 0;
//	for (size_t ptr1 = 0; ptr1 < t.size(); ptr1++) {
//		if (t[ptr1] == s[ptr]) {
//			ptr++;
//		}
//		if (ptr == len_s) {
//			return true;
//		}
//	}
//	return false;
//}
//
//vector<int> shuffle(vector<int>& nums, int n) {
//	vector<int> res;
//	for (size_t ptr = 0, ptr_mid = n; ptr < n; ptr++, ptr_mid++) {
//		res.push_back(nums[ptr]);
//		res.push_back(nums[ptr_mid]);
//	}
//	return res;
//}
//
//int secondHighest(string s) {
//	set<int> res;
//	for (const auto& el : s) {
//		if (std::isdigit(el)) {
//			res.insert(el - 48);
//		}
//	}
//	if (res.size() == 1 || res.empty()) {
//		return -1;
//	}
//
//	return *--(--res.end());
//}
//
//void sort_clean(std::vector<std::string>& words) {
//	std::sort(words.begin(), words.end(), [](std::string& A, std::string& B) {
//		return A[A.size() - 1] < B[B.size() - 1];
//		});
//	for (auto& w : words) {
//		w = w.substr(0, w.size() - 1);
//	}
//}
//
//std::vector<std::string> SplitIntoWords_1(const std::string_view& text) {
//	std::vector<std::string> words;
//	std::string word;
//	for (const char c : text) {
//		if (c == ' ') {
//			if (!word.empty()) {
//				words.push_back(word);
//				word.clear();
//			}
//		} else {
//			word += c;
//		}
//	}
//	if (!word.empty()) {
//		words.push_back(word);
//	}
//	sort_clean(words);
//	return words;
//}
//
//string sortSentence(string s) {
//	std::string res;
//	std::vector<std::string> words = SplitIntoWords_1(s);
//
//	for (auto& w : words) {
//		res += w + ' ';
//	}
//
//	return res.substr(0, res.size() - 1);
//}
//
//int arraySign(vector<int>& nums) {
//	if (nums.empty()) {
//		return 0;
//	}
//	for (auto& w : nums) {
//		if (w < 0) {
//			w = -1;
//		}
//		if (w > 0) {
//			w = 1;
//		}
//	}
//	int res = std::accumulate(begin(nums), end(nums), 1, std::multiplies<int>());
//	if (res > 0) {
//		return 1;
//	}
//	if (res == 0) {
//		return 0;
//	}
//	return -1;
//}
//
//bool rotateString(string s, string goal) {
//	if (s.empty() && goal.empty()) {
//		return true;
//	}
//	if (s.empty()) {
//		return false;
//	}
//
//	size_t s_s = s.size();
//	while (s_s) {
//		char f = s[0];
//		s = s.substr(1);
//		s += f;
//		if (s == goal) {
//			return true;
//		}
//		s_s--;
//	}
//	return false;
//}
//
//bool canConstruct(string ransomNote, string magazine) {
//	map<char, int> rans;
//	map<char, int> mag;
//	for (const auto& c : ransomNote) {
//		rans[c]++;
//	}
//	for (const auto& c : magazine) {
//		mag[c]++;
//	}
//	for (const auto& [ch, ctr] : rans) {
//		if (mag.find(ch) == mag.end()) {
//			return false;
//		}
//		if (ctr > mag.at(ch)) {
//			return false;
//		}
//	}
//	return true;
//}
//
//vector<vector<int>> largeGroupPositions(string s) {
//	vector<vector<int>> res;
//	int ctr = 0;
//	int p_beg = 0;
//	int p_end = 0;
//
//	for (size_t ptr = 0; ptr + 1 < s.size(); ptr++) {
//		if (s[ptr] == s[ptr + 1]) {
//			p_beg = ptr;
//			while (s[ptr] == s[ptr + 1]) {
//				ptr++;
//			}
//			p_end = ptr;
//		}
//
//
//		if ((p_end - p_beg) + 1 >= 3) {
//			res.push_back({ p_beg, p_end });
//			p_beg = 0;
//			p_end = 0;
//		}
//	}
//
//	return res;
//}
//
//
//
//ListNode* reverseList(ListNode* head) {
//	if (head == nullptr) {
//		return {};
//	}
//	ListNode* prev_ = nullptr;
//	ListNode* curr_ = head;
//	ListNode* next_ = nullptr;
//	while (curr_ != nullptr) {
//		next_ = curr_->next;
//		curr_->next = prev_;
//		prev_ = curr_;
//		curr_ = next_;
//
//	}
//
//	return head;
//}
//
//void XoringSubsets(vector<int>& nums, vector<int>& subset, int& res, int index) {
//	int r = 0;
//	for (auto& num : subset) {
//		r = r xor num;
//	}
//	res += r;
//
//	for (int ptr = index; ptr < nums.size(); ptr++) {
//		subset.push_back(nums[ptr]);
//		XoringSubsets(nums, subset, res, ptr + 1);
//		subset.pop_back();
//	}
//	return;
//}
//
//int subsetXORSum(vector<int>& nums) {
//	if (nums.size() == 1) {
//		return nums[0];
//	}
//
//	int res = 0, index = 0;
//	vector<int> subset;
//
//	XoringSubsets(nums, subset, res, index);
//
//	return res;
//}
//
//bool isPowerOfTwo(int n) {
//	return ((n > 0) && ((n & n - 1) == 0));
//	//https://tproger.ru/problems/explaination-what-the-following-code-do/
//}
//
//bool isPowerOfThree(int n) {
//	return ((n > 0) && (1162261467 % n == 0));
//}
//
//bool isPowerOfFour(int num) {
//	if (num <= 0) {
//		return false;
//	} else {
//		double x = log(num) / log(4);  //OLOLO
//		return (int)x == x;		//MATH MAGIC!!!
//	}
//}
//
//
//int findJudge(int n, vector<vector<int>>& trust) {
//	if (trust.empty() && n == 1) {
//		return 1;
//	} else if (trust.empty() && n > 1) {
//		return -1;
//	}
//
//	int judge_num = -1;
//
//	map<int, set<int>> hash_tree;
//
//	for (const auto& pair : trust) {
//		hash_tree[pair[0]].insert(pair[1]);
//	}
//
//	for (int guy = 1; guy <= n; guy++) {
//		bool trusted = true;
//		size_t ctr = 0;
//		if (hash_tree.find(guy) == hash_tree.end()) {
//			for (const auto& [peop, trusts] : hash_tree) {
//				if (trusts.find(guy) == trusts.end()) {
//					trusted = false;
//				}
//				ctr++;
//			}
//			if (trusted && ctr == n - 1) {
//				judge_num = guy;
//				break;
//			}
//		}
//	}
//	return judge_num;
//}
//
//int findJudge_2(int N, vector<vector<int>>& trust) {
//	vector<int> arr;
//	arr.resize(1005);
//
//	for (int i = 0; i < trust.size(); i++) {
//		arr[trust[i][0]]--;
//		arr[trust[i][1]]++;
//	}
//	for (int i = 1; i <= N; i++) {
//		if (arr[i] == N - 1) {
//			return i;
//		}
//	}
//	return -1;
//}
//
//
//struct Point {
//	int x = 0;
//	int y = 0;
//};
//
//bool operator==(const Point& lhs, const Point& rhs) {
//	return lhs.x == rhs.x && lhs.y == rhs.y;
//}
//
//bool operator!=(const Point& lhs, const Point& rhs) {
//	return !(lhs.x == rhs.x && lhs.y == rhs.y);
//}
//
//bool isPathCrossing(string path) {
//	vector<Point> da_way{ {0,0} };
//	for (const auto& p : path) {
//		if (p == 'N') {
//			Point tmp = *(--da_way.end());
//			tmp.x += 1;
//			auto p_serch = std::find(da_way.begin(), da_way.end(), tmp);
//			if (p_serch != da_way.end()) {
//				return true;
//			} else {
//				da_way.push_back(tmp);
//			}
//		}
//		if (p == 'E') {
//			Point tmp = *(--da_way.end());
//			tmp.y += 1;
//			auto p_serch = std::find(da_way.begin(), da_way.end(), tmp);
//			if (p_serch != da_way.end()) {
//				return true;
//			} else {
//				da_way.push_back(tmp);
//			}
//		}
//		if (p == 'S') {
//			Point tmp = *(--da_way.end());
//			tmp.x -= 1;
//			auto p_serch = std::find(da_way.begin(), da_way.end(), tmp);
//			if (p_serch != da_way.end()) {
//				return true;
//			} else {
//				da_way.push_back(tmp);
//			}
//		}
//		if (p == 'W') {
//			Point tmp = *(--da_way.end());
//			tmp.y -= 1;
//			auto p_serch = std::find(da_way.begin(), da_way.end(), tmp);
//			if (p_serch != da_way.end()) {
//				return true;
//			} else {
//				da_way.push_back(tmp);
//			}
//		}
//	}
//
//	return false;
//}
//
//bool isPalindrome(const string& x) {
//	if (x.size() == 0) {
//		return true;
//	}
//
//	for (size_t btr = 0, ept = x.size() - 1; btr < x.size() / 2; btr++, ept--) {
//		if (x[btr] != x[ept]) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void XoringSubsets(vector<vector<string>>& res, vector<string>& subset, size_t start, size_t n, const string& str) {
//	if (start >= n) {
//		res.push_back(subset);
//		return;
//	}
//
//	for (size_t ptr = start; ptr < n; ptr++) {
//		if (isPalindrome(str.substr(start, ptr - start + 1))) {
//			subset.push_back(str.substr(start, ptr - start + 1));
//			XoringSubsets(res, subset, ptr + 1, n, str);
//			subset.pop_back();
//		}
//	}
//	return;
//}
//
//vector<vector<string>> partition(string s) {
//	vector<vector<string>> res;
//	vector<string> tmp_1;
//
//	XoringSubsets(res, tmp_1, 0, s.size(), s);
//	return res;
//}
//
//bool bracers_comparator(const char& open, const char& close) {
//	if (open == 40 && close == 41) {
//		return 0;
//	}
//	if (open == 91 && close == 93) {
//		return 0;
//	}
//	if (open == 123 && close == 125) {
//		return 0;
//	}
//	return 1;
//}
//
//bool is_balanced_bracers(const std::string& data_) {
//	if (data_.size() % 2 != 0 || data_.size() == 0) {
//		return 0;
//	}
//	std::stack<char> open_bracers;
//	for (const auto& ch : data_) {
//		if (ch == '(' || ch == '{' || ch == '[') {
//			open_bracers.push(ch);
//		} else {
//			if (open_bracers.empty() || bracers_comparator(open_bracers.top(), ch)) {
//				return 0;
//			} else {
//				open_bracers.pop();
//			}
//		}
//	}
//	return 1;
//}
//
//int daysBetweenDates(string date1, string date2) {
//	std::tm dt_first = {};
//	stringstream ss_f(date1);
//	ss_f >> get_time(&dt_first, "%Y-%m-%d");
//
//	std::tm dt_second = {};
//	stringstream ss_s(date2);
//	ss_s >> get_time(&dt_second, "%Y-%m-%d");
//
//	std::time_t x = std::mktime(&dt_first);
//	std::time_t y = std::mktime(&dt_second);
//
//	double difference = std::difftime(y, x) / (60 * 60 * 24);
//	return difference;
//}
//
//namespace C_ {
//#define MAX(x,y) ((x)>(y)?(x):(y))
//#define SquareOf(x) x * x
//
//	void f(int a[]) {
//		int i;
//		a[0] = 10;
//		a[1] = 20;
//	}
//} //namespace C
//
//bool squareIsWhite(string coordinates) {
//	int x = coordinates[0] - 96;
//	int y = coordinates[1] - 48;
//
//	if (y % 2 != 0) {
//		if (x % 2 != 0) {
//			return false;
//		} else {
//			return true;
//		}
//	}
//	if (y % 2 == 0) {
//		if (x % 2 != 0) {
//			return true;
//		} else {
//			return false;
//		}
//	}
//	return false;
//}
//
//bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
//	string f;
//	string s;
//	for (size_t ptr = 0; ptr < word1.size(); ptr++) {
//		f += word1[ptr];
//
//	}
//	for (size_t ptr = 0; ptr < word2.size(); ptr++) {
//		s += word2[ptr];
//
//	}
//	return f == s;
//}
//
//int minOperations(vector<int>& nums) {
//	if (nums.size() == 1) {
//		return 0;
//	}
//
//	int res = 0;
//	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
//		if (nums[ptr] >= nums[ptr + 1]) {
//			res += (nums[ptr] - nums[ptr + 1]) + 1;
//			nums[ptr + 1] += (nums[ptr] - nums[ptr + 1]) + 1;
//		}
//	}
//
//}
//
//ListNode* mergeKLists(vector<ListNode*> lists) {
//	ListNode* res_ = nullptr;
//	vector<int> tmp_values;
//	size_t ctr = 0;
//	for (auto list : lists) {
//		while (list != nullptr) {
//			tmp_values.push_back(list->val);
//			list = list->next;
//		}
//	}
//
//	std::sort(tmp_values.begin(), tmp_values.end());
//
//	for (auto v : tmp_values) {
//		ListNode* tmp = new ListNode(v, nullptr);
//		ListNode* tmp_ptr = nullptr;
//		if (res_ == NULL) {
//			res_ = tmp;
//		} else {
//			tmp_ptr = res_;
//			while (tmp_ptr->next != NULL) {
//				tmp_ptr = tmp_ptr->next;
//			}
//			tmp_ptr->next = tmp;
//		}
//	}
//
//	return res_;
//}
//
//vector<int> findDuplicates(vector<int>& nums) {
//	map<int, int>ctr;
//	vector<int>res;
//	for (auto& ptr : nums) {
//		++ctr[ptr];
//	}
//	for (auto& ptr : ctr) {
//		if (ptr.second > 1) {
//			res.push_back(ptr.first);
//		}
//	}
//	return res;
//}
//
////----
//int finde_max_m_element(vector<int>& numbers, vector<int>& directions) {
//	int index = -1;
//	for (int p = 0; p < numbers.size(); p++) {
//		int next_index = p + directions[p];
//		if (next_index >= 0 && next_index < numbers.size()) {
//			if (numbers[p] > numbers[next_index]) {
//				if (index == -1) {
//					index = p;
//				} else {
//					if (numbers[p] > numbers[index]) {
//						index = p;
//					}
//				}
//			}
//		}
//	}
//	return index;
//}
//
//void element_swap(vector<int>& numbers, vector<int>& directions, int src, int dst) {
//	std::swap(numbers[src], numbers[dst]);
//	std::swap(directions[src], directions[dst]);
//}
//
//void change_direction_elemnt(vector<int>& numbers, vector<int>& directions, int mobile_element) {
//	for (int ptr = 0; ptr < numbers.size(); ptr++) {
//		if (numbers[ptr] > mobile_element) {
//			directions[ptr] = directions[ptr] * (-1);
//		}
//	}
//}
//
//int j_t_shuffle(vector<int>& numbers) {
//	if (numbers.empty()) {
//		return 0;
//	}
//	if (numbers.size() == 1) {
//		return 1;
//	}
//	if (numbers.size() == 2) {
//		return 2;
//	}
//	int var_ctr = 1;
//	sort(numbers.begin(), numbers.end());
//	vector<int> directions(numbers.size(), -1);
//
//	int m_index = finde_max_m_element(numbers, directions);
//	while (m_index != -1) {
//		int mob_element = numbers[m_index];
//		int next_index = m_index + directions[m_index];
//		element_swap(numbers, directions, m_index, next_index);
//		change_direction_elemnt(numbers, directions, mob_element);
//
//
//		var_ctr++;
//		m_index = finde_max_m_element(numbers, directions);
//	}
//
//	return var_ctr;
//}
////----
////KNUT-MORRIS-PRATTA
//bool repeatedSubstringPattern(string s) {
//	string res;
//	int m = 0;
//	if (s.size() <= 1) {
//		return false;
//	} else {
//		// ---- Search algorithm KNUT - MORRIS - PRATT ---- //
//		int* ref = new int[s.size()];
//		int b = 0, S = 1;
//		ref[0] = -1;
//		while (s[S]) {
//			if (s[S] == s[b]) {
//				ref[S++] = b++;
//			} else if (b == 0) {
//				ref[S++] = -1;
//			} else {
//				b = ref[b - 1] + 1;
//			}
//		}
//		delete[] ref;
//		m = S - b;
//		// ---- Search algorithm KNUT - MORRIS - PRATT ---- //
//		if (m == s.size()) {
//			return false;
//		} else {
//			int size = s.size() / m;
//			while (size) {
//				for (int ptr = 0; ptr < m; ptr++) {
//					res += s[ptr];
//				}
//				size--;
//			}
//		}
//	}
//	return res == s ? true : false;
//}
//
//string toHex(int num) {
//	string res;
//	stringstream ss;
//	ss << hex << num;
//	res = ss.str();
//	return res;
//}
//
//vector<string> subdomainVisits(vector<string>& cpdomains) {
//	vector<string> res;
//	unordered_map<string, int> SS;
//	for (string ptr : cpdomains) {
//		int spaceI = ptr.find(' ');
//		int cntr = stoi(ptr.substr(0, spaceI));
//		string rem = ptr.substr(spaceI + 1);
//		for (int i = 0; i < rem.size(); i++) {
//			if (rem[i] == '.') {
//				SS[rem.substr(i + 1)] += cntr;
//			}
//		}
//		SS[rem] += cntr;
//	}
//	for (auto ptr : SS) {
//		string tmp;
//		tmp += to_string(ptr.second);
//		tmp += ' ';
//		tmp += ptr.first;
//		res.push_back(tmp);
//	}
//	return res;
//}
//
//ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
//	if (l1 == nullptr || l2 == nullptr) {
//		if (l1 == nullptr) {
//			return l2;
//		} else {
//			return l1;
//		}
//	}
//	vector<int> values;
//
//	while (l1 != nullptr) {
//		values.push_back(l1->val);
//		l1 = l1->next;
//	}
//	while (l2 != nullptr) {
//		values.push_back(l2->val);
//		l2 = l2->next;
//	}
//	std::sort(values.begin(), values.end());
//	ListNode* res = new ListNode(values[0]);
//	ListNode* head = res;
//	for (size_t ptr = 1; ptr < values.size(); ptr++) {
//		head->next = new ListNode(values[ptr]);
//		head = head->next;
//	}
//	return res;
//}
//
//int minPairSum(vector<int>& nums) {
//	int max = INT_MIN;
//	std::sort(nums.begin(), nums.end());
//	for (size_t ptr_b = 0, ptr_e = nums.size() - 1; ptr_b < nums.size() / 2; ptr_b++, ptr_e--) {
//		if (nums[ptr_b] + nums[ptr_e] > max) {
//			max = nums[ptr_b] + nums[ptr_e];
//		}
//	}
//	return max;
//}
//
//ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
//	ListNode* begin_node = list1;
//	ListNode* end_node = list1;
//	ListNode* list2_end = list2;
//	a -= 1;
//	b += 1;
//	while (a != 0) {
//		begin_node = begin_node->next;
//		a--;
//	}
//	while (b != 0) {
//		end_node = end_node->next;
//		b--;
//	}
//	while (list2_end->next != nullptr) {
//		list2_end = list2_end->next;
//	}
//
//	ListNode* to_delete;
//	to_delete = begin_node->next;
//	while (to_delete) {
//		ListNode* deleted = to_delete;
//		delete deleted;
//		to_delete = to_delete->next;
//	}
//
//	begin_node->next = list2;
//	list2_end->next = end_node;
//	return list1;
//}
//
//struct BoxCmp {
//	bool operator()(const vector<int> a, const vector<int> b) {
//		return a[1] > b[1];
//	}
//};
//
//
//int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
//	std::sort(boxTypes.begin(), boxTypes.end(), BoxCmp());
//	size_t box_iter = 0;
//	int res = 0;
//
//	while (truckSize > 0) {
//		if (box_iter == boxTypes.size()) {
//			break;
//		}
//		if (truckSize < boxTypes[box_iter][0]) {
//			res += truckSize * boxTypes[box_iter][1];
//		} else {
//			res += boxTypes[box_iter][0] * boxTypes[box_iter][1];
//		}
//
//		truckSize -= boxTypes[box_iter][0];
//		box_iter++;
//	}
//	return res;
//}
//
//int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
//	int res = 0;
//	for (size_t ptr = 0; ptr < startTime.size(); ptr++) {
//		if ((startTime[ptr] <= queryTime) && (endTime[ptr] >= queryTime)) {
//			res++;
//		}
//	}
//	return res;
//}
//
//int maxCoins(vector<int>& piles) {
//	int res = 0;
//	std::sort(piles.begin(), piles.end());
//	for (size_t ptr = piles.size() / 3; ptr < piles.size(); ptr += 2) {
//		res += piles[ptr];
//	}
//
//	return res;
//}
//
//
//int isPrefixOfWord(string sentence, string searchWord) {
//	int res = 0;
//	int spaces = 0;
//	std::string word;
//	for (const char c : sentence) {
//		if (c == ' ') {
//			spaces++;
//			if (!word.empty()) {
//				size_t find_it = word.find(searchWord);
//				if (find_it == 0) {
//					res += spaces;
//					return ++res;
//				}
//				word.clear();
//			}
//		} else {
//			word += c;
//		}
//	}
//	if (!word.empty()) {
//		size_t find_it = word.find(searchWord);
//		if (find_it == 0) {
//			res += spaces;
//			return ++res;
//		}
//	}
//	return -1;
//}
//
//void bst(TreeNode* root, map<int, int>& result) {
//	if (root == nullptr) {
//		return;
//	}
//	std::stack<std::pair<TreeNode*, int>> hsh;
//	hsh.push({ root, 1 });
//
//	while (!hsh.empty()) {
//		std::pair<TreeNode*, int> curr_root = hsh.top();
//		hsh.pop();
//		result[curr_root.second] += curr_root.first->val;
//		if (curr_root.first->left) {
//			hsh.push({ curr_root.first->left, curr_root.second + 1 });
//		}
//		if (curr_root.first->right) {
//			hsh.push({ curr_root.first->right, curr_root.second + 1 });
//		}
//	}
//}
//
//int maxLevelSum(TreeNode* root) {
//	map<int, int> sum_level;
//	bst(root, sum_level);
//	auto pr = std::max_element(std::begin(sum_level), std::end(sum_level), [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
//		return lhs.second < rhs.second;
//		});
//	return pr->first;
//}
//
//string maximumTime(string time) {
//	size_t f_pos = time.find('?', 0);
//	while (f_pos != std::string::npos) {
//		if (f_pos == 0) {
//			if (time[f_pos + 1] > '3' && time[f_pos + 1] != '?') {
//				time[f_pos] = '1';
//			} else {
//				time[f_pos] = '2';
//			}
//		}
//		if (f_pos == 1) {
//			if (time[f_pos - 1] == '2') {
//				time[f_pos] = '3';
//			} else {
//				time[f_pos] = '9';
//			}
//
//		}
//		if (f_pos == 3) {
//			time[f_pos] = '5';
//		}
//		if (f_pos == 4) {
//			time[f_pos] = '9';
//		}
//		f_pos = time.find('?', f_pos++);
//	}
//	return time;
//}
//
//
////BAD
//int numberOfMatches(int n) {
//	int res = 0;
//	if (n == 1) {
//		return 0;
//	}
//	while (n != 1) {
//		if (n % 2 == 0) {
//			res += n / 2;
//			n /= 2;
//		} else {
//			res += (n - 1) / 2;
//			n = (n - 1) / 2 + 1;
//		}
//	}
//	return res;
//}
//
////GOOD
//int numberOfMatches_1(int n) {
//	return n - 1;
//}
//
//string truncateSentence(string s, int k) {
//	string res;
//	vector<string> words = SplitIntoWords(s);
//	if (k >= words.size()) {
//		return s;
//	}
//	for (size_t ptr = 0; ptr < k; ptr++) {
//		if (ptr != k) {
//			res += words[ptr] + ' ';
//		} else {
//			res += words[ptr];
//		}
//	}
//	return res;
//}
//
//int TwoSum(const vector<int>& elems, const int target) {
//	map<int, int> hsh;
//	for (const auto& elem : elems) {
//		int compliant = target - elem;
//		if (hsh.count(elem) > 0) {
//			return hsh.at(elem) + elem;
//		}
//		hsh[compliant] = elem;
//	}
//	return -1;
//}
//
//bool checkZeroOnes(string s) {
//	int zero_ctr = 0;
//	int one_ctr = 0;
//	if (s.find('0') == std::string::npos) {
//		return 1;
//	}
//	if (s.find('1') == std::string::npos) {
//		return 0;
//	}
//	for (size_t ptr = 0; ptr < s.size();) {
//		int tmp_one = 0;
//		int tmp_zero = 0;
//		while (s[ptr] == '1') {
//			tmp_one++;
//			ptr++;
//		}
//		while (s[ptr] == '0') {
//			tmp_zero++;
//			ptr++;
//		}
//		if (zero_ctr < tmp_zero) {
//			zero_ctr = tmp_zero;
//		}
//		if (one_ctr < tmp_one) {
//			one_ctr = tmp_one;
//		}
//	}
//	return one_ctr > zero_ctr ? 1 : 0;
//}
//
//vector<int> decompressRLElist(vector<int>& nums) {
//	vector<int> res;
//	for (size_t ptr = 0; ptr < nums.size(); ptr += 2) {
//		int ctr = nums[ptr];
//		while (ctr) {
//			res.push_back(nums[ptr + 1]);
//			ctr--;
//		}
//	}
//	return res;
//}
//
//int maxDepth(string s) {
//	if (s.find('(') == std::string::npos || s.find(')') == std::string::npos) {
//		return 0;
//	}
//	int res = 0;
//	int tmp = 0;
//	int ctr_open = 0;
//	int ctr_close = 0;
//	for (const auto& ch : s) {
//		if (ch == '(') {
//			ctr_open++;
//		} else if (ch == ')') {
//			tmp = ctr_open - ctr_close;
//			ctr_close++;
//		}
//		res = max(res, tmp);
//	}
//	res = max(res, tmp);
//	return res;
//}
//
//string toLowerCase(string s) {
//	for (auto& ch : s) {
//		if (ch >= 'A' && ch <= 'Z') {
//			ch += 32;
//		}
//	}
//	return s;
//}
////---------------------------
//struct sumestruct {
//	sumestruct(string st, size_t i, char c) {
//		num = st;
//		id = i;
//		I = c;
//	}
//	string num = "";
//	size_t id = 0;
//	char I = ' ';
//};
//
//inline static constexpr int hshr_salt = 65;
//
//struct Testhshr {
//	int operator()(const sumestruct& lhs) const {
//		return ((lhs.num.size() * lhs.id) + lhs.I) * hshr_salt;
//	}
//};
//
//struct TestComparator_word {
//	bool operator()(const pair<int, string>& lhs, const pair<int, string>& rhs) const {
//		return std::lexicographical_compare(lhs.second.begin(), lhs.second.end(), rhs.second.begin(), rhs.second.end());
//	}
//};
//
//struct TestComparator_key {
//	bool operator()(const pair<int, string>& lhs, const pair<int, string>& rhs) const {
//		return lhs.first > rhs.first;
//	}
//};
//
//struct sumestruct_id_cmp {
//	bool operator()(const sumestruct& lhs, const sumestruct& rhs) const {
//		return lhs.id > rhs.id;
//	}
//};
////---------------------------
//
//int maxProduct(vector<int>& nums) {
//	sort(nums.begin(), nums.end());
//	size_t length = nums.size();
//	return (nums[length - 2] - 1) * (nums[length - 1] - 1);
//}
//
//class SubrectangleQueries {
//public:
//	SubrectangleQueries(vector<vector<int>>& rectangle) : rectangle_coords_(rectangle) {}
//
//	void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
//		for (size_t row_ = row1; row_ <= row2; row_++) {
//			for (size_t col_ = col1; col_ <= col2; col_++) {
//				this->rectangle_coords_[row_][col_] = newValue;
//			}
//		}
//	}
//
//	int getValue(int row, int col) {
//		return this->rectangle_coords_[row][col];
//	}
//private:
//	vector<vector<int>> rectangle_coords_;
//};
//
//int minPartitions(string n) {
//	int max_ = 0;
//	for (const char ch : n) {
//		max_ = max(max_, ch - 48);
//	}
//	return max_;
//}
//
//string thousandSeparator(int n) {
//	string res = to_string(n);
//	if (res.size() < 4) {
//		return res;
//	}
//	for (int ptr = res.size() - 3; ptr > 0; ptr -= 3) {
//		res.insert(ptr, 1, '.');
//	}
//	return res;
//}
//
//vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
//	vector<int> res;
//	res.resize(queries.size());
//
//	for (size_t ptr = 0; ptr < queries.size(); ptr++) {
//		int ctr = 0;
//		for (const auto point : points) {
//			if (std::pow((point[0] - queries[ptr][0]), 2) + std::pow((point[1] - queries[ptr][1]), 2) <= std::pow(queries[ptr][2], 2)) {
//				ctr++;
//			}
//		}
//		res[ptr] = ctr;
//	}
//	return res;
//}
//
//string interpret(string command) {
//	string res;
//	auto str_ptr = command.begin();
//	while (str_ptr != command.end()) {
//		if (*str_ptr == 'G') {
//			res += *str_ptr;
//			str_ptr++;
//			continue;
//		}
//		if (*str_ptr == '(') {
//			if (*(str_ptr + 1) == ')') {
//				res += 'o';
//				str_ptr += 2;
//				continue;
//			} else {
//				res += "al";
//				str_ptr += 4;
//				continue;
//			}
//		}
//	}
//	return res;
//}
//
//bool detectCapitalUse(string word) {
//	if (word.size() == 1) {
//		return true;
//	}
//	if (word[0] >= 97) {
//		auto ptr = word.begin();
//		while (ptr != word.end()) {
//			if (*ptr < 97) {
//				return false;
//			}
//			ptr++;
//		}
//		return true;
//	}
//	if (word[0] >= 65 && word[0] <= 90) {
//		if (word[1] >= 97) {
//			auto ptr = word.begin() + 1;
//			while (ptr != word.end()) {
//				if (*ptr < 97) {
//					return false;
//				}
//				ptr++;
//			}
//			return true;
//		} else {
//			auto ptr = word.begin();
//			while (ptr != word.end()) {
//				if (*ptr > 90) {
//					return false;
//				}
//				ptr++;
//			}
//			return true;
//		}
//	}
//	return true;
//}
//
//vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
//	vector <string> res;
//	map<string, int[2]> hash;
//	for (size_t ptr1 = 0, ptr2 = 0; ptr1 < list1.size() || ptr2 < list2.size();) {
//		if (ptr1 < list1.size()) {
//			if (hash.count(list1[ptr1]) > 0) {
//				hash[list1[ptr1]][0] += 1;
//				hash[list1[ptr1]][1] += ptr1;
//			} else {
//				hash[list1[ptr1]][0] = 1;
//				hash[list1[ptr1]][1] = ptr1;
//			}
//
//			ptr1++;
//		}
//		if (ptr2 < list2.size()) {
//			if (hash.count(list2[ptr2]) > 0) {
//				hash[list2[ptr2]][0] += 1;
//				hash[list2[ptr2]][1] += ptr2;
//			} else {
//				hash[list2[ptr2]][0] = 1;
//				hash[list2[ptr2]][1] = ptr2;
//			}
//			ptr2++;
//		}
//	}
//
//	int tmp_min = INT_MAX;
//	for (const auto& [rest, ctr] : hash) {
//		if (ctr[0] > 1) {
//			if (tmp_min > ctr[1] || tmp_min == ctr[1]) {
//				if (tmp_min > ctr[1] && !res.empty()) {
//					res.clear();
//				}
//				tmp_min = ctr[1];
//				res.push_back(rest);
//			}
//		}
//	}
//	return res;
//}
//
//
//int maximumPopulation(vector<vector<int>>& logs) {
//	map<int, int> res;
//	int year_res = 0;
//	int year_summ = 0;
//	int year_summ_tmp = 0;
//	for (size_t pst = 0; pst < logs.size(); pst++) {
//		res[logs[pst][1]]--;
//		res[logs[pst][0]]++;
//	}
//
//	for (const auto& [year, ctr] : res) {
//		year_summ += ctr;
//		if (year_summ > year_summ_tmp) {
//			year_summ_tmp = year_summ;
//			year_res = year;
//		}
//	}
//
//	return year_res;
//}
//
//string licenseKeyFormatting(string s, int k) {
//	string res = s;
//	stringstream ss_res;
//	res.erase(std::remove(res.begin(), res.end(), '-'), res.end());
//	for (char& ch : res) {
//		if (std::isalpha(ch)) {
//			ch = std::toupper(ch);
//		}
//	}
//
//	if (res.size() % k != 0) {
//		for (size_t ptr = 0; ptr < res.size(); ptr++) {
//			if (ptr % k == 0 && ptr != 0) {
//				ss_res << '-';
//				ss_res << res[ptr];
//			} else {
//				ss_res << res[ptr];
//			}
//		}
//	} else {
//		int sep_tmp = 1;
//		while ((res.size() - sep_tmp) % k == 0) {
//			sep_tmp++;
//		}
//		while (sep_tmp) {
//			ss_res << res[0];
//			res = res.substr(1);
//			sep_tmp--;
//		}
//
//		for (size_t ptr = 0; ptr < res.size(); ptr++) {
//			if (ptr % k == 0) {
//				ss_res << '-';
//				ss_res << res[ptr];
//			} else {
//				ss_res << res[ptr];
//			}
//		}
//	}
//	return ss_res.str();
//}
//
//int isSubseq(string s, string t) {
//	int res = 0;
//	size_t len_s = s.size();
//	size_t ptr = 0;
//	size_t Tlen_ctr = 0;
//	for (size_t ptr1 = 0; ptr1 < t.size() && ptr < len_s;) {
//		if (t[ptr1] == s[ptr]) {
//			Tlen_ctr++;
//			if ((ptr1 == t.size() - 1 || ptr == len_s - 1) && Tlen_ctr == t.size()) {
//				res++;
//			}
//			ptr++;
//			ptr1++;
//		} else {
//			ptr++;
//		}
//	}
//	return res;
//}
//
//int numMatchingSubseq(string s, vector<string>& words) {
//	int res = 0;
//	map<string, int> hsh;
//	for (const auto& word : words) {
//		hsh[word]++;
//	}
//	for (const auto& [word, ctr] : hsh) {
//		res += (isSubseq(s, word) * ctr);
//	}
//	return res;
//}
//
//int countGoodRectangles(vector<vector<int>>& rectangles) {
//	int max_lin = 0;
//	int ctr = 0;
//	for (const auto& rect : rectangles) {
//		int tmp_miv = *(std::min_element(rect.begin(), rect.end()));
//		if (tmp_miv > max_lin) {
//			max_lin = tmp_miv;
//			ctr = 1;
//		} else if (tmp_miv == max_lin) {
//			ctr++;
//		}
//	}
//
//	return ctr;
//}
//
//int findLengthOfLCIS(vector<int>& nums) {
//	int ctr = 1;
//	for (size_t ptr = 0; ptr + 1 < nums.size(); ptr++) {
//		int tmp_ctr = 1;
//		while (ptr + 1 < nums.size() && nums[ptr] < nums[ptr + 1]) {
//			ptr++;
//			tmp_ctr++;
//		}
//		if (tmp_ctr > ctr) {
//			ctr = tmp_ctr;
//		}
//	}
//	return ctr;
////}