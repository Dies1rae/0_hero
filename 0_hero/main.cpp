#include "TreeNode.h"
#include "queue.h"
#include "stack.h"
#include "priority_queue.h"
#include "vector_full_test.h"
#include "vector_simple.h"
#include "SingleLinkedList_full.h"
#include "UnionFind.h"
#include "BST.h"

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

using namespace std;



int main() {
	BinarySearchTree BST_test(5);
	BST_test.Add(6);
	BST_test.Add(4);
	BST_test.Add(10);
	BST_test.Add(1);
	BST_test.Add(7);
	BST_test.Add(8);
	BST_test.Add(20);
	BST_test.Add(2);
	BST_test.Add(0);

	cout << BST_test.IsEmpty() << ' ' << BST_test.Size() << endl;
	vector<int> test_order = BST_test.travers(BinarySearchTree<int>::OrderTraversal::inOrderTraversal);
	for (const auto& ptr : test_order) {
		cout << ptr << ' ';
	}
	cout << endl;
	test_order = BST_test.travers(BinarySearchTree<int>::OrderTraversal::preOrderTraversal);
	for (const auto& ptr : test_order) {
		cout << ptr << ' ';
	}
	cout << endl;
	test_order = BST_test.travers(BinarySearchTree<int>::OrderTraversal::postOrderTraversal);
	for (const auto& ptr : test_order) {
		cout << ptr << ' ';
	}
	cout << endl;
	test_order = BST_test.travers(BinarySearchTree<int>::OrderTraversal::levelOrderTraversal);
	for (const auto& ptr : test_order) {
		cout << ptr << ' ';
	}
	cout << endl;

	return 0;
}

