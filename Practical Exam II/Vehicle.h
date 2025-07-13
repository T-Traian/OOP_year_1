#pragma once
#include <iostream>
#include<string>

class Vehicle {
protected:
	std::string model;
	int year;
	double dailyRate;

public:
	Vehicle();
	Vehicle(std::string model, int year, double dailyRate);

	std::string getModel();
	int getYear();
	void setDailyRate(double dailyRate);
	double getDailyRate();


	virtual void display();
	void operator<<(Vehicle& v);


};