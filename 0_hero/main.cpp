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
#include <stdio.h>
#include <windows.h>
#include <cstdlib>

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

int main() {
	HANDLE serial_dev;
	DCB dcbSerialParams = {0};
	serial_dev = CreateFile(TEXT("\\\\.\\COM4"), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (serial_dev == INVALID_HANDLE_VALUE) {
		cout << "Error open port\n";
	} else {
		cout << "Port opened\n";
	}
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	DWORD bytes_written;
	char buf [256];
	
	WriteFile(serial_dev, "@00040044*", 10, &bytes_written, NULL);
	
	ReadFile(serial_dev, &buf, 18, &bytes_written, NULL);
	CloseHandle(serial_dev);
	cout << buf << endl;
	cout << getData(buf, 18) << endl;
	return 0;
}
