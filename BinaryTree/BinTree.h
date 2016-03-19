#ifndef BINTREE_H_
#define BINTREE_H_

#include "BiNode.h"
#include <ostream>
using namespace std;

template <class T>
class BinTree {
public:
	BinTree();//DONE
	~BinTree();//DONE

	void insert(T data);//DONE
	void remove(T data);//TODO
	bool contains(T data);//TEST
	void printTree(bool ascending, ostream &out);//DONE
	int depth();//DONE
	int numOfNodes();//DONE
private:
	BiNode<T> *root;
	int nNodes;

	BiNode<T> *insert(BiNode<T> *r, T data);//DONE
	BiNode<T> *remove(BiNode<T> *r, T data);//TODO
	void deleteTree(BiNode<T> *r);//DONE
	void printTree(BiNode<T> *r, bool ascending, ostream &out);//DONE
	void getDepth(BiNode<T> *r, int curDepth, int &maxDepth);//DONE
};

#endif /* BINTREE_H_ */

template <class T>
BinTree<T>::BinTree() {
	root = nullptr;
	nNodes = 0;
}

template <class T>
BinTree<T>::~BinTree() {
	deleteTree(root);
}

template <class T>
void BinTree<T>::deleteTree(BiNode<T> *r) {
	if (r == nullptr) return;
	deleteTree(r->left);
	deleteTree(r->right);
	delete r;
	nNodes = 0;
}	

template <class T>
void BinTree<T>::insert(T data) {
	root = insert(root, data);
}

template <class T>
BiNode<T> *BinTree<T>::insert(BiNode<T> *r, T data) {
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

template <class T>
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

template <class T>
void BinTree<T>::printTree(bool ascending, ostream &out) {
	printTree(root, ascending, out);
}

template <class T>
void BinTree<T>::printTree(BiNode<T> *r, bool ascending, ostream &out) {
	if (r == nullptr) return;
	if (ascending)	printTree(r->left, ascending, out);
	else printTree(r->right, ascending, out);
	out << r->data << endl;
	if (ascending) printTree(r->right, ascending, out);
	else printTree(r->left, ascending, out);
	
}

template <class T>
void BinTree<T>::remove(T data) {
	root = remove(root, data);
}

template <class T>
BiNode<T> *BinTree<T>::remove(BiNode<T> *r, T data) {
	if (r == nullptr) return nullptr;
	BiNode<T> *toDelete = nullptr;
	if (data == r->data) {//Found node to delete
		toDelete = r;
	} else if (data < r->data) {//Go Left
		r->left = remove(r->left, data);
	} else { //Go right
		r->right = remove(r->right, data);
	}
	if (toDelete == nullptr) return r;
	BiNode<T> *tmp = nullptr;
	if (toDelete->left != nullptr) {
		tmp = toDelete->left;
		if (tmp->right != nullptr) {
			//TODO
		} else {
			toDelete->data = tmp->data;
			toDelete->left = tmp->left;
			delete tmp;
			return toDelete;
		}
	} 
	if (toDelete->right != nullptr) {
		tmp = toDelete->right;
		if (tmp->left != nullptr) {
			//TODO
		} else {
			toDelete->data = tmp->data;
			toDelete->right = tmp->right;
			delete tmp;
			return toDelete;
		}
	} 
	delete toDelete;
	return nullptr;

}

template <class T>
int BinTree<T>::depth() {
	int maxDepth = 0;
	getDepth(root, 0, maxDepth);
	return maxDepth;
}

template <class T>
void BinTree<T>::getDepth(BiNode<T> *r, int curDepth, int &maxDepth) {
	if (r == nullptr) return;
	if (curDepth > maxDepth) maxDepth = curDepth;
	getDepth(r->left, curDepth + 1, maxDepth);
	getDepth(r->right, curDepth + 1, maxDepth);
}

template <class T>
int BinTree<T>::numOfNodes() {
	return nNodes;
}

