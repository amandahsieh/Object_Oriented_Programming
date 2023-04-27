#include <iostream>
#include <fstream>
#include "Integer.h"

using namespace std;

//read the data from the file
void readFile(const char* fileName);


int main()
{
	readFile("input1.txt");
	//cout << endl << endl;
	//readFile("input2.txt");
	//cout << endl << endl;
	//readFile("input3.txt");
	return 0;
}

void readFile(const char* fileName) {
	ifstream inputFile;
	ifstream input (fileName);
	ifstream out(fileName);
	int lines ;
	input >> lines;
	//output << lines;
	//TODO: Read the input file here.
	//int lines = ...

	for (size_t i = 0; i < lines; i++)
	{
		Integer a("0"), b("0"), answer("0");
		string line = "";
		char  op[2] = {};
		input >> line;
		//cout << line.length() << endl;
		//cout << line;
		//cout << endl;
		int k = 0;
		int second = 0;
		while (k < line.length()) {
			if (k != 0 && (line[k] == '+' || line[k] == '-')) {
				op[0] = line[k++];
				second = 1;
			}
			else if (second == 0) a.num.push_back(line[k++]);
			else b.num.push_back(line[k++]);
		}
		if (a.num[0] == '-' && op[0] == '-') {
			Integer tempa("0"), temp("0");
			for (int j = 1; j < a.num.size(); j++)
				tempa.num.push_back(a.num[j]);
			temp = tempa + b;
			answer.neg=1;
			for (int j = 0; j < temp.num.size(); j++) {
				answer.num.push_back(temp.num[j]);
			}
		}
		else if (a.num[0] == '-') {
			Integer tempa("0");
			for (int j = 1; j < a.num.size(); j++)
				tempa.num.push_back(a.num[j]);
			answer = b - tempa;
		}
		else if (op[0] == '+')
			answer = a + b;
		else
			answer = a - b;
		answer.an = 1;
		
		//TODO: Implement your add or minus
		
		//answer = a + b;
		//answer = a - b;
		
		cout << i + 1 << endl;
		cout << "num1: " << a << endl;
		cout << "num2: " << b << endl;
		cout << "result: " << answer << endl << endl;
	}

	inputFile.close();
}