/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {
		static unsigned int last_id;
		unsigned int id;
		string name;
		vector<Account *> myAccounts;
	public:
		BankOfficer();
		void setName(string nm);
		void addAccount(Account *a);
		void addAccount(vector<Account *> accounts);
		string getName() const;
		vector<Account *> getAccounts() const;
		unsigned int getID() const;

		//-------
		BankOfficer(string nm);
		vector<Account *> removeBankOfficer(string name);

		friend bool operator>(const BankOfficer &b1, const BankOfficer &b2);
};

template <class T>
unsigned int numberDifferent (const vector<T> & v1) {
	vector<T> v2;

	for (auto a : v1)
		if (find(v2.begin(), v2.end(), a) == v2.end())
			v2.push_back(a);

	return v2.size();
}

class NoBankOfficerException {
		string name;
	public:
		NoBankOfficerException(string name);
		string getName() const;
};

#endif /* SRC_BANKOFFICER_H_ */
