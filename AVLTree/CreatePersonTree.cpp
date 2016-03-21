#include <iostream>
#include <fstream>
#include "PeopleParser.h"
#include "AVLTree.h"
using namespace std;

Person parseLineForPerson(const string line);

void invalidUsage() {
	cout << "usage: perTreeTest <filename> [-pd(print, print descending] [maxEntries]\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 4) invalidUsage();

	bool printTree, ascending;
	long long int max = LLONG_MAX;
	string options;
	if (argc > 2) {
		options = argv[2];
		int maxInd = options.length() ;
		if (options[0] == '-') {
			printTree = (options.find('p') < maxInd) ? true : false;
			ascending = (options.find('d') < maxInd) ? false : true;
		} else {
			max = stol(argv[2]);
		}
		if (argc == 4) max = stol(argv[3]);
	} 


	ifstream fin(argv[1]);
	if (fin.fail()) exit(-1);
	AVLTree<Person> pplTree;
	string line;
	Person perBuff;
	
	for (long long int i = 0; i < max; i++) {
		getline(fin, line);
		if (fin.fail()) break;
		perBuff = parseLineForPerson(line);
		pplTree.insert(perBuff);
	}

	cout << "Stats\n" << "Num of Nodes: " << pplTree.numOfNodes() << endl
		<< "Depth: " << pplTree.depth() << endl << endl;

	if (printTree) pplTree.printTree(ascending, cout);
	

	

	fin.close();
	return 0;
}