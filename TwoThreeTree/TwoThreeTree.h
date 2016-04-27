#ifndef TWOTHREETREE_H_
#define TWOTHREETREE_H_ 

#include "Node.h"
using namespace std;

template <typename T>
class B23Tree {
public:
	B23Tree();
	// ~B23Tree();

	void insert(T *data);//DONE
	bool contains(T *data);//DONE
	T *get(T *data);//DONE
	T *remove(T *data);//TODO

	void printTree(bool ascending, ostream &out);//DONE
	int numOfNodes();//DONE
	int numOfData();//DONE
	int getDepth();//DONE
	float avgDepth();
private:
	Node<T> *root;
	int nNodes;
	int nData;

	Node<T> *insert(Node<T> *iter, T *data, Node<T> *& left, T *& dataPop, Node<T> *& right);//DONE
	bool contains(Node<T> *iter, T *data);//DONE
	T *get(Node<T> *iter, T *data);//DONE
	T *remove(Node<T> *iter, T *data, Node<T> *left, T *dataPop, Node<T> *right);//TODO

	void printAscending(Node<T> * iter, ostream &out);//Done
	void printDescending(Node<T> * iter, ostream &out);//Done
	void getDepth(Node<T> *iter, int curDepth, int &max);//DONE
	void totalDepth(Node<T> *iter, int curDepth, float &total);
};

#endif

template <typename T>
B23Tree<T>::B23Tree() {
	root = nullptr;
	nNodes = 0;
	nData = 0;
}

template <typename T>
void B23Tree<T>::insert(T *data) {
	if (data == nullptr) return;	
	if (root == nullptr) {
		root = new Node<T>(data);
		nNodes += 1;
	} else {
		Node<T> *left = nullptr;
		Node<T> *right = nullptr;
		T *dataPop = nullptr;
		root = insert(root, data, left, dataPop, right);
		if (root == nullptr && dataPop != nullptr) {
			root = new Node<T>(dataPop);
			nNodes += 1;
			root->left = left;
			root->right = right;
		}
	}
	nData++;
}
template <typename T>
bool B23Tree<T>::contains(T *data) {
	return contains(root, data);
}
template <typename T>
T *B23Tree<T>::get(T * data) {
	return get(root, data);
}

template <typename T>
void B23Tree<T>::printTree(bool ascending, ostream &out) {
	
	if (ascending) 
		printAscending(root, out);
	else
		printDescending(root, out);
}
template <typename T>
int B23Tree<T>::numOfNodes() {
	return nNodes;
}
template <typename T>
int B23Tree<T>::numOfData() {
	return nData;
}
template <typename T>
int B23Tree<T>::getDepth() {
	if (root == nullptr) return 0;
	int max = 0;
	getDepth(root, 1, max);
	return max;
}
template <typename T>
void B23Tree<T>::getDepth(Node<T> *iter, int curDepth, int &max) {
	if (iter == nullptr) return;
	if (curDepth > max) max = curDepth;
	getDepth(iter->left, curDepth + 1, max);
	getDepth(iter->mid, curDepth + 1, max);
	getDepth(iter->right, curDepth + 1, max);
}
template <typename T>
float B23Tree<T>::avgDepth() {
	float total = 0;
	totalDepth(root, 1, total);
	return total / nData;
}
template <typename T>
void B23Tree<T>::totalDepth(Node<T> *iter, int curDepth, float &total) {
	if (iter == nullptr) return;
	total += (curDepth * iter->size());
	totalDepth(iter->left, curDepth + 1, total);
	totalDepth(iter->mid, curDepth + 1, total);
	totalDepth(iter->right, curDepth + 1, total);
}

