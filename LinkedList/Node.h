#ifndef NODE_H_
#define NODE_H_

#define nullptr 0

template <class T>
struct Node {
	T data;
	Node *next;
	Node(T data) {
		this->data = data;
		next = nullptr;
	}
};

#endif //NODE_H_
