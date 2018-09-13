#include<stemmer.h>

bool stemmer::unchanged(string& s, int j) {
	if(checkExceptions(s, j))
		return true;
	else {
		if(s.length() > 1 && s.at(0) == '+'){
			bool check = ambiguous(s);
			if(check){
				s = s.substr(1);
				return true;
			}else{
				string temp = "";
				temp = tolower(s.at(1));
				string rest = s.substr(2);
				temp += rest;
				s = temp;
				if(checkExceptions(s, j)){
					return true;
				}
				return false;
			}
		}
	}
	if(s.length() <= 2) return true;
	for(unsigned int i = 0; i < s.length(); i++){
		if(isupper(s.at(i)) || isdigit(s.at(i))) return true;
	}
	return false;
}

bool stemmer::checkExceptions(string& s, const int j){
	if(s.length() != 2 && map.find(s) != map.end()){
		v.at(j) = map.find(s)->second;
		return true;
	}
	return false;
		
}

bool stemmer::ambiguous(string s){
	return binary_search(unique.begin(), unique.end(), s.substr(1));
}

string stemmer::region1(const string& s) const{
	if(s == "")
		return s;
	string region1 = "";
	for(unsigned int i = 1; i < s.length() - 1; i++){
		if(!isVowel(s, i) && (isVowel(s, i-1))){
			region1 = s.substr(i+1, s.length() - i - 1);
			break;
		}
	}
	return region1;
}

string stemmer::region2(const string& s) const{
	if(region1(s) == "")
		return "";
	string region2 = "";
	unsigned int len = s.length() - region1(s).length();
	for(; len < s.length() - 1; len++){
		if(!isVowel(s, len) && (isVowel(s, len - 1))){
			region2 = s.substr(len + 1, s.length() - len - 1);
			break;
		}
	}
	return region2;
}

bool stemmer::isVowel(const string& s, const int i) const {
	char c = s.at(i);
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return true;
	else if(c == 'y') return checkY(s, i);
	return false;
}

bool stemmer::containsVowel(const string& s) const {
	for(unsigned int i = 0; i < s.length(); i++)
		if(isVowel(s, i))
			return true;
	return false;	
	
}

bool stemmer::checkY(const string& s, const int i) const{
	if(i == 0 && s.at(i) == 'y') return false;
	if(s.at(i) == 'y' && isVowel(s, i - 1)) return false;
	return true;
}

bool stemmer::isDouble(const string& s, const int i) const{
	string d = s.substr(i, 2);
	if(d == "bb" || d == "dd" || d == "ff" || d == "gg" || d == "mm" || d == "nn" || d == "pp" || d == "rr" || d == "tt") return true;
	return false;
}

bool stemmer::liEnding(const char c) const{
	return c == 'c' || c == 'd' || c == 'e' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'r' || c == 't';
}

bool stemmer::shortSyllable(const string& s) const{
	int end = s.length() - 1;
	if(s.length() == 2 && isVowel(s, 0) && !isVowel(s, 1)) return true;
	if(s.length() > 2 && s.at(end) != 'x' && s.at(end) != 'w' && s.at(end) != 'y'){
		if(!isVowel(s, end - 2) && isVowel(s, end - 1) && !isVowel(s, end))
			return true;
	}
	return false;
}

bool stemmer::Short(const string& s) const{
	if(region1(s) == "" && shortSyllable(s)) return true;
	return false;
}

string stemmer::s3p(string a) const{
	string s = "";
	if(a.length() >= 2)
		s = a.substr(a.length() - 2);
	if(s.length() >= 2 && (s == "at" || s == "bl" || s == "iz" || Short(a)))
		a += "e";
	else if(s.length() >= 2 && isDouble(s, s.length() - 2))
		a = a.substr(0, a.length() - 1);
	return a;
}

bool stemmer::s7p4(const string a) const{
	return a == "ance" || a == "ence" || a == "able" || a == "ible" || a == "ment";
}

bool stemmer::s7p3(const string a) const {
	return a == "ant" || a == "ent" || a == "ism" || a == "ate" || a == "iti" || a == "ous" || a == "ive" || a == "ize";
}

