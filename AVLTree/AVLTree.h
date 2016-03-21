#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "AVLNode.h"
#include <ostream>
using namespace std;

template <class T>
class AVLTree {
public:
	AVLTree();//TEST
	~AVLTree();//TEST

	void insert(T data);//TEST
	bool remove(T data);//TEST
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);
	int depth();
	int numOfNodes();
private:
	AVLNode<T> *root;
	int nNodes;

	AVLNode<T> *insert(AVLNode<T> *r, T &data);//TEST
	AVLNode<T> *remove(AVLNode<T> *r, T &data);//TODO
	void deleteTree(AVLNode<T> *r);//TEST
	void printTree(AVLNode<T> *r, bool ascending, ostream &out);
	void getDepth(AVLNode<T> *r, int curDepth, int &maxDepth);
	AVLNode<T> *rotate(AVLNode<T> *r, bool left);
};

#endif /* AVLTREE_H_ */

template <class T>
AVLTree<T>::AVLTree() {
	root = nullptr;
	nNodes = 0;
}

template <class T>
AVLTree<T>::~AVLTree() {
	deleteTree(root);
}

template <class T>
void AVLTree<T>::deleteTree(AVLNode<T> *r) {
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
template <class T>
AVLNode<T> *AVLTree<T>::rotate(AVLNode<T> *r, bool left) {
	AVLNode<T> * tmp;
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

template <class T>
void AVLTree<T>::insert(T data) {
	root = insert(root, data);
}

template <class T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *r, T &data) {
	if (r == nullptr) {
		r = new AVLNode<T>(data);
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
	return r;
}

template <class T>
bool AVLTree<T>::contains(T data) {
	AVLNode<T> *iter = root;
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

template <class T>
void AVLTree<T>::printTree(bool ascending, ostream &out) {
	printTree(root, ascending, out);
}

template <class T>
void AVLTree<T>::printTree(AVLNode<T> *r, bool ascending, ostream &out) {
	if (r == nullptr) return;
	if (ascending)	printTree(r->left, ascending, out);
	else printTree(r->right, ascending, out);
	out << r->data.toString() << endl;
	if (ascending) printTree(r->right, ascending, out);
	else printTree(r->left, ascending, out);
	
}

template <class T>
bool AVLTree<T>::remove(T data) {
	int befDel = nNodes;
	root = remove(root, data);
	if (befDel > nNodes) return true;
	else return false;
}

template <class T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *r, T &data) {
	//TODO
}

template <class T>
int AVLTree<T>::depth() {
	int maxDepth = 0;
	getDepth(root, 0, maxDepth);
	return maxDepth;
}

template <class T>
void AVLTree<T>::getDepth(AVLNode<T> *r, int curDepth, int &maxDepth) {
	if (r == nullptr) return;
	if (curDepth > maxDepth) maxDepth = curDepth;
	getDepth(r->left, curDepth + 1, maxDepth);
	getDepth(r->right, curDepth + 1, maxDepth);
}

template <class T>
int AVLTree<T>::numOfNodes() {
	return nNodes;
}