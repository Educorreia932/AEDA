#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <string>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo() {
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}

vector <CKart> CPista::getKartsAvariados() {
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it)
        if ((it)->getAvariado()) aux.push_back((*it));

    return aux;
}

bool compKarts(CKart &k1, CKart &k2) {
    return k1.getNumero() < k2.getNumero();
}

//Exercicio 1 a)     
vector<CKart> CGrupo::ordenaKarts() {
	vector<CKart> vord;

	for (auto &p : pistasG)
	    for (auto &c : p.getFrotaActual())
	        vord.push_back(c);

	sort(vord.begin(), vord.end(), compKarts);

	return vord;
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind) {
    int result = 0;

    for (auto &p : pistasG)
        for (auto &c : p.getKartsAvariados())
            if (c.getCilindrada() == cilind)
                result++;

    return result;
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind) {
        for (auto &c : frotaKartsPista)
            if (c.getCilindrada() == cilind && numeroKarts > 0) {
                kartsLinhaPartida.push(c);
                numeroKarts--;
            }

    return kartsLinhaPartida.size() == numeroKarts;
}

//Exercicio 1 d) 
int CPista::inicioCorrida() {
    int numIter = kartsLinhaPartida.size() - 1;

    for (int i = 0; i < numIter; i++) {
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }

    return kartsEmProva.size();
}

