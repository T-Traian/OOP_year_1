#include "Vehicle.h"

Vehicle::Vehicle() : model(""), year(0), dailyRate(0.0) {}

Vehicle::Vehicle(std::string model, int year, double dailyRate): model(model), year(year) {
	try {
		if (dailyRate < 10)
			throw std::invalid_argument("Invalid daily rate!");
		else
			this->dailyRate = dailyRate;
	}
	catch (std::invalid_argument) {
		std::cerr << "Invalid daily rate!";
	}
}

void Vehicle::setDailyRate(double dailyRate) {
	try {
		if (dailyRate < 10)
			throw std::invalid_argument("Invalid daily rate!");
		else
			this->dailyRate = dailyRate;
	}
	catch (std::invalid_argument) {
		std::cerr << "Invalid daily rate!";
	}
}

double Vehicle::getDailyRate() {
	return dailyRate;
}

void Vehicle::display() {
	std::cout << model << " " << year << " " << dailyRate << std::endl;
}

void Vehicle::operator<<(Vehicle& v) {
	v.display();
}

std::string Vehicle::getModel() {
	return model;
}

int Vehicle::getYear() {
	return year;
}