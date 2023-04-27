#include "DateCalculator.h"

using namespace std;

DateCalculator::DateCalculator():year(2000),month(1),day(1), changeDays(0){}


void DateCalculator::readFile(const char *fileName) {
	//TODO:
	//Read the data from the txt file.
	//The file is in the Lab4_template/Lab4.
	//Hint: You can use get() to get a character in ifstream.
	//      You can use getline() to get one line in the txt file.
	//      You can use atoi() or stoi() to change variable type from string to int
	ifstream input(fileName);
	while (input >> this->op >> this->date >> this->changeDays) {
		int sum = 0, type = 0;
		for (int i = 0; i < strlen(this->date); i++) {
			if (this->date[i] == '/') {
				switch (type) {
				case 0: year = sum; break;
				case 1: month = sum; break;
				}
				sum = 0;
				type++;
			}
			else {
				sum = sum * 10 + (this->date[i] - '0');
			}
		}
		day = sum;
		if (op == '+')  add();
		else  minus();
		showDay();
		//cout << endl;
	}
	
}

void DateCalculator::add() {
	//TODO:
	//Calculate the date add the changeDays.
	int daysleft = monthdate[month]-day+1;
	for (int i = month + 1; i < 13; i++) 	daysleft += monthdate[i];	
	if (isLeapYear(year) && month <= 2)		daysleft++;
	if (changeDays >= daysleft) {
		changeDays -= daysleft;
		year++;
		month = 1;
		day = 1;
	}
	while (changeDays > 0) {
		if (month > 2) {
			if (isLeapYear(year + 1) && changeDays > 366) {
				year++;
				changeDays -= 366;
			}
			else if (!isLeapYear(year+1) && changeDays > 365) {
				year++;
				changeDays -= 365;
			}
			else {
				if (changeDays > monthdate[month]) changeDays -= monthdate[month++];
				else {
					day += changeDays;
					changeDays = 0;
					if (day > monthdate[month]) day -= monthdate[month++];
				}
			}
		}
		else if (month <= 2) {
			if (isLeapYear(year) && changeDays > 366) {
				year++;
				changeDays -= 366;
			}
			else if (!isLeapYear(year) && changeDays > 365) {
				year++;
				changeDays -= 365;
			}
			else {
				if (isLeapYear(year)&& month == 2) {
					if (changeDays > 29) {
						month++;
						changeDays -= 29;
					}
					else {
						day += changeDays;
						changeDays = 0;
						if (day > 29) {
							month++;
							day -= 29;
						}
					}
				}
				else {
					if (changeDays > monthdate[month]) changeDays -= monthdate[month++];
					else {
						day += changeDays;
						changeDays = 0;
						if (day > monthdate[month]) day -= monthdate[month++];
					}
				}
			}
		}
	}
}

void DateCalculator::minus() {
	//TODO:
	//Calculate the date minus the changeDays.
	int days = day;
	for (int i = 1; i < month; i++)			days += monthdate[i];
	if (isLeapYear(year) && month > 2)		days++;
	if (changeDays >= days) {
		changeDays -= days;
		year--;
		month = 12;
		day = 31;
	}
	day -= changeDays;
	while (day <= 0) {
		if (month <= 2) {
			if (isLeapYear(year - 1) && day < -366) {
				year--;
				day += 366;
			}
			else if (!isLeapYear(year - 1) && day < -365) {
				year--;
				day += 365;
			}
			else if (month>1)  day += monthdate[--month];
		}
		else {
			if (isLeapYear(year) && day < -366) {
				year--;
				day += 366;
			}
			else if (!isLeapYear(year) && day < -365) {
				year--;
				day += 365;
			}
			else {
				if (month == 3 && isLeapYear(year)) day += monthdate[--month] + 1;
				else day += monthdate[--month];
			}
		}
	}
}

bool DateCalculator::isLeapYear(int year_) {
	//TODO: 
	//Determine whether year_ is a leap year.
	if ((year_ % 4 == 0 && year_ % 100 != 0) || year_ % 400 == 0)
		return true;
	else
		return false;
}

void DateCalculator::showDay() {
	//TODO: 
	//The function output the date on the screen.
	//Hint: You can use setw() to set the length of the number.
	//      You can use setfill('c') to fill 'c' to the empty space.
	//      Two functions of above is in iomanip header file. 
	cout << year << "/";
	if (month < 10)
		cout << "0";
	cout << month << "/";
	if (day < 10)
		cout << "0";
	cout << day << endl;
}