#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class DateCalculator {
private:
	int year;
	int month;
	int day;
	int changeDays;
	char op;
	char date[55];
	int monthdate[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	//You can add any variable if you need.
public:
	DateCalculator();
	void readFile(const char *filename);
	void add();
	void minus();
	bool isLeapYear(int year_);
	void showDay();
	//You can add any function if you need.
};