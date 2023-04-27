#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include "Queue.h"
#include "Stack.h"
using namespace std;
int main() {
	fstream file;
	file.open("input2.txt");
	if (!file.is_open()) {
		cout << "Fail to open file" << endl;
		return 0;
	}

	int cases = 0;
	file >> cases;
	while (cases--) {
		char type;
		file >> type;
		if (type == 's' || type == 'S') {
			Stack test;
			int num;
			file >> num;
			while (num--) {
				char operation[20];
				file >> operation;
				if (operation[1] == 'u') {
					int value;
					file >> value;
					test.push(value);
				}
				else if (operation[1] == 'o') test.pop();
				else {
					cout << "The values in the stack : ";
					test.print();
				}
			}
		}
		else if (type == 'q' || type == 'Q') {
			Queue test;
			int num;
			file >> num;
			while (num--) {
				char operation[20];
				file >> operation;
				if (operation[0] == 'e') {
					int value;
					file >> value;
					test.enqueue(value);
				}
				else if (operation[0] == 'd') test.dequeue();
				else {
					cout << "The values in the queue : ";
					test.print();
				}
			}
		}
		cout << endl;
	}
}
