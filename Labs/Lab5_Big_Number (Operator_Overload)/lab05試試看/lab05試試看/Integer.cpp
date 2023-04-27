#include "Integer.h"

Integer::Integer(string number) 
{
	
	//TODO: read the string and construct the huge integer
}

Integer Integer::operator +(const Integer& b) {
	Integer s1=*this,s2= b;
	
	if (s1.num.size() < s2.num.size()) 	swap(s1, s2);
	for (int j=1 ; j<= s2.num.size();j++){
		if ('a' <= s2.num[s2.num.size() - j]&& s2.num[s2.num.size() - j] <= 'f')
			s1.num[s1.num.size() - j] += (s2.num[s2.num.size() - j] - 'a' + 10);
		else
			s1.num[s1.num.size() - j] += (s2.num[s2.num.size() - j] - '0');
		if (s1.num[s1.num.size() - j] > '9' && s1.num[s1.num.size() - j] <= ('9' + 32))
			s1.num[s1.num.size() - j] = 'a' + (s1.num[s1.num.size() - j] - '9' - 1);

		if ('f' < s1.num[s1.num.size() - j] && s1.num[s1.num.size() - j] <= 'z') {
			s1.num[s1.num.size() - j - 1] += 1;
			int k = s1.num[s1.num.size() - j] - 'f'-1;
			if (k > 9)
				s1.num[s1.num.size() - j] = 'a' + (k - 10);
			else
				s1.num[s1.num.size() - j] = '0' + k;
		}
	}
	return s1;
	//TODO: perform + opearion overloading
}
Integer Integer::operator -(const Integer& b) {
	Integer s1 =*this, s2 = b;
	if (s1.num.size() < s2.num.size() || (s1.num.size() == s2.num.size() && s1.num < s2.num)) {
		swap(s1, s2);
		s1.neg = 1;
	}
	for (int j = 1; j <= s2.num.size(); j++) {
		if ('a' <= s2.num[s2.num.size() - j] && s2.num[s2.num.size() - j] <= 'f')
			s1.num[s1.num.size() - j] -= (s2.num[s2.num.size() - j] - 'a' + 10);
		else
			s1.num[s1.num.size() - j] -= (s2.num[s2.num.size() - j] - '0');
		if (s1.num[s1.num.size() - j] < 'a' && s1.num[s1.num.size() - j]>'9') {
			s1.num[s1.num.size() - j] = '9' + (s1.num[s1.num.size() - j] - 'a') + 1;
		}
		if (s1.num[s1.num.size() - j] < '0') {
			s1.num[s1.num.size() - j - 1] -= 1;
			s1.num[s1.num.size() - j] += 16;
			if (s1.num[s1.num.size() - j]>'9')
				s1.num[s1.num.size() - j] = 'a' + s1.num[s1.num.size() - j]-'9'-1;
		}
	}
	return s1;
	//TODO: perform - opearion overloading
}

ostream& operator << (ostream& out, const Integer& i) {
	int start = 0;
	if (i.an == 1) {
		while (start < i.num.size()) {
			if (i.num[start] != '0')
				break;
			else
				start++;
		}
	}
	
	if (start == i.num.size()) {
		out << '0';
	}
	else {
		if (i.neg == 1)
			out << "-";
		for (int j = start; j < i.num.size(); j++)
			out << i.num[j];
	}
	return out;
	//TODO: perform output overloading
}
