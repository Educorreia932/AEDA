#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
    public:
        N info;
        vector< Aresta<N,A> > arestas;
        No(N inf) {
            info = inf;
        }
};

template <class N, class A>
class Aresta {
    public:
        A valor;
        No<N,A> *destino;
        Aresta(No<N,A> *dest, A val) {
            valor = val;
            destino = dest;
        }
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo();
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const;
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g) {
    g.imprimir(out);

    return out;
}

// excecao NoRepetido
template <class N>
class NoRepetido {
    public:
       N info;
       NoRepetido(N inf) { info=inf; }
};

template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no) {
    out << "No repetido: " << no.info; return out;
}

// excecao NoInexistente
template <class N>
class NoInexistente {
    public:
        N info;
        NoInexistente(N inf) {
            info = inf;
        }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni){
    out << "No inexistente: " << ni.info; return out;
}

// excecao ArestaRepetida
template <class N>
class ArestaRepetida {
    public:
        N inicio;
        N fim;
        ArestaRepetida(N inicio, N fim) {
            this->inicio = inicio;
            this->fim = fim;
        }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar) {
    out << "Aresta repetida: " << ar.inicio << " , " << ar.fim;
    return out;
}

// excecao ArestaInexistente

template <class N>
class ArestaInexistente {
    public:
        N inicio;
        N fim;
        ArestaInexistente(N inicio, N fim) {
            this->inicio = inicio;
            this->fim = fim;
        }
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ai) {
    out << "Aresta inexistente: " << ai.inicio << " , " << ai.fim;
    return out;
}

template <class N, class A>
Grafo<N, A>::Grafo() {
        nos = {};
}

template <class N, class A>
Grafo<N, A>::~Grafo() {
    for (int i = 0; i < numNos(); i++)
        delete nos[i];
}

template <class N, class A>
int Grafo<N, A>::numNos() const {
    return nos.size();
}

template <class N, class A>
int Grafo<N, A>::numArestas() const {
    int result = 0;

    for (int i = 0; i < numNos(); i++)
        result += nos[i]->arestas.size();

    return result;
}

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirNo(const N &dados) {
    for (int i = 0; i < numNos(); i++)
        if (nos[i]->info == dados)
            throw NoRepetido<N>(dados);

    No<N, A> *no;
    no = new No<N, A>(dados);

    nos.push_back(no);

    return *this;
}

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    int inicio_pos = -1, fim_pos = -1;

    //Verifica se algum dos nós não existe
    for (int i = 0; i < numNos(); i++) {
        if (nos[i]->info == inicio)
            inicio_pos = i;

        if (nos[i]->info == fim)
            fim_pos = i;

        if (inicio_pos != -1 && fim_pos != -1)
            break;
    }

    if (inicio_pos == -1)
        throw NoInexistente<N>(inicio);

    if (fim_pos == -1)
        throw NoInexistente<N>(fim);

    //Verifica se a aresta já existe
    for (int i = 0; i < nos[inicio_pos]->arestas.size(); i++)
        if (nos[inicio_pos]->arestas[i].destino->info == fim)
            throw ArestaRepetida<N>(inicio, fim);

    Aresta<N, A> aresta(nos[fim_pos], val);

    nos[inicio_pos]->arestas.push_back(aresta);

    return *this;
}

template<class N, class A>
A &Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {
    bool no_existe = false;

    for (int i1 = 0; i1 < numNos(); i1++)
        for (int i2 = 0; i2 < nos[i1]->arestas.size(); i2++)
            if (nos[i1]->info == inicio) {
                no_existe = true;

                if(nos[i1]->arestas[i2].destino->info == fim)
                    return nos[i1]->arestas[i2].valor;
            }

    if (!no_existe)
        throw NoInexistente<N>(inicio);

    throw ArestaInexistente<N>(inicio, fim);
}

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim) {
    bool no_existe = false;
    bool aresta_existe = false;

    for (int i1 = 0; i1 < numNos(); i1++)
        for (int i2 = 0; i2 < nos[i1]->arestas.size(); i2++)
            if (nos[i1]->info == inicio) {
                no_existe = true;

                if(nos[i1]->arestas[i2].destino->info == fim) {
                    aresta_existe = true;
                    nos[i1]->arestas.erase(nos[i1]->arestas.begin() + i2, nos[i1]->arestas.begin() + i2 + 1);
                }
            }

    if (!no_existe)
        throw NoInexistente<N>(inicio);

    if(!aresta_existe)
        throw ArestaInexistente<N>(inicio, fim);

    return *this;
}

template<class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const {
    for (int i1 = 0; i1 < numNos(); i1++) {
        os << "( " << nos[i1]->info;

        for (int i2 = 0; i2 < nos[i1]->arestas.size(); i2++)
            os << "[ " << nos[i1]->arestas[i2].destino->info << ' ' << nos[i1]->arestas[i2].valor << "] ";

        os << ") ";
    }
}
