#ifndef BINODE_H_
#define BINODE_H_

#define nullHeight -1

template <typename T>
struct Node {
	T data;
	Node<T> *left;
	Node<T> *right;
	int height;
	Node(T data) {
		this->data = data;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
	~Node() {}
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

#endif/* BINODE_H_ */