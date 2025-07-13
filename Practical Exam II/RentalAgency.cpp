#include "RentalAgency.h"

RentalAgency::RentalAgency(std::vector<Vehicle*> vehicles) : vehicles(vehicles) {}

RentalAgency::RentalAgency(RentalAgency& r) {
	vehicles = r.vehicles;
}

RentalAgency& RentalAgency::operator=(RentalAgency& r) {
	for (auto v : vehicles) {
		delete v;
	}
	vehicles.clear();
	vehicles = r.vehicles;
	return *this;
}

void RentalAgency::operator<<(RentalAgency& r) {
	for (auto v : vehicles) {
		v->display();
	}
}

void RentalAgency::addVehicle(Vehicle* v) {
	vehicles.push_back(v);
}

std::vector<Vehicle*> RentalAgency::getVehicles() {
	return vehicles;
}

RentalAgency::~RentalAgency() {
	for (auto v : vehicles) {
		delete v;
	}
	vehicles.clear();
}