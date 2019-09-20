#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = 0;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
    for (int i = 0; i < clientes.size(); i++)
        if (clientes[i].nome == nome)
            return i;

    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
    if (clientes.size() < numMaximoClientes) {
        InfoCartao cliente;
        cliente.nome = nome;
        cliente.presente = false;
        clientes.push_back(cliente);

        return true;
    }

    return false;
}

bool ParqueEstacionamento::entrar(const string & nome) {
    if (posicaoCliente(nome) == -1 || clientes[posicaoCliente(nome)].presente || vagas == lotacao)
        return false;

    clientes[posicaoCliente(nome)].presente = true;

    vagas++;

    return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
    if (posicaoCliente(nome) != -1 && !clientes[posicaoCliente(nome)].presente) {
        clientes.erase(clientes.begin() + posicaoCliente(nome));
        return true;
    }

    return false;
}

bool ParqueEstacionamento::sair(const string & nome) {
    if (posicaoCliente(nome) == -1 || !clientes[posicaoCliente(nome)].presente)
        return false;

    clientes[posicaoCliente(nome)].presente = false;

    vagas--;

    return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return vagas;
}
unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}