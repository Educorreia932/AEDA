#include "../Headers/Client.h"

using namespace std;

unsigned int Client::id = 0;

Client::Client(unsigned int id, string name, bool gold_member) {
    this->id = id;
    this->name = name;
    this->gold_member = gold_member;
}

bool Client::isGoldMember() const {
    return this->gold_member;
}

void Client::purchaseGold() {

    if(this->gold_member){
        throw alreadyGoldMember (this->id);
    } else {
        gold_member = true;
    }

}

string Client::getName() const {
    return this->name;
}

unsigned int Client::getId() const {
    return this->id;
}

void Client::setName(string newName) {
    this->name = newName;
}

ostream &operator<<(ostream &out, const alreadyGoldMember &member) {
    out << "Client with ID \"" << member.id << "\" already has a gold card." << endl;
    return out;
}
