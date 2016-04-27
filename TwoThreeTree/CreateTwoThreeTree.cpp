#include <iostream>
#include <fstream>
#include "TwoThreeTree.h"
#include "Person.h"
#include "vector"
#include "sstream"
using namespace std;

Person *parseLineForPerson(const string line) {
	stringstream ss(line);
	vector<string> elems;
	std::string item;
    while (getline(ss, item, ' ')) {
        elems.push_back(item);
    }

	string social = elems[0];
	int day = stoi(elems[1].substr(0, 2));
	int month = stoi(elems[1].substr(2, 2));
	int year = stoi(elems[1].substr(4));
	string first = elems[2], last = elems[3];
	string state = elems[4];
	double bankBal = stof(elems[5]);
	return new Person(first, last, day, month, year,social, state, bankBal);
}

void invalidUsage() {
	cout << "usage: per23Tree <filename> [-pd(print, print descending] [maxEntries]\n";
	exit(-1);
}

int main(int argc, char *argv[]) {
	if (argc < 2 || argc > 4) invalidUsage();

	bool printTree = false, ascending = false;
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

	B23Tree<Person> pplTree;
	string line;
	Person *perBuff;
	ifstream fin(argv[1]);
	if (fin.fail()) {
		cout << "Could not open file: " << argv[1] << endl;
		exit(-1);	
	} 
	for (long long int i = 0; i < max; i++) {
		getline(fin, line);
		if (fin.fail()) break;
		perBuff = parseLineForPerson(line);
		pplTree.insert(perBuff);
	}
	fin.close();
	cout << "Stats: [ " << "Nodes: " << pplTree.numOfNodes() << " | Data: " << pplTree.numOfData()
		<< "| Avg Depth: " << pplTree.avgDepth() << " | MaxDepth: " << pplTree.getDepth() << " ]\n";
	if (printTree) pplTree.printTree(ascending, cout);

	//TODO add search statistics, depth is correct though
	return 0;
}