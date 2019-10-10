#include "animal.h"
#include <sstream>

using namespace std;

/*
 * Classe Animal
 */

int Animal::maisJovem = 0;

Animal::Animal(string nome, int idade) {
    this->nome = nome;
    this->idade = idade;

    if (!Animal::maisJovem)
        Animal::maisJovem = idade;

    else if (idade < maisJovem)
        Animal::maisJovem = idade;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getMaisJovem() {
    return Animal::maisJovem;
}

Veterinario *Animal::getVet() const {
    return vet;
}

void Animal::setVet(Veterinario * vet) {
    this->vet = vet;
    temVet = true;
}

int Animal::getIdade() const {
    return idade;
}

bool Animal::getTemVet() const {
    return temVet;
}

Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade) {
    this->raca = raca;
}

bool Cao::eJovem() const {
    return idade < 5;
}

string Cao::getInformacao() const {
    stringstream result;
    string veterinario;

    if (temVet)
        veterinario =  vet->getNome() + ", " + to_string(vet->getCodOrdem()) + ", ";

    result << nome << ", " << idade << ", " << veterinario << raca;

    return result.str();
}

Voador::Voador(int vmax, int amax) {
    velocidade_max = vmax;
    altura_max = amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade), Voador(vmax, amax) {

}

bool Morcego::eJovem() const {
    return idade < 4;
}

string Morcego::getInformacao() const {
    stringstream result;

    result << nome << ", " << idade << ", " << velocidade_max <<  ", " << altura_max;

    return result.str();
}
