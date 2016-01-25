#include "Node.h"

/*
	Will replicate a singly linked list implementation
*/
template <T>
class List {
private:	
	Node<T> *head;
	Node<T> *tail;
	int size;
public:
	List();
	~List();

	void append(T data);
	void insert(T data, int index);//Inserts a new node at index, pushing everything back
	void remove(T data);//Removes first instance of a node with matching data
	void removeAt(int index);//Removes from specified index
	void msort();//Assumes comparison operators are overloaded correctly

	bool empty();
	int getSize();
	Node<T> *front();
	Node<T> *back();
};

List::List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

List::~List(){
	if (size == 0)
		return;
	Node<T> *ptr = head;
	Node<T> *deleted;
	while (ptr == NULL) {
		deleted = ptr;
		ptr = ptr.next;
		delete deleted;
	}
}