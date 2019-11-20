/*
 * Doctor.cpp
 */

#include "Doctor.h"

Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS) {}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS) {

}

Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1) {

}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}

	else throw PatientInexistent();
}

//Exercicio 1 c)
void Doctor::moveToFront(unsigned codP1) {
	queue<Patient> to_add, result;
	int num_iterations = patients.size();

	for (int i = 0; i < num_iterations; i++) {
		if (patients.front().getCode() == codP1) {
			result.push(patients.front());
			patients.pop();
			break;
		}

		else {
			to_add.push(patients.front());
			patients.pop();
		}
	}

	// There's no patient with codP1
	if (result.empty()) {
		patients = to_add;
		return;
	}

	num_iterations = to_add.size();

	for (int i = 0; i < num_iterations; i++) {
		result.push(to_add.front());
		to_add.pop();
	}

	num_iterations = patients.size();

	for(int i = 0; i < num_iterations;i++) {
		result.push(patients.front());
		patients.pop();
	}

	patients = result;
}
