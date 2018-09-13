#ifndef exceptions_H_INCLUDE
#define exceptions_H_INCLUDE

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>

using std::istream;
using std::ostream;
using std::string;
using std::unordered_map;
using std::make_pair;
using std::move;
using std::getline;
using namespace std;

class exceptions{
public:
	exceptions(){};
	bool Read(istream& istr);
	inline unordered_map<string, string>& getMap(){return exception;};

protected:
	unordered_map<string, string> exception;
};
#endif
