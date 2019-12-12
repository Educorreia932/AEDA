#include "jogador.h"

void Jogador::adicionaAposta(const Aposta & ap) {
	apostas.emplace(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const {
	unsigned result = 0;

	for (auto &A : apostas)
		if (A.contem(num))
			result++;

	return result;
}

bool foiPremiada(const tabHAposta &aposta, const tabHInt &sorteio) {
	unsigned num_iguais = 0;

	for (auto &a : sorteio)
		if (aposta.find(a) != aposta.end())
			num_iguais++;

	return num_iguais > 3;
}

tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const {
	tabHAposta money;

	for (auto &a : apostas)
		if (foiPremiada(a, sorteio))
			money.insert(a);

	return money;
}
