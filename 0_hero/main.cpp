#include <algorithm>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

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

int main() {

	
	for (const auto& num : getRow(1)) {
		cout << num << ' ';
	}
	cout << endl;

	return 0;
}
