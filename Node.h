#pragma once 

template <class T>
struct Node {
	T data;
	Node *next;
	Node(T data) {
		this->data = data;
		next = NULL;
	}
};
