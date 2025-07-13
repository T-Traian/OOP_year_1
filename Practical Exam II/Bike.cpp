#include "Bike.h"

Bike::Bike() : Vehicle(), bikeType("") {}

Bike::Bike(std::string model, int year, double dailyRate,std::string bikeType): Vehicle(model,year,dailyRate), bikeType(bikeType){}

void Bike::display() {
	std::cout << model << " " << year << " " << dailyRate << " " << bikeType << std::endl;
}

std::string Bike::getType() {
	return bikeType;
}