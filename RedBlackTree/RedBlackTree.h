#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include "BiNode.h"
#include <ostream>
using namespace std;

template <typename T>
class RedBlackTree {
public:
	RedBlackTree();//TEST
	~RedBlackTree();//TEST

	void insert(T data);//TEST
	bool remove(T data);//TEST
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);
	int depth();
	int numOfNodes();
private:
	Node<T> *root;
	int nNodes;

	Node<T> *insert(Node<T> *r, T &data);//TEST
	Node<T> *remove(Node<T> *r, T &data);//TODO
	void deleteTree(Node<T> *r);//TEST
	void printTree(Node<T> *r, bool ascending, ostream &out);//DONE
	void printAscending(Node<T> *r, ostream &out);
	void printDescending(Node<T> *r, ostream &out);
	void getDepth(Node<T> *r, int curDepth, int &maxDepth);
	Node<T> *rotate(Node<T> *r, bool left);
};

#endif /* REDBLACKTREE_H_ */

template <typename T>
RedBlackTree<T>::RedBlackTree() {
	root = nullptr;
	nNodes = 0;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
	deleteTree(root);
}

template <typename T>
void RedBlackTree<T>::deleteTree(Node<T> *r) {
	if (r == nullptr) return;
	deleteTree(r->left);
	deleteTree(r->right);
	delete r;
	nNodes = 0;
}	

/*
	r will rotate down left or right depending on the bool passed
	@returns a pointer to the node replacing r's position
*/
template <typename T>
Node<T> *RedBlackTree<T>::rotate(Node<T> *r, bool left) {
	Node<T> * tmp;
	if (left) {
		tmp = r->right;
		r->right = tmp->left;
		r->evalHeight();
		tmp->left = r;
	} else {
		tmp = r->left;
		r->left = tmp->right;
		r->evalHeight();
		tmp->right = r;
	}
	tmp->evalHeight();
	return tmp;
}

template <typename T>
void RedBlackTree<T>::insert(T data) {
	root = insert(root, data);
}

template <typename T>
Node<T> *RedBlackTree<T>::insert(Node<T> *r, T &data) {
	if (r == nullptr) {
		r = new Node<T>(data);
		nNodes++;
	} else if (data < r->data) {//Less than, Go left
		r->left = insert(r->left, data);
	} else { //Greater than or equal, Go right
		r->right = insert(r->right, data);
	}
	r->evalHeight();
	int bal = r->getBalance();
	bool left = true, right = false;
	if (bal > 1) {//Left Heavy
		if (r->left->getBalance() > 0) {//Zig-Zig:Left-Left
			r = rotate(r, right);
		} else {//Zig-Zag:Left-Right
			r->left = rotate(r->left, left);
			r = rotate(r, right);
		}
	} else if (bal < -1) {//Right Heavy
		if (r->right->getBalance() < 0) {//Zig-Zig:Right-Right
			r = rotate(r, left);
		} else {//Zig-Zag:Right-Left
			r->right = rotate(r->right, right);
			r = rotate(r, left);
		}
	}
	r->evalHeight();
	return r;
}

template <typename T>
bool RedBlackTree<T>::contains(T data) {
	Node<T> *iter = root;
	while (iter != nullptr) {
		if (iter->data == data) {
			return true;
		}  else if (data < iter->data) {//Less than, Go left
			iter = iter->left;
		} else { //Greater than or equal, Go right
			iter = iter->right;
		}
	}
	return false;
}

template <typename T>
void RedBlackTree<T>::printTree(bool ascending, ostream &out) {
	printTree(root, ascending, out);
}

template <typename T>
void RedBlackTree<T>::printTree(Node<T> *r, bool ascending, ostream &out) {
	if (ascending) printAscending(root, out);
	else printDescending(root, out);
}

template <typename T>
void RedBlackTree<T>::printAscending(Node<T> *r, ostream &out) {
	if (r == nullptr) return;
	printAscending(r->left, out);
	out << r->data.toString() << endl;
	printAscending(r->right, out);
}

template <typename T>
void RedBlackTree<T>::printDescending(Node<T> *r, ostream &out) {
	if (r == nullptr) return;
	printDescending(r->right, out);
	out << r->data.toString() << endl;
	printDescending(r->left, out);
}

template <typename T>
bool RedBlackTree<T>::remove(T data) {
	int befDel = nNodes;
	root = remove(root, data);
	if (befDel > nNodes) return true;
	else return false;
}

template <typename T>
Node<T> *RedBlackTree<T>::remove(Node<T> *r, T &data) {
	//TODO
}

template <typename T>
int RedBlackTree<T>::depth() {
	int maxDepth = 0;
	getDepth(root, 0, maxDepth);
	return maxDepth;
}

template <typename T>
void RedBlackTree<T>::getDepth(Node<T> *r, int curDepth, int &maxDepth) {
	if (r == nullptr) return;
	if (curDepth > maxDepth) maxDepth = curDepth;
	getDepth(r->left, curDepth + 1, maxDepth);
	getDepth(r->right, curDepth + 1, maxDepth);
}

template <typename T>
int RedBlackTree<T>::numOfNodes() {
	return nNodes;
}