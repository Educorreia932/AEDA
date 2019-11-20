#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
    animais.push_back(a1);
}

bool Zoo::animalJovem(string nomeA) {
    for (int i = 0; i < numAnimais(); i++)
        if (animais[i]->getNome() == nomeA)
            return animais[i]->eJovem();

    return false;
}

string Zoo::getInformacao() const {
    stringstream result;

    for (int i = 0; i < numAnimais(); i++)
        result << animais[i]->getInformacao();

    return result.str();
}

void Zoo::alocaVeterinarios(istream &isV) {
    string line, nome;
    long codOrdem;
    int counter = 0;

    while (getline(isV, line)) {
        if (counter % 2 == 0)
            nome = line;

        else {
            codOrdem = stol(line);
            Veterinario vet(nome, codOrdem);
            veterinarios.push_back(&vet);
            animais[counter - 1]->setVet(&vet);
        }

        counter++;
    }
}

bool Zoo::removeVeterinario(string nomeV) {
    for (int i1 = 0; i1 < numVeterinarios(); i1++)
        if (veterinarios[i1]->getNome() == nomeV) {
            veterinarios.erase(veterinarios.begin() + i1, veterinarios.begin() + i1 + 1);

            for (int i2 = 0; i2 < numAnimais(); i2++)
                if (animais[i2]->getVet()->getNome() == veterinarios[i1]->getNome())
                    animais[i2]->setVet(veterinarios[i1 + 1]);

            return true;
        }

    return false;
}

