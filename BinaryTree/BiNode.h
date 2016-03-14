#ifndef BINODE_H_
#define BINODE_H_

template <class T>
struct BiNode {
	T data;
	BiNode *left;
	BiNode *right;
	BiNode(T data) {
		this->data = data;
		left = NULL;
		right = NULL;
	}
	~BiNode() {}
};

#endif /* BINODE_H_ */