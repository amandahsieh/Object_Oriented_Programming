#include <iostream>
#include "DateCalculator.h"
using namespace std;


int main() {
	DateCalculator calculator;
	//cout << "calculate the trial text" << endl;
	calculator.readFile("input_HIDDEN.txt");
	cout << endl;//<< "calculate the input1 text" << endl;
	calculator.readFile("input1.txt");
	cout << endl;//<< "calculate the input2 text" << endl;
	calculator.readFile("input2.txt");

	system("PAUSE");
	return 0;
}