bool stemmer::s7p2(const string a) const{
	return a == "al" || a == "er" || a == "ic";
}

void stemmer::iterate(){
	string next = "";
	for(unsigned int i = 0; i < v.size(); i++){
		if(!unchanged(v.at(i), i)){
			next = Caller(v.at(i));
			if(next.length() == 0) v.erase(v.begin() + i);
			else v.at(i) = next;
		}
	}
}

string& stemmer::Caller(string& s) const{
	s = step1(s);
	s = step2(s);
	s = step3(s);
	s = step4(s);
	s = step5(s);
	s = step6(s);
	s = step7(s);
	s = step8(s);
	return s;
}


string stemmer::step1(string& s) const{
	int end = s.length() - 1;
	if(s.length() >= 1 && s.at(0) == '\''){
		s = s.substr(1);
		end = s.length() - 1;
	}
	if(s.length() >= 3 && s.substr(end - 2) == "'s'")
		return s.substr(0, end - 2);
	if(s.length() >= 2 && s.substr(end - 1) == "'s"){
		return s.substr(0, end - 1);
	}
	if(s.length() >= 1 && s.substr(end) == "'")
		return s.substr(0, end);
	return s;
}

string stemmer::step2(string& s) const{
	int end = s.length()-1;
	if(s.length() >= 4 && s.substr(end - 3) == "sses")
		return s.substr(0,end - 1);
	else if(s.length() >= 3 && (s.substr(end - 2) == "ied" || s.substr(end - 2) == "ies")){
		if(s.length() > 4){
			return s.substr(0, end - 1);
		}
		else
			return s.substr(0, end);
	}
	else if(s.length() >= 2 && (s.substr(end - 1) == "us" || s.substr(end - 1) == "ss")){
		return s;
	}
	else if(s.length() >= 3 && s.at(end) == 's'){
		for(unsigned int i = 0; i < s.length() - 2; i++)
			if(isVowel(s, i))
				return s.substr(0, end);
		return s;
	}
	return s;
}

string stemmer::step3(string& s) const{
	string r1 = region1(s);
	int end = s.length();
	if((s.length() >= 3 && s.substr(end - 3) == "eed") || (s.length() >= 5 && s.substr(end - 5) == "eedly")){
		end = r1.length() - 1;
		if(r1.length() >= 3 && r1.substr(end - 2) == "eed"){
			s = s.substr(0, s.length() - 1);
		}
		if(r1.length() >= 5 && r1.substr(end - 4) == "eedly"){
			s = s.substr(0, s.length() - 3);
		}
	}
	else if(end >= 5 && s.substr(end - 5) == "ingly" && containsVowel(s.substr(0,end - 5)))
		return s3p(s.substr(0, end - 5));
	else if(end >= 4 && s.substr(end - 4) == "edly" && containsVowel(s.substr(0,end - 4)))
		return s3p(s.substr(0, end - 4));
	else if(end >= 3 && s.substr(end - 3) == "ing" && containsVowel(s.substr(0,end - 3)))
		return s3p(s.substr(0, end - 3));
	else if(end >= 2 && s.substr(end - 2) == "ed" && containsVowel(s.substr(0,end - 2)))
		return s3p(s.substr(0, end - 2));
	return s;
}

string stemmer::step4(string& s) const{
	int end = s.length();
	if(end >= 2 && s.at(end - 1) == 'y' && !isVowel(s, end - 2) && (end - 2 != 0))
		s = s.substr(0, end - 1) + "i";	
	return s;
}

