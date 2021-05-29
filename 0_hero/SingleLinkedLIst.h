#pragma once

struct LinkedList {
	explicit LinkedList() = default;
	explicit LinkedList(const int& val) : val_(val) {}

	int val_ = 0;
	LinkedList* next_ = nullptr;
};