#pragma once
#include "Vehicle.h"

class Bike : public Vehicle {
private:
	std::string bikeType;

public:
	Bike();
	Bike(std::string model, int year, double dailyRate, std::string bikeType);

	std::string getType();

	void display() override;
};