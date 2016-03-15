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
	T remove(T data);//TODO
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);
	int depth();
	int numOfNodes();
private:
	AVLNode<T> *root;
	int nNodes;

	AVLNode<T> *insert(AVLNode<T> *r, T data);//TEST
	void deleteTree(AVLNode<T> *r);//TEST
	void printTree(AVLNode<T> *r, bool ascending, ostream &out);
	void getDepth(AVLNode<T> *r, int curDepth, int &maxDepth);
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

template <class T>
void AVLTree<T>::insert(T data) {
	root = insert(root, data);
}

template <class T>//fixing
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *r, T data) {
	if (r == nullptr) {
		r = new AVLNode<T>(data);
		nNodes++;
	} else if (data < r->data) {//Less than, Go left
		r->left = insert(r->left, data);
	} else { //Greater than or equal, Go right
		r->right = insert(r->right, data);
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
	out << r->data << endl;
	if (ascending) printTree(r->right, ascending, out);
	else printTree(r->left, ascending, out);
	
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

