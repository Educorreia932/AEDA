#include "frota.h"
#include <string>
#include <iostream>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
    return veiculos.size();
}

int Frota::menorAno() const {
    if (!numVeiculos())
        return 0;

    int smallest_year = veiculos[0]->getAno();

    for (int i = 1; i < numVeiculos(); i++)
        if (veiculos[i]->getAno() < smallest_year)
            smallest_year = veiculos[i]->getAno();

    return smallest_year;
}

ostream &operator<<(ostream &o, const Frota &f) {
    for (int i = 0; i < f.numVeiculos(); i++)
        o << f.veiculos[i]->getMarca() << endl;

    return o;
}

vector<Veiculo *> Frota::operator()(int anoM) const {
    vector<Veiculo *>  aux;

    for (int i = 0; i < numVeiculos(); i++)
        if (veiculos[i]->getAno() == anoM)
            aux.push_back(veiculos[i]);

    return aux;
}

float Frota::totalImposto() const {
    float result = 0;

    for (int i = 0; i < numVeiculos(); i++)
        result += veiculos[i]->calcImposto();

    return result;
}
