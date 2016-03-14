#ifndef BINTREE_H_
#define BINTREE_H_

#include "BiNode.h"
#include <ostream>
using namespace std;

template <class T>
class BinTree {
public:
	BinTree();//TEST
	~BinTree();//TEST

	void insert(T data);//TEST
	T remove(T data);//TODO
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);
private:
	BiNode<T> *root;
	int nNodes;

	BiNode<T> *insert(BiNode<T> *r, T data);//TEST
	void deleteTree(BiNode<T> *r);//TEST
	void printTree(BiNode<T> *r, bool ascending, ostream &out);
};

#endif /* BINTREE_H_ */

template <class T>
BinTree<T>::BinTree() {
	root = NULL;
	nNodes = 0;
}

template <class T>
BinTree<T>::~BinTree() {
	deleteTree(root);
}

template <class T>
void BinTree<T>::deleteTree(BiNode<T> *r) {
	if (r == NULL) return;
	deleteTree(r->left);
	deleteTree(r->right);
	delete r;
	nNodes = 0;
}	

template <class T>
void BinTree<T>::insert(T data) {
	root = insert(root, data);
}

template <class T>//fixing
BiNode<T> *BinTree<T>::insert(BiNode<T> *r, T data) {
	if (r == NULL) {
		r = new BiNode<T>(data);
		nNodes++;
	} else if (data < r->data) {//Less than, Go left
		r->left = insert(r->left, data);
	} else { //Greater than or equal, Go right
		r->right = insert(r->right, data);
	}
	return r;
}

template <class T>
bool BinTree<T>::contains(T data) {
	BiNode<T> *iter = root;
	while (iter != NULL) {
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
void BinTree<T>::printTree(bool ascending, ostream &out) {
	printTree(root, ascending, out);
}

template <class T>
void BinTree<T>::printTree(BiNode<T> *r, bool ascending, ostream &out) {
	if (r == NULL) return;
	printTree(r->left, ascending, out);
	out << r->data << endl;
	printTree(r->right, ascending, out);
}
















