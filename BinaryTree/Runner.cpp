#include <iostream>
#include <fstream>
#include "BinTree.h"
using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "usage: intTreeTest <filename> <-pd(print, print descending>\n";
		exit(-1);
	}

	ifstream fin(argv[1]);
	BinTree<int> intTree;
	string intBuff;
	while (!fin.eof()) {
		getline(fin, intBuff);
		if (fin.fail()) break;
		intTree.insert(atoi(intBuff.c_str()));
	}

	cout << "Stats\n" << "Num of Nodes: " << intTree.numOfNodes() << endl
		<< "Depth: " << intTree.depth() << endl << endl;

	if (argc != 3) return 0;

	string options(argv[2]);
	int maxInd = options.length() ;
	bool printTree = false, ascending = true;
	if (options.find('-') < maxInd) {
		if (options.find('p') < maxInd) {
			if (options.find('d') < maxInd) ascending = false;
			intTree.printTree(ascending, cout);
		}
	}

	// intTree.printTree(true, cout);


	return 0;
}