#pragma once
#include "Vehicle.h"
#include <vector>

class RentalAgency {
private:
	std::vector<Vehicle*> vehicles;

public:
	RentalAgency() = default;
	RentalAgency(std::vector<Vehicle*> vehicles);
	RentalAgency(RentalAgency& r);
	RentalAgency& operator=(RentalAgency& r);

	void operator<<(RentalAgency& r);

	void addVehicle(Vehicle* v);
	std::vector<Vehicle*> getVehicles();

	~RentalAgency();
};