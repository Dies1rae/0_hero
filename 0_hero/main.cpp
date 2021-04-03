#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <set>

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

int main() {
	string s = "01001";

	cout << minOperations(s) << endl;

	return 0;
}
