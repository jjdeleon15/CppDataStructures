#ifndef AVLNODE_H_
#define AVLNODE_H_

#include <stddef.h>
#define nullHeight -1

template <class T>
struct AVLNode {
	T data;
	AVLNode *left;
	AVLNode *right;
	int height;
	AVLNode(T data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
	~AVLNode() {}
	void evalHeight() {
		int l = (left != nullptr) ? left->height : nullHeight;
		int r = (right != nullptr) ? right->height : nullHeight;
		height = max(l, r) + 1;
	}
	int getBalance() {
		int l = (left != nullptr) ? left->height : nullHeight;
		int r = (right != nullptr) ? right->height : nullHeight;
		return (l - r);
	}
};

#endif /* AVLNODE_H_ */