string stemmer::step5(string& s) const{
	int l = s.length();
	if(l >= 7){
		if(s.substr(l-7) == "ization" || s.substr(l-7) == "ational")
			return s.substr(0, l - 5) + "e";
		else if(s.substr(l - 7) == "fulness" || s.substr(l - 7) == "ousness" || s.substr(l - 7) == "iveness")
			return s.substr(0, l - 4);
	}
	if(l >= 6){
		if(s.substr(l - 6) == "tional" || s.substr(l - 6) == "lessli")
			return s.substr(0, l - 2);
		else if(s.substr(l - 6) == "biliti")
			return s.substr(0, l - 5) + "le";
	}
	if(l >= 5){
		string f = s.substr(l - 5);
		if(f == "entli" || f == "ousli" || f == "fulli")
			return s.substr(0, l - 2);
		else if(f == "alism" || f == "aliti")
			return s.substr(0, l - 3);
		else if(f == "ation" || f == "iviti")
			return s.substr(0, l - 3) + "e";
	}
	if(l >= 4){
		string f = s.substr(l - 4);
		if(f == "enci" || f == "anci" || f == "abli")
			return s.substr(0, l - 1) + "e";
		else if(f == "izer")
			return s.substr(0, l - 1);
		else if(f == "ator")
			return s.substr(0, l - 2) + "e";
		else if(f == "alli")
			return s.substr(0, l - 2);
		else if(f.substr(1) == "ogi" && s.at(l - 4) == 'l')
			return s.substr(0, l - 1);
	}
	if(l >= 3){
		string f = s.substr(l - 3);
		string g = s.substr(l - 2);
		char c = s.at(l - 3);
		if(f == "bli")
			return s.substr(0, l - 1) + "e";
		else if(g == "li" && liEnding(c))
			return s.substr(0, l - 2);
	}
	return s;
}

string stemmer::step6(string& s) const{
	string r1 = region1(s);
	string r2 = region2(s);
	int l = r1.length();
	int a = s.length();
	if(l >= 7 && r1.substr(l - 7) == "ational")
		return s.substr(0, a - 5) + "e";
	else if(l >= 6 && r1.substr(l - 6) == "tional")
		return s.substr(0, a - 2);
	else if(l >= 5 && (r1.substr(l - 5) == "alize" || r1.substr(l - 5) == "icate" || r1.substr(l - 5) == "iciti"))
		return s.substr(0 , a - 3);
	else if(r2.length() >= 5 && r2.substr(r2.length() - 5) == "ative")
		return s.substr(0 , a - 5);
	else if(l >= 4 && r1.substr(l - 4) == "ical")
		return s.substr(0 , a - 2);
	else if(l >= 4 && r1.substr(l - 4) == "ness")
		return s.substr(0 , a - 4);
	else if(l >= 3 && r1.substr(l - 3) == "ful")
		return s.substr(0 , a - 3);
	return s;
}

string stemmer::step7(string& s) const{
	string r1 = region1(s);
	string r2 = region2(s);
	int l = r2.length();
	int a = s.length();
	if(a >= 5 && s.substr(a - 5) == "ement"){
		if(l >= 5 && r2.substr(l - 5) == "ement")
			return s.substr(0, a - 5);
	}
	else if(a >= 4 && s7p4(s.substr(a - 4))){
		if(l >= 4 && s7p4(r2.substr(l - 4)))
			return s.substr(0, a - 4);
	}
	else if(a >= 3 && s7p3(s.substr(a - 3))){
		if(l >= 3 && s7p3(r2.substr(l - 3)))
			return s.substr(0, a - 3);
	}
	else if(a >= 2 && s7p2(s.substr(a - 2))){
		if(l >= 2 && s7p2(r2.substr(l - 2)))
			return s.substr(0, a - 2);
	}
	else if((l >= 3 && a >= 4 && r2.substr(l - 3) == "ion") && (s.at(a - 4) == 's' || s.at(a - 4) == 't')){
		return s.substr(0, a - 3);
	}
	return s;
}

string stemmer::step8(string& s) const{
	string r1 = region1(s);
	string r2 = region2(s);
	string prec = s.substr(0, s.length() - 1);
	if(r2.length() >= 1 && r2.at(r2.length() - 1) == 'l' && prec.at(prec.length() - 1) == 'l')
		return s.substr(0, s.length() - 1);
	else if((r2.length() > 0 && r2.at(r2.length() - 1) == 'e') || (r1.length() > 0 && r1.at(r1.length() - 1) == 'e' && !(shortSyllable(prec))))
		return s.substr(0, s.length() - 1);
	return s;
}
