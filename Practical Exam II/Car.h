#pragma once
#include "Vehicle.h"

class Car :public Vehicle {
private:
	int seats;
	std::string fuel;

public:
	Car();
	Car(std::string model, int year, double dailyRate, int seats, std::string fuel);

	std::string getFuel();
	int getSeats();
	void display() override;
};
