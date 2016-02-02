#ifndef VECTOR_H_
#define VECTOR_H_

#define nullptr, 0


template <class T>
class myVector {
private:	
//Attributes
	int capacity;
	int curSize;
	T *table;
//Internal functions needed
	void resizeTable(int n);
	void copyTable(T *oldTable, int oldSize);
public:
//Constructor
	myVector();
	myVector(int initCap);
	myVector(T *initArr, int n);
	~myVector();
//Capacity
	int size();
	int resize();
	int capacty();
	bool empty();
	void shrink_to_fit();
//Element Access
//	T operator[];
	T at(int n);
	T front();
	T back();
//Modifiers
	void push_back(T data);
	void push_front(T data);
	void clear();
};

#endif/* VECTOR_H_ */

template <class T>
myVector<T>::myVector<T>() {
	capacity = 0;
	curSize = 0;
	table = nullptr;	
}

template <class T>
myVector<T>::myVector<T>(int initCap) {
	capacity = initCap;
	curSize = 0;
	table = new T[initCap];
}

template <class T>
myVector<T>::myVector<T>(T *initArr, int n) {
	capacity = 0;
	curSize = 0;
	table = nullptr;	
	resizeTable(n);//Updates capacity as well
	copyTable(initArr, n);//Updates curSize as well
}
