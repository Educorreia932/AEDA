/*
 * Hospital.cpp
 */
#include <iostream>
#include "Hospital.h"

#include <algorithm>

using namespace std;

Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}

//Exercicio 1 a)
unsigned Hospital::numPatients(string medicalSpecialty) const {
	list<Doctor>::const_iterator it;
	unsigned int result = 0;

	for (it = doctors.begin(); it != doctors.end(); it++)
		if (it->getMedicalSpecialty() == medicalSpecialty)
			result += it->getPatients().size();

	return result;
}

bool compDoctors(Doctor &D1, Doctor &D2) {
	if (D1.getPatients().size() == D2.getPatients().size()) {
		if (D1.getMedicalSpecialty() == D2.getMedicalSpecialty())
			return D1.getCode() < D2.getCode();

		return D1.getMedicalSpecialty() < D2.getMedicalSpecialty();
	}

	return D1.getPatients().size() < D2.getPatients().size();
}

//Exercicio 1 b)
void Hospital::sortDoctors() {
	doctors.sort(compDoctors);
}

//Exercicio 1 d)
bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	int numDoctors = 0;

	for (auto &d : doctors)
		if (d.getMedicalSpecialty() == medicalSpecialty1)
			numDoctors++;

	if (numDoctors >= 3)
		return false;

	doctors.push_back(Doctor(codM1, medicalSpecialty1));

	return true;
}

//Exercicio 1 e)
queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> result;
	list<Doctor>::const_iterator it;

	for (it = doctors.begin(); it != doctors.end(); it++)
		if (it->getCode() == codM1)
			break;

	if (it == doctors.end())
		throw DoctorInexistent();

	result = it->getPatients();

	doctors.erase(it);

	return result;
}

//Exercicio 1 f)
bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	Doctor *less_busy = nullptr;
	bool first = true;

	for (auto &d : doctors)
		if (first || (d.getMedicalSpecialty() == medicalSpecialty1 && d.getPatients().size() < less_busy->getPatients().size())) {
			first = false;
			less_busy = &d;
		}

	if (less_busy == nullptr)
		return false;

	less_busy->addPatient(Patient(cod1, medicalSpecialty1));

	return true;
}

//Exercicio 1 g)
void Hospital::processPatient(unsigned codM1) {

}

//Exercicio 1 h)
unsigned Hospital::removePatients(unsigned codP1) {
	return 0;
}
