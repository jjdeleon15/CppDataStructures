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
		height = nullHeight;
	}
	~AVLNode() {}
	void evalHeight() {
		int l = (left != nullptr) ? left->height : nullHeight;
		int r = (right != nullptr) ? right->height : nullHeight;
		height = max(l, r) + 1;
	}
};

#endif /* AVLNODE_H_ */