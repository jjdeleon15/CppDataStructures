#ifndef AVLNODE_H_
#define AVLNODE_H_

#include <stddef.h>

template <class T>
struct AVLNode {
	T data;
	AVLNode *left;
	AVLNode *right;
	AVLNode(T data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
	~AVLNode() {}
};

#endif /* AVLNODE_H_ */