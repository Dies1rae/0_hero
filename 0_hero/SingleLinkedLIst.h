#pragma once

template <typename T>
struct LinkedList {
	explicit LinkedList() = default;
	explicit LinkedList(const T& val) : val_(val) {}
	explicit LinkedList(const T& val,LinkedList* next ) : val_(val), next_(next) {}

	T val_;
	LinkedList* next_ = nullptr;
};