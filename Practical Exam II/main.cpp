//Tiniuc Traian-Tudor 812/2

#include "RentalAgency.h"
#include "Car.h"
#include "Bike.h"
#include <fstream>

std::string display() {
	std::cout << "Available choices:" << std::endl;
	std::cout << "1.Display all." << std::endl;
	std::cout << "2.Read info about a vehicle (car or bike) and add it to the agency's inventory." << std::endl;
	std::cout << "3.Display all vehicles of a type." << std::endl;
	std::cout << "4.Select a vehicle and display its rental charge for a given number of days." << std::endl;
	std::cout << "5.Write the agency's vehicle inventory in a text file." << std::endl;
	std::cout << "6.Exit." << std::endl;
	std::string choice;
	std::cin >> choice;
	return choice;
}

int main() {
	std::vector<Vehicle*> vehicles;
	RentalAgency agency(vehicles);
	Car* car1 = new Car("X5", 2020, 20, 4, "Diesel");
	Car* car2 = new Car("R8", 2024, 30, 4, "Gasoline");
	Car* car3 = new Car("GTR", 2019, 25, 2, "Gasoline");
	Bike* bike1 = new Bike("BMX", 2015, 15, "Street");
	agency.addVehicle(car1);
	agency.addVehicle(car2);
	agency.addVehicle(car3);
	agency.addVehicle(bike1);

	std::string choice;
	while (true) {
		choice = display();
		if (choice == "1") {
			for (auto v : agency.getVehicles()) {
				v->display();
			}
			std::cout << std::endl;
		}
		else {
			if (choice == "2") {
				std::string type;
				std::cout << "Enter the type of the vehicle:";
				std::cin >> type;
				if (type == "Car") {
					std::string model, fuel;
					int year, seats;
					double dailyRate;
					std::cin >> model >> year >> dailyRate >> seats >> fuel;
					Car* car = new Car(model, year, dailyRate, seats, fuel);
					agency.addVehicle(car);
				}
				else {
					std::string model, bikeType;
					int year;
					double dailyRate;
					std::cin >> model >> year >> dailyRate >> bikeType;
					Bike* bike = new Bike(model, year, dailyRate, bikeType);
					agency.addVehicle(bike);
				}
			}
			else {
				if (choice == "3") {
					std::string type;
					std::cout << "Please enter type:";
					std::cin >> type;
					if (type == "Car") {
						std::vector<Car*> cars;
						for (auto v : agency.getVehicles()) {
							Car* car = dynamic_cast<Car*>(v);
							if (car)
								cars.push_back(car);
						}
						for (auto c : cars) {
							c->display();
						}
					}
					else
						if (type == "Bike") {
							std::vector<Bike*> bikes;
							for (auto v : agency.getVehicles()) {
								Bike* bike = dynamic_cast<Bike*>(v);
								if (bike)
									bikes.push_back(bike);
							}
							for (auto b : bikes) {
								b->display();
							}
						}
				}
				else {
					if (choice == "4") {
						std::string model;
						std::cout << "Enter the model of the vehicle:";
						std::cin >> model;
						int days;
						std::cout << "Enter the days:";
						std::cin >> days;
						for (auto v : agency.getVehicles()) {
							if (v->getModel() == model) {
								std::cout << v->getDailyRate() * days<<std::endl;
								break;
							}
						}
					}
					else {
						if (choice == "5") {
							try {
								std::string path;
								std::cout << "Please enter file type:";
								std::cin >> path;
								std::ofstream file(path);
								if (!file.is_open()) {
									throw std::exception();
								}
								else {
									for (auto v : agency.getVehicles()) {
										file << v->getModel() << " " << v->getYear() << " " << v->getDailyRate();
										Car* car = dynamic_cast<Car*>(v);
										if (car) {
											file << car->getSeats() << " " << car->getFuel();
										}
										else {
											Bike* bike = dynamic_cast<Bike*>(v);
											file << bike->getType();
										}
									}
								}
								file.close();
							}
							catch (std::exception()) {
								std::cerr << "Invalid file path.";
							}
						}
						else {
							if (choice == "6")
								break;
						}
					}
					}
				}
			}
		}

		agency.~RentalAgency();
	}