/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

using namespace std;

template <class Vehicle>
class Garage {
	vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
	public:
		NoSuchVehicleException() { }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle) {
	for (auto v : vehicles)
		if (v->getBrand() == vehicle->getBrand() && v->getModel() == vehicle->getModel())
			return false;

	if (vehicles.size() < capacity) {
		vehicles.push_back(vehicle);
		return true;
	}

	return false;
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles() {
	int j;

	for (int i = 0; i < getVehicles().size(); ++i) {
		Vehicle *tmp;
		tmp = (vehicles[i]);

		for (j = i; j > 0 && *tmp < *(vehicles.at(j - 1)); j--)
			vehicles.at(j) = vehicles.at(j-1);

		vehicles[j] = tmp;
	}
}

#endif /* SRC_GARAGE_H_ */
