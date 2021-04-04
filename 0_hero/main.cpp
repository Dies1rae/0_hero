#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <numeric>

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

int main() {
	vector<int> code{ 10,5,7,7,3,2,10,3,6,9,1,6 };

	for (auto& decoded : decrypt(code, -4)) {
		cout << decoded << ' ';
	}

	cout << endl;
	return 0;
}
