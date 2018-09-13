#include<PA9.h>


void PA9::split(string& s){
	string temp = "";
	bool eos = false;
	for(unsigned int i = 0; i < s.length();){
		if(s.at(i) == '.' && i == 0 && s.length() > 1 && isdigit(s.at(i+1))){
			temp += s.at(i);
			++i;
		}
		if(isalpha(s.at(i)) || isdigit(s.at(i)) || s.at(i) == '\''){
			while(i < s.length() && (isalpha(s.at(i)) || isdigit(s.at(i)) || s.at(i) == '\'')){
				temp += s.at(i);
				++i;
				if(i < s.length()){
					char c = s.at(i);
					if(c == '.' || c == ','){
						if(i < s.length() - 1 && isdigit(s.at(i-1)) && isdigit(s.at(i+1))){
							temp += c;
							++i;
						}
					}
				}

			}
			ldoc += temp.length();
			words += 1;
			v.push_back(temp);
			temp = "";
		}
		else{
			while(i < s.length() && (!isalpha(s.at(i)) && !isdigit(s.at(i)) && s.at(i) != '\'')){
				if(s.at(i) == '.' || s.at(i) == '?' || s.at(i) == '!')
					eos = true;
				temp += s.at(i);
				++i;
			}
			if(eos){
				sdoc += 1;
				eos = false;
			}
			v.push_back(temp);
			temp = "";
		}
	}
}

bool PA9::isNumber(const string& s) const{
	return s.find_first_not_of("0123456789") == string::npos;
}


string PA9::AddaPlus(string& s, const int i){
	string first = s.substr(0,1);
	string end = s.substr(1, s.length() - 1);
	if(isupper(first.at(0))){
		if(startofsentence(i)){
			if(end.length() == 0)
				return "+" + s;
			for(unsigned int j = 0; j < end.length(); j++){ 
				if(!islower(end.at(j))){
					if(end.at(j) != '\'')
						return s;
				}
			}
			return "+" + s;
		}
	}
	return s;
}

bool PA9::startofsentence(const int i) const{
	if(i == 0)
		return true;
	string temp = v.at(i - 1);
	if(isAllPunc(temp)){
		for(unsigned int k = 0; k < temp.length(); k++){
			if(temp.at(k) == '.' || temp.at(k) == '?' || temp.at(k) == '!'){
				return true;
			}
		}
	}
	return false;
}

bool PA9::isAllPunc(const string& s) const{
	for(unsigned int i = 0; i < s.length(); i++){
		if(s.at(i) == '\'' || isalnum(s.at(i))){
			return false;
		}
	}
	return true;
}

double PA9::Sdoc() const {
	return sdoc/words*100;
}

double PA9::Ldoc() const {
	return ldoc/words*100;
}

double PA9::CLdoc() const {
	if(words == 0){
		return -1;
	}
	else{
		return 0.0588 * Ldoc() - 0.296 * Sdoc() - 15.8;
	}
}

vector<string>& PA9::getVector(){
	return v;
}

vector<string>& PA9::getUnique(){
	return uniqueWords;
}

void PA9::sortVector(){
	sort(v.begin(), v.end());
}

bool PA9::Read(istream& istr)
{
	string next = "";
	istr >> next;
	if(istr.eof()) return false;
	while(!istr.eof())
	{
		split(next);
		if(istr.fail()) return false;
		istr >> next;
	}
	for(unsigned int i = 0; i < v.size(); i++){
		string s = v.at(i);
		v.at(i) = AddaPlus(s, i);
	}
	vector<string>::iterator i;
	uniqueWords.assign(v.begin(), v.end());
	sort(uniqueWords.begin(), uniqueWords.end());
	i = unique(uniqueWords.begin(), uniqueWords.end());
	uniqueWords.resize(distance(uniqueWords.begin(), i));
	return true;
}

bool PA9::Write(ostream& ostr)
{
	int temp = 1;
	string a = "";
	char c, d;
	sortVector();
	for(unsigned int i = 0; i < v.size(); ++i){
		a = v.at(i);
		c = a.at(0);
		if(a.length() > 1)
			d = a.at(1);
		if(c == '\'' || isdigit(c) || isupper(c) || islower(c) || (a.length() > 1 && c == '.' && isdigit(d))){
			if((i < (v.size() - 1)) && v.at(i) == v.at(i+1)){
				temp++;
				if(i == (v.size() - 2)){
					newMap.insert(pair<string, int>(a, temp));
					//ostr << v.at(i) << " " << temp << std::endl;
					return true;
				}
			}
			else{
				newMap.insert(pair<string, int>(a, temp));
				//ostr << v.at(i) << " " << temp << std::endl;
				temp = 1;
			}
		}
	}
return true;
}
