#include<similarities.h>
#include<iomanip>


double similarities::idf(const string s) const {
	double count = 0;
	multimap<string, int>::iterator it;
	for(unsigned int i = 0; i < doc.size(); i++){
		it = doc.at(i).find(s);
		if(it != doc.at(i).end())
			count++;
	}
	return log10(doc.size() / count);
}



double similarities::sim(multimap<string, int> one, multimap<string, int> two) const {
	multimap<string, int>::iterator it1;
	multimap<string, int>::iterator it2;
	double idfs = 0;
	double result = 0;
	for(it1 = one.begin(); it1 != one.end(); it1++){
		it2 = two.find(it1->first);
		if(it2 != two.end()){
			idfs = idf(it1->first);
			result += idfs * it1->second * idfs * it2->second;
		}
	}
	return result;
}

void similarities::iterate(vector<string> names, multimap<string, double>& tfidf) {
	multimap<string,double>::iterator i;
	unsigned int count = 0;
	for(i = tfidf.begin(); i != tfidf.end() && count < tfidf.size(); i++){
			tfidf.find(names.at(count)) -> second = sim(doc.at(0), doc.at(count));
			count++;
	}
}
