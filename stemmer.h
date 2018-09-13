#ifndef stemmer_H_INCLUDE
#define stemmer_H_INCLUDE

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctype.h>
#include<stdio.h>
#include<unordered_map>
#include<algorithm>

using std::binary_search;
using std::iostream;
using std::ostream;
using std::vector;
using std::string;
using std::unordered_map;

class stemmer{
public:
	stemmer(vector<string>& before,vector<string>& x, unordered_map<string, string>& m) : v(before), unique(x), map(m) {};
	
	bool unchanged(string& s, int j);
	bool ambiguous(string s);
	string region1(const string& s) const;
	string region2(const string& s) const;
	bool isVowel(const string& s, const int i) const;
	bool containsVowel(const string& s) const;
	bool checkY(const string& s, const int i) const;
	bool isDouble(const string& s, const int i) const;
	bool liEnding(const char c) const;
	bool shortSyllable(const string& s) const;
	bool Short(const string& s) const;
	string s3p(string s) const;
	bool s7p4(const string s) const;
	bool s7p3(const string s) const;
	bool s7p2(const string s) const;
	string& Caller(string& s) const;
	string step1(string& s) const;
	string step2(string& s) const;
	string step3(string& s) const;
	string step4(string& s) const;
	string step5(string& s) const;
	string step6(string& s) const;
	string step7(string& s) const;
	string step8(string& s) const;
	
	void iterate();
	
	bool checkExceptions(string& s, const int j);
	
protected:
	vector<string>& v;
	vector<string>& unique;
	unordered_map<string, string>& map;

};
#endif