template <typename T>
Node<T> *B23Tree<T>::insert(Node<T> *iter, T *data, Node<T> *& left, T *& dataPop, Node<T> *& right) {
	if (iter->isLeaf()) {
		if (iter->size() == 1) {
			iter->add(data);
			return iter;
		} else {
			if (*data < *iter->lData) {//Goes left
				left = new Node<T>(data);
				dataPop = iter->removeLeft();
				right = iter;
			} else if (*iter->rData < *data) {//Goes right
				dataPop = iter->removeRight();
				left = iter;
				right = new Node<T>(data);
			} else {//Goes middle
				dataPop = data;
				left = iter;
				right = new Node<T>(iter->removeRight());
			}
			nNodes += 1;
			return nullptr;
		}
	}
	left = nullptr;
	right = nullptr;
	dataPop = nullptr;
	if (*data < *iter->lData) {//Goes left	
		iter->left = insert(iter->left, data, left, dataPop, right);
	} else {
		if (iter->size() == 2 && *data <= *iter->rData) {//Goes in the middle
			iter->mid = insert(iter->mid, data, left, dataPop, right);
		} else {//Goes right
			iter->right = insert(iter->right, data, left, dataPop, right);
		}
	} 
	if (dataPop != nullptr) {
		if (iter->size() == 1) {
			iter->add(dataPop);
			if (iter->left == nullptr) {//Came from left
				iter->left = left;
				iter->mid = right;
			} else {//Came from right
				iter->mid = left;
				iter->right = right;
			}
			left = nullptr;
			dataPop = nullptr;
			right = nullptr;
			return iter;
		} else {
			Node<T> *tmp;
			if (iter->left == nullptr) {//Exploding from left
				tmp = new Node<T>(dataPop);
				tmp->left = left;
				tmp->right = right;
				left = tmp;
				dataPop = iter->removeLeft();
				iter->left = iter->mid;
				iter->mid = nullptr;
				right = iter;
			} else if (iter->right == nullptr) {//Exploding from right
				tmp = new Node<T>(dataPop);
				tmp->left = left;
				tmp->right = right;
				right = tmp;
				dataPop = iter->removeRight();
				iter->right = iter->mid;
				iter->mid = nullptr;
				left = iter;
			} else {//Must have come from middle
				//dataPop stays the same
				tmp = new Node<T>(iter->removeRight());
				tmp->right = iter->right;
				tmp->left = right;
				right = tmp;
				iter->right = left;
				left = iter;
			}
			nNodes++;
			return nullptr;
		}
	}
	return iter;
}
template <typename T>
bool B23Tree<T>::contains(Node<T> *iter, T *data) {
	if (iter == nullptr)
		return nullptr;
	if (*iter->lData == *data) 
		return true;
	if (iter->size() == 2 && *iter->rData == *data) 
		return true;
	if (*data < *iter->lData) 
		return contains(iter->left, data);//Go left
	if (iter->size() == 2 && *data <= *iter->rData) 
		return contains(iter->mid, data);
	else 
		return contains(iter->right, data);
}
template <typename T>
T *B23Tree<T>::get(Node<T> *iter, T *data) {
	if (iter == nullptr)
		return nullptr;
	if (*iter->lData == *data) 
		return *iter->lData;
	if (iter->size() == 2 && *iter->rData == *data) 
		return *iter->rData;
	if (*data < *iter->lData) 
		return get(iter->left, data);//Go left
	if (iter->size() == 2 && *data <= *iter->rData) 
		return get(iter->mid, data);
	else 
		return get(iter->right, data);
}
template <typename T>
void B23Tree<T>::printAscending(Node<T> *iter, ostream &out) {
	if (iter == nullptr) return;
	printAscending(iter->left, out);
	out << *iter->lData << endl;
	if (iter->size() == 2) {
		printAscending(iter->mid, out);
		out << *iter->rData << endl;
	}
	printAscending(iter->right, out);
}
template <typename T>
void B23Tree<T>::printDescending(Node<T> *iter, ostream &out) {
	if (iter == nullptr) return;
	printDescending(iter->right, out);
	if (iter->size() == 2) {
		out << *iter->rData << endl;
		printDescending(iter->mid, out);
	}
	out << *iter->lData << endl;
	printDescending(iter->left, out);
}