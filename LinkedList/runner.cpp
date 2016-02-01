#include "List.h"
#include <iostream>
using namespace std;

int main() {
	List<int> myList;
	if (myList.empty())
		cout << "Empty\n";
	else
		cout << "We done goofed\n";
	

/*	myList.append(1);
	myList.append(2);
	myList.append(3);
	myList.append(4);
	myList.append(5);
	myList.append(6);
	myList.append(7);
	myList.append(8);
	myList.append(9);
*/
	myList.printList(cout);

	myList.removeAt(0);
	myList.printList(cout);

	myList.removeAt(7);
	myList.printList(cout);

}
