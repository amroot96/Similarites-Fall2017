#include<PA9.h>
#include<stemmer.h>
#include<exceptions.h>
#include<similarities.h>
#include<iostream>
#include<fstream>
#include<unordered_set>
#include<map>

using std::map;
using std::unordered_set;
using std::cout;
using std::endl;
using std::ifstream;

int WrongFormat(char* arg0)
{
	cout << "Usage: " << arg0 << " exceptions" << endl;
	cout << "Exception file does not have the correct format." << endl;
	return -1;
}

int FailtoRead(char* arg0)
{
	cout << "Usage: " << arg0 << " testFile" << endl;
	cout << "Test file failed to read." << endl;
	return -1;
}

int IncArgs(char* arg0)
{
	cout << "Usage: " << arg0 << endl;
	cout << "Incorrect number of arguments." << endl;
	return -1;
}

int FailtoOpen(char* arg0)
{
	cout << "Usage: " << arg0 << endl;
	cout << "Failed to open file." << endl;
	return -1;
}

int main(int argc, char* argv[])
{
	unordered_map<string, double> CLs;
	vector<multimap<string, int> > documents;
	multimap<string, double> tfidf;
	vector<string> names;

	if(argc != 5) return IncArgs(argv[0]);
	
	ifstream istr1(argv[1]);
	if(istr1.fail()) return FailtoOpen(argv[1]);

	tfidf.insert(pair<string,double>(argv[1], 0));

	PA9 compare; //Read in the file we will be comparing to
	if(!compare.Read(istr1)) return FailtoRead(argv[1]);
 	
	CLs.insert(pair<string, double>(argv[1], compare.CLdoc()));
	names.push_back(argv[1]);

	ifstream istr2(argv[2]);
	if(istr2.fail()) return FailtoOpen(argv[2]);

	string file = "";
	istr2 >> file;
	
	ifstream exc(file);
	exceptions excep;
	if(!excep.Read(exc)) return WrongFormat(argv[2]);
	
	stemmer s(compare.getVector(), compare.getUnique(), excep.getMap());
	s.iterate();
	compare.Write(cout);
	documents.push_back(compare.getMap());
	
	istr2 >> file;
	if(istr2.eof()){
		cout << "No background documents available." << endl;
		return -1;
	}
	while(!istr2.eof()){
		if(istr2.fail()) return FailtoOpen(argv[2]);
		tfidf.insert(pair<string, double>(file, 0));
		ifstream istr3(file); //test file
		if(istr3.fail()) return FailtoOpen(argv[0]);
		
		PA9 test;
		if(!test.Read(istr3)) return FailtoRead(argv[0]);
		
		//cout << test.CLdoc() << endl;
		CLs.insert(pair<string, double>(file, test.CLdoc()));

		stemmer stem(test.getVector(), test.getUnique(), excep.getMap());
		
		stem.iterate();
		//test.sortVector();
		test.Write(cout);
		documents.push_back(test.getMap());
		names.push_back(file);
		
		istr2 >> file;
	}
	
	double low, high;
	try{
		low = stod(argv[3]);
		if(low < 0){		
			cout << "Fail to attain lowest reading level" << endl;
			return -1;
		}
	}catch(std::invalid_argument){
		cout << "Invalid low reading level entered." << endl;
		return -1;
	}

	try{
		high = stod(argv[4]);
		if(high < 0 || high < low){
			cout << "Fail to attain highest reading level." << endl;
			return -1;
		}
	} catch(std::invalid_argument) {
		cout << "Invalid highest reading level entered." << endl;
		return -1;
	}

	similarities find(documents);
	find.iterate(names, tfidf);
	
	string match = "";
	double max = 0;
	unordered_map<string, double>::iterator i;
	for(i = CLs.begin(); i != CLs.end(); i++){
		if(i -> second >= low && i -> second <= high){
			if(tfidf.find(i -> first) -> second > max){
				match = i ->first;
				max = tfidf.find(i -> first) -> second;
			}
		}
	}
	if(match == ""){
		cout << "No matching files." << endl;
		return 0;
	}
	else{
		cout << match << endl;
	}
	return 0;
}
