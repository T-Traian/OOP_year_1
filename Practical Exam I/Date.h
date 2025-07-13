#pragma once

#include <iostream>

using namespace std;

class Date {
private:
	int year;
	int month;
	int day;

public:
	Date();
	Date(int year, int month, int day);
	int getYear();
	int getMonth();
	int getDay();
	void setYear(int year);
	void setMonth(int month);
	void setDay(int day);
};