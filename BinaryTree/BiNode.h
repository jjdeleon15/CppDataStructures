#ifndef BINODE_H_
#define BINODE_H_

#include <stddef.h>

template <class T>
struct BiNode {
	T data;
	BiNode *left;
	BiNode *right;
	BiNode(T data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
	~BiNode() {}
};

#endif /* BINODE_H_ */