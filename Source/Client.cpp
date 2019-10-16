#include "../Headers/Client.h"

Client::Client(unsigned int id, string name, bool has_gold_card) {
    this->id = id;
    this->name = name;
    this->has_gold_card = has_gold_card;
}