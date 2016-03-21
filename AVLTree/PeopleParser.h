#ifndef PEOPLEPARSER_H_
#define PEOPLEPARSER_H_
#include "Person.h"
#include <vector>
#include <sstream>
using namespace std;

Person parseLineForPerson(const string line) {
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
	return Person(first, last, day, month, year,social, state, bankBal);
}

#endif/* PEOPLEPARSER_H_ */