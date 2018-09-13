#include<exceptions.h>

bool exceptions::Read(istream& istr){
	string one = "";
	string two = "";
	string three = "";
	string line = "";
	
	if(istr.fail())
		return false;
	
	while(!istr.eof() && getline(istr, line)){
		istr >> std::ws;
		istringstream count(line);
		count >> one >> two;
		if(line == ""){}
		else if(one != "" && two != ""){
			if(count >> three){
				return false;
			}
			else{
				exception.insert(make_pair(one, two));
				one = "";
				two = "";
			}
		}
		else{
			return false;
		}
	}
	return true;	
}
