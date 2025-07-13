#include "Date.h"

Date::Date() {
	this->year = 1970;
	this->month = 1;
	this->day = 1;
}

Date::Date(int year, int month, int day) {
	this->year = year;
	this->month = month;
	this->day = day;
}

int Date::getYear() {
	return this->year;
}

int Date::getMonth() {
	return this->month;
}

int Date::getDay() {
	return this->day;
}

void Date::setYear(int year) {
	if (year > 0) {
		this->year = year;
	}
	else
		cout << "Invalid year.";
}

void Date::setMonth(int month) {
	if (month > 0 and month < 13) {
		this->month = month;
	}
	else
		cout << "Invalid month";
}

void Date::setDay(int day) {
	if (day > 0 and day < 32) {
		this->day = day;
	}
	else
		cout << "Invalid day.";
}