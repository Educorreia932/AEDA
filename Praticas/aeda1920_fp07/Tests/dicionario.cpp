#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
    if (palavra == ps1.getPalavra())
        return significado < ps1.getSignificado();

    return palavra < ps1.getPalavra();
}

void Dicionario::lerDicionario(ifstream &fich) {
    string line, palavra, significado;
    int counter = 0;

    if (fich.is_open()) {
        while(getline(fich, line)) {
            switch (counter % 2) {
                case 0:
                    palavra = line;
                    break;
                case 1:
                    significado = line;
                    palavras.insert(PalavraSignificado(palavra, significado));
                    break;
            }

            counter++;
        }
    }
}

string Dicionario::consulta(string palavra) const {
    BSTItrIn<PalavraSignificado> it(palavras);

    auto* anterior = new PalavraSignificado(it.retrieve().getPalavra(), it.retrieve().getSignificado());

    while (!it.isAtEnd()) {
        if (it.retrieve().getPalavra() == palavra)
            return it.retrieve().getSignificado();

        else if (it.retrieve().getPalavra() > palavra)
            throw PalavraNaoExiste(anterior->getPalavra(), anterior->getSignificado(), it.retrieve().getPalavra(), it.retrieve().getSignificado());

        anterior = new PalavraSignificado(it.retrieve().getPalavra(), it.retrieve().getSignificado());

        it.advance();
    }

    throw PalavraNaoExiste();
}

bool Dicionario::corrige(string palavra, string significado) {
    PalavraSignificado pDic = palavras.find(PalavraSignificado(palavra,""));
    if (pDic.getPalavra().empty() && pDic.getSignificado().empty()) {
        palavras.insert(PalavraSignificado(palavra,significado));
        return false;
    }
    else {
        palavras.remove(PalavraSignificado(palavra,""));
        pDic.setSignificado(significado);
        palavras.insert(pDic);
        return true;
    }
}

void Dicionario::imprime() const {
    BSTItrIn<PalavraSignificado> it(palavras);

    while (!it.isAtEnd()) {
        cout << it.retrieve().getPalavra() << endl
             << it.retrieve().getSignificado() << endl;

        it.advance();
    }

}


