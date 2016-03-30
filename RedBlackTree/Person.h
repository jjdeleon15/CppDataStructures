#ifndef PERSON_H_
#define PERSON_H_

#include <sstream>
#include <string>
using namespace std;

class Person {
public:
	string first, last;
	int day, month, year;
	string social, state;
	double bankBal;
	string toString();
	Person(string first, string last, int day, int month, 
		int year, string social, string state, double bankBal);
	Person();//Default for template
};

bool operator<(Person &a, Person &b) {
	int comp = strcasecmp(a.last.c_str(), b.last.c_str());
	if (comp == 0) comp = strcasecmp(a.first.c_str(), b.first.c_str());
	return (comp < 0);
}
bool operator>=(Person &a, Person &b) {
	return !(a < b);
}
bool operator==(Person &a, Person &b) {
	int comp = strcasecmp(a.last.c_str(), b.last.c_str());
	if (comp == 0) comp = strcasecmp(a.first.c_str(), b.first.c_str());
	else return false;
	return (comp == 0);
}
bool operator>(Person &a, Person &b) {
	int comp = strcasecmp(a.last.c_str(), b.last.c_str());
	if (comp == 0) comp = strcasecmp(a.first.c_str(), b.first.c_str());
	return (comp > 0);
}
bool operator<=(Person &a, Person &b) {
	return !(a > b);
}
bool operator!=(Person &a, Person &b) {
	return !(a == b);
}

#endif/* PERSON_H_ */
Person::Person(string first, string last, int day, int month, 
	int year, string social, string state, double bankBal) {
	this->first = first;
	this->last = last;
	this->day = day;
	this->month = month;
	this->year = year;
	this->social = social;
	this->state = state;
	this->bankBal = bankBal;
}

Person::Person() {
	this->first = "";
	this->last = "";
	this->day = -1;
	this->month = -1;
	this->year = -1;
	this->social = "";
	this->state = "";
	this->bankBal = -1.0;
}

string Person::toString() {
	stringstream ss;
	ss << last << ", " << first << " " << day << month << year << " "
		<< state << " " << bankBal << " " << social;
	return ss.str();
}