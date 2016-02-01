#ifndef LIST_H_
#define LIST_H_

#include "Node.h"
#include <iostream>
using namespace std;

/*
	Will replicate a singly linked list implementation
*/

template <class T>
class List {
private:	
	Node<T> *head;
	Node<T> *tail;
public:
	List();
	~List();

	void append(T data);//DONE
	void insert(T data, int index);//DONE
	void remove(T data);//DONE
	void removeAt(int index);//DONE
	void msort();//Assumes comparison operators are overloaded correctly

	bool empty();//DONE
	Node<T> *front();//DONE
	Node<T> *back();//DONE
	void printList(ostream &out);//DONE, FOR DEBUGGING
};

#endif //LIST_H_

template<class T>
List<T>::List() {
        head = nullptr;
        tail = nullptr;
}

template<class T>
List<T>::~List(){
        if (head == nullptr)
                return;
        Node<T> *ptr = head;
        Node<T> *deleted;
        while (ptr != nullptr) {
                deleted = ptr;
                ptr = ptr->next;
                delete deleted;
        }
}

/*
  Always adds a new node to the end of the list
  Reassigns head and tail accordingly
*/
template<class T>
void List<T>::append(T data) {
	if (head != nullptr) {
		tail->next = new Node<T>(data);
		tail = tail->next;

	} else {
		head = new Node<T>(data);
		tail = head;
	}
}

/*
  insert shall insert a new node to the nth position
  if n is larger than the length of the list, it shall append to the end
  otherwise it shall work as any insert should
*/
template <class T>
void List<T>::insert(T data, int index) {
	Node<T> *added = new Node<T>(data);
	if (index == 0) {
		added->next = head;
		head = added;
	} else {
		Node<T> *ptr = head;
		int i = 0;
		while (ptr != nullptr && i < index) {
			ptr = ptr->next;
			i++;
		}
		if (ptr != nullptr) {
			added->next = ptr->next;
			added->data = ptr->data;
			ptr->next = added;
			ptr->data = data;	
		} else {
			this->append(data);
		}
	}
}

/*
  remove will delete the given node if it is inside the list
  the node will be deleted by saving it's next pointer, 
  copying it's next pointer to itself,
  then deleting its next pointer
  if its next pointer is NULL, then simply checking head, and tail are synced correctly
  finally, delete the darn thing
*/
template<class T>
void List<T>::remove(T data) {
	Node<T> *ptr = head;
	
	if (head == nullptr) {
		return;
	} else if (tail->data != data) {
		while (ptr != nullptr && ptr->data != data) {
			ptr = ptr->next;
		}
		if (ptr != nullptr) {
			Node<T> *temp = ptr->next;
			ptr->data = temp->data;
			ptr->next = temp->next;
			ptr = temp;
		}	
	} else {//Just for the booty
		while (ptr->next != tail) {
			ptr = ptr->next;
		}
		tail = ptr;
		ptr = tail->next;
		tail->next = nullptr;		
	}
	if (ptr != nullptr) 
		delete ptr;
}

template <class T>
void List<T>::removeAt(int index) {
	Node<T> *ptr = head;	
	if (head == nullptr) {
		return;
	} else if (index == 0) {
		head = head->next;
		delete ptr;
	} else {
		int i = 0;
		while (ptr != nullptr && i < index - 1) {
			ptr = ptr->next;
			i++;
		}
		if (ptr == nullptr) 
			return;

		Node<T> *deleted = ptr->next;
		if (deleted != tail) 
			ptr->next = deleted->next;
		else {
			tail = ptr;
			tail->next = nullptr;
		}
		delete deleted;		
	}
}

template<class T>
bool List<T>::empty(){
        if (head == nullptr)
                return true;
        else
                return false;
}

template<class T>
Node<T> *List<T>::front() {
	return head;
}

template<class T>
Node<T> *List<T>::back() {
	return tail;
}

template <class T>
void List<T>::printList(ostream &out) {
	Node<T> *ptr = head;
	while (ptr != nullptr) {
		out << ptr->data << " -> ";
		ptr = ptr->next;
	}
	out << " NULL \n";
}
