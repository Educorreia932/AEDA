/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"

unsigned int BankOfficer::last_id = 0;

BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}

// ----------------------------------------------------------------------------------------------

BankOfficer::BankOfficer(string name) {
	this->name = name;
	id = ++last_id;
}

bool operator>(const BankOfficer &b1, const BankOfficer &b2) {
	if (b1.getAccounts().size() > b2.getAccounts().size())
		return true;

	else if (b1.getAccounts().size() == b2.getAccounts().size())
		return b1.getName() > b2.getName();

	else
		return false;
}

NoBankOfficerException::NoBankOfficerException(string name) {
	this->name = name;
}

string NoBankOfficerException::getName() const {
	return name;
}
