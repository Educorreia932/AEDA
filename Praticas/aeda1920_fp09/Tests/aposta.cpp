#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

//a alterar
bool Aposta::contem(unsigned num) const {
    return (numeros.find(num) != numeros.end());
}

void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n) {
    for (auto &v : valores) {
        numeros.insert(v);

        if (numeros.size() == n)
            break;
    }
}

unsigned Aposta::calculaCertos(const tabHInt & sorteio) const {
    unsigned result = 0;

    for (auto &n : sorteio)
        if (contem(n))
            result++;

    return result;
}





