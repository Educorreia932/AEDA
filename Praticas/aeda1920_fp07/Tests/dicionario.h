#ifndef _DIC
#define _DIC

#include <string>
#include <fstream>
#include "bst.h"

class PalavraSignificado {
      string palavra;
      string significado;
	public:
	   PalavraSignificado(string p, string s): palavra(p), significado(s) {}
	   string getPalavra() const { return palavra; }
	   string getSignificado() const { return significado; }
	   void setSignificado(string sig) { significado=sig; }
	   bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario {
        BST<PalavraSignificado> palavras;
    public:
		Dicionario(): palavras(PalavraSignificado("","")){};
		BST<PalavraSignificado> getPalavras() const;
		void lerDicionario(ifstream &fich);
		string consulta(string palavra) const;
		bool corrige(string palavra, string significado);
		void imprime() const;
};

class PalavraNaoExiste {
		string PalavraAntes, SignificadoAntes, PalavraApos, SignificadoApos;
	public:
		PalavraNaoExiste() {};
		PalavraNaoExiste(const string& PalavraAntes, const string& SignificadoAntes, const string& PalavraApos, const string& SignificadoApos) {
			this->PalavraAntes = PalavraAntes;
			this->SignificadoAntes = SignificadoAntes;
			this-> PalavraApos = PalavraApos;
			this-> SignificadoApos = SignificadoApos;
		};

		string getPalavraAntes() const { return PalavraAntes; }
		string getSignificadoAntes() const { return SignificadoAntes; }
		string getPalavraApos() const { return PalavraApos; }
		string getSignificadoApos() const { return SignificadoApos; }
};

#endif
