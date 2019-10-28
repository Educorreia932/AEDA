#include "veiculo.h"
#include <iostream>

#define gas combustivel == "gasolina"
#define outro combustivel != "gasolina"
#define CHECK(x, y, n) ((n) > (x) && (n) <= (y) ? 1 : 0)

using namespace std;

Veiculo::Veiculo(string mc, int m, int a) {
    marca = mc;
    mes = m;
    ano = a;
}

string Veiculo::getMarca() const {
    return marca;
}

int Veiculo::getAno() const {
    return ano;
}

int Veiculo::info() const {
    cout << 3;
    return 3;
}

bool Veiculo::operator< (const Veiculo &v) const {
    return ano < v.ano || (ano == v.ano && mes < v.mes);
}

Motorizado::Motorizado(string mc, int m, int a, string c, int cil) : Veiculo(mc, m, a) {
    combustivel = c;
    cilindrada = cil;
}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Motorizado::info() const {
    cout << 5;
    return 5;
}

float Motorizado::calcImposto() const {
        if ((gas && cilindrada <= 1000) || (outro && cilindrada <= 1500))
            if (ano > 1995)
                return 14.56;

            else
                return 8.10;

        else if ((gas && CHECK(1000, 1300, cilindrada)) || (outro && CHECK(1500, 2000, cilindrada)))
            if (ano > 1995)
                return 29.06;

            else
                return 14.56;

        else if ((gas && CHECK(1300, 1750, cilindrada)) || (outro && CHECK(2000, 3000, cilindrada)))
            if (ano > 1995)
                return 45.15;

            else
                return 22.65;

        else if ((gas && CHECK(1750, 2600, cilindrada)) || (outro && cilindrada > 3000))
            if (ano > 1995)
                return 113.98;

            else
                return 54.89;

        else if (gas && CHECK(2600, 3500, cilindrada))
            if (ano > 1995)
                return 181.17;

            else
                return 87.13;

        else if (gas && cilindrada > 3500)
            if (ano > 1995)
                return 320.89;

            else
                return 148.37;

        return -1;
}

Automovel::Automovel(string mc, int m, int a, string c, int cil) : Motorizado(mc, m, a, c, cil) {

}

int Automovel::info() const {
    cout << 5;
    return 5;
}

Camiao::Camiao(string mc, int m, int a, string c, int cil,int cm) : Motorizado(mc, m, a , c, cil) {
    carga_maxima = cm;
}

int Camiao::info() const {
    cout << 6;
    return 6;
}

Bicicleta::Bicicleta(string mc, int m, int a,string t) : Veiculo(mc, m, a) {
    tipo = t;
}

int Bicicleta::info() const {
    cout << 4;
    return 4;
}

float Bicicleta::calcImposto() const {
    return 0;
}


