#ifndef PA9_H_INCLUDE
#define PA9_H_INCLUDE

#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<stdio.h>
#include<unordered_map>
#include<map>

using std::multimap;
using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::sort;
using std::unordered_map;
using std::pair;

class PA9{
public:
	PA9(){};
	bool Read(istream& istr);
	void split(string& s);
	vector<string>& getVector();
	vector<string>& getUnique();
	void sortVector();
	bool isAllPunc(const string& s) const;
	inline multimap<string, int>& getMap(){return newMap;};
	bool Write(ostream& ostr);
	bool isNumber(const string& s) const;
	string AddaPlus(string& s, const int i);
	bool startofsentence(const int i) const;
	double Ldoc() const;
	double Sdoc() const;
	double CLdoc() const;	

protected:
	vector<string> v;
	vector<string> uniqueWords;
	multimap<string, int> newMap;
	double ldoc = 0;
	double sdoc = 0;
	double words = 0;
};
#endif
