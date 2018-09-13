#ifndef similarities
#define similarities_H_INCLUDE

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>
#include<vector>
#include<stdio.h>
#include<math.h>
#include<iomanip>
#include<map>
#include<algorithm>

using std::map;
using std::vector;
using std::string;
using std::unordered_map;
using std::endl;
using std::cout;
using namespace std;


class similarities{	
public:
	similarities(vector<multimap<string, int> >& map): doc(map){};
	
	double idf(const string s) const;
	void iterate(vector<string> names, multimap<string, double>& tfidf);
	double sim(multimap<string, int> one,multimap<string, int> two) const;
 
protected:
	vector<multimap<string, int> >& doc;
};
#endif
