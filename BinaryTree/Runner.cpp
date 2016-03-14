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



	return 0;
}