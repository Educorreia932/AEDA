#include "../Headers/Client.h"

using namespace std;

unsigned int Client::id = 0;

Client::Client(string name, bool gold_member) {
    this->id = Client::id++;
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

Client::Client(const string &filename, int line_number) {
    string line;
    ifstream File(filename);
    int counter = 0;

    if (File.is_open()) {
        while (getline(File, line)) {
            if (counter >= line_number && line_number + 3 > counter) {
                switch (counter % 3) {
                    case 0:
                        name = line;
                        break;
                    case 1:
                        id = stoi(line);
                        break;
                    case 2:
                        gold_member = stob(line);
                        break;
                }
            }


            counter++;
        }

        File.close();
    }

}

ostream &operator<<(ostream &out, const alreadyGoldMember &member) {
    out << "Client with ID \"" << member.id << "\" already has a gold card." << endl;
    return out;
}
