#pragma once

#ifndef NODE_H_
#define NODE_H_ 

/**
Node will be a node for any 2-3 tree node
	data will be stored in lData unless it is a 3 node
	the pointers will be stored in left and right
	the mid pointer can only be used if it is a 3 node
 */
template <typename T>
struct Node {
	T *lData, *rData;
	Node<T> *left, *mid, *right;
	Node(T *data){
		lData = data;
		rData = nullptr;
		left = nullptr;
		mid = nullptr;
		right = nullptr;
	}
	int size() {
		int size = 0;
		if (lData != nullptr)
			size++;
		if (rData != nullptr)
			size++;
		return size;
	}
	bool isLeaf() {
		return (left == nullptr && mid == nullptr && right == nullptr);
	}
	void add(T *data) {
		if (*data < *lData) {
			rData = lData;
			lData = data;
		} else {
			rData = data;
		}
	}
	T *removeLeft() {//Assumes it is a 3 node
		T *l = lData;
		lData = rData;
		rData = nullptr;
		return l;
	}
	T *removeRight() {
		T *r = rData;
		rData = nullptr;
		return r;
	}
};

#endif