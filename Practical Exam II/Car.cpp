#include "Car.h"

Car::Car() : Vehicle(), seats(0), fuel("") {}

Car::Car(std::string model, int year, double dailyRate, int seats, std::string fuel) : Vehicle(model, year, dailyRate), fuel(fuel) {
	try {
		if (seats > 10)
			throw std::runtime_error("Invalid number of seats!");
		else
			this->seats = seats;
	}
	catch (std::runtime_error) {
		std::cerr << "Invalid number of seats!";
	}
}

std::string Car::getFuel() {
	return fuel;
}

int Car::getSeats() {
	return seats;
}

void Car::display() {
	std::cout << model << " " << year << " " << dailyRate << " " << seats << " " << fuel << std::endl;
}