#include "jogo.h"
#include <sstream>

//a alterar
ostream &operator << (ostream &os, Circulo &c1) {
	return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados) {
	Circulo c1(pontos[pos],estados[pos]);

	if (!niv)
		return BinaryTree<Circulo>(c1);

	BinaryTree<Circulo> filhoEsq = iniciaJogo(2 * pos + 1, niv - 1, pontos, estados);
	BinaryTree<Circulo> filhoDir = iniciaJogo(2 * pos + 2, niv - 1, pontos, estados);

	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados) {
	jogo = iniciaJogo(0, niv,pontos,estados);
}

string Jogo::escreveJogo() {
	BTItrLevel<Circulo> it(jogo);
	stringstream result;

	while (!it.isAtEnd()) {
		result << it.retrieve().getPontuacao() << '-';

		if (it.retrieve().getEstado())
			result << "true-";

		else
			result << "false-";

		result << it.retrieve().getNVisitas() << endl;

		it.advance();
	}

	return result.str();
}

int Jogo::jogada() {
	BTItrLevel<Circulo> it(jogo);
	int increment, result = 0, p = 0;

	while (!it.isAtEnd()) {
		increment = 1;

		if (it.retrieve().getEstado()) // direita
			increment = 2;

		it.retrieve().mudaEstado();
		it.retrieve().incrementaVisitas();
		result += it.retrieve().getPontuacao();

		for (int i = 0; i < p + increment ; i++) {
			it.advance();
			p++;
		}
	}

	return result;
}


//a alterar
int Jogo::maisVisitado()
{
	return 0;
}

