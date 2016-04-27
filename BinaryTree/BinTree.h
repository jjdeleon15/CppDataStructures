#ifndef BINTREE_H_
#define BINTREE_H_

#include "BiNode.h"
#include <ostream>
using namespace std;

template <typename T>
class BinTree {
public:
	BinTree();//TEST
	~BinTree();//TEST

	void insert(T data);//TEST
	bool remove(T data);//TEST
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);
	int depth();
	float avgDepth();
	int numOfNodes();
private:
	BiNode<T> *root;
	int nNodes;

	BiNode<T> *insert(BiNode<T> *r, T &data);//TEST
	BiNode<T> *remove(BiNode<T> *r, T &data);//TODO
	void deleteTree(BiNode<T> *r);//TEST
	void printTree(BiNode<T> *r, bool ascending, ostream &out);//DONE
	void printAscending(BiNode<T> *r, ostream &out);
	void printDescending(BiNode<T> *r, ostream &out);
	void getDepth(BiNode<T> *r, int curDepth, int &maxDepth);
	void totalDepth(BiNode<T> *r, int curDepth, float &total);
	BiNode<T> *rotate(BiNode<T> *r, bool left);
};

#endif /* BINTREE_H_ */

template <typename T>
BinTree<T>::BinTree() {
	root = nullptr;
	nNodes = 0;
}

template <typename T>
BinTree<T>::~BinTree() {
	deleteTree(root);
}

template <typename T>
void BinTree<T>::deleteTree(BiNode<T> *r) {
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
BiNode<T> *BinTree<T>::rotate(BiNode<T> *r, bool left) {
	BiNode<T> * tmp;
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
void BinTree<T>::insert(T data) {
	root = insert(root, data);
}

template <typename T>
BiNode<T> *BinTree<T>::insert(BiNode<T> *r, T &data) {
	if (r == nullptr) {
		r = new BiNode<T>(data);
		nNodes++;
	} else if (data < r->data) {//Less than, Go left
		r->left = insert(r->left, data);
	} else { //Greater than or equal, Go right
		r->right = insert(r->right, data);
	}
	return r;
}

template <typename T>
bool BinTree<T>::contains(T data) {
	BiNode<T> *iter = root;
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
void BinTree<T>::printTree(bool ascending, ostream &out) {
	printTree(root, ascending, out);
}

template <typename T>
void BinTree<T>::printTree(BiNode<T> *r, bool ascending, ostream &out) {
	if (ascending) printAscending(root, out);
	else printDescending(root, out);
}

template <typename T>
void BinTree<T>::printAscending(BiNode<T> *r, ostream &out) {
	if (r == nullptr) return;
	printAscending(r->left, out);
	out << r->data.toString() << endl;
	printAscending(r->right, out);
}

template <typename T>
void BinTree<T>::printDescending(BiNode<T> *r, ostream &out) {
	if (r == nullptr) return;
	printDescending(r->right, out);
	out << r->data.toString() << endl;
	printDescending(r->left, out);
}

template <typename T>
bool BinTree<T>::remove(T data) {
	int befDel = nNodes;
	root = remove(root, data);
	if (befDel > nNodes) return true;
	else return false;
}

template <typename T>
BiNode<T> *BinTree<T>::remove(BiNode<T> *r, T &data) {
	//TODO
}

template <typename T>
int BinTree<T>::depth() {
	int maxDepth = 0;
	getDepth(root, 0, maxDepth);
	return maxDepth;
}

template <typename T>
void BinTree<T>::getDepth(BiNode<T> *r, int curDepth, int &maxDepth) {
	if (r == nullptr) return;
	if (curDepth > maxDepth) maxDepth = curDepth;
	getDepth(r->left, curDepth + 1, maxDepth);
	getDepth(r->right, curDepth + 1, maxDepth);
}

template <typename T>
int BinTree<T>::numOfNodes() {
	return nNodes;
}

template <typename T>
float BinTree<T>::avgDepth() {
	if (root == nullptr) return 0;
	float total = 0;
	totalDepth(root, 1, total);
	return total / nNodes;
}
template <typename T>
void BinTree<T>::totalDepth(BiNode<T> *r, int curDepth, float &total) {
	if (r == nullptr) return;
	total += curDepth;
	totalDepth(r->left, curDepth + 1, total);
	totalDepth(r->right, curDepth + 1, total);
}