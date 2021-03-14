#include <algorithm>
#include <vector>
#include <iostream>

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
	int sides = 1;
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

int main() {
	vector<int> prices = { 7,1,5,3,6,4 };
	cout << maxProfit(prices) << endl;

	int nums = 1;
	for(auto ptr : Pascal_Triangle(nums)) {
		for (auto ptr2 : ptr) {
			cout << ptr2 << ' ';
		}
		cout << endl;
	}


	return 0;
}
