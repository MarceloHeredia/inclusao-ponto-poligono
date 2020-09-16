

#ifndef ConjuntoDeFaixas_hpp
#define ConjuntoDeFaixas_hpp

#include <vector>
#include "Faixa.h"

class ConjuntoDeFaixas {
	std::vector<Faixa> TodasAsFaixas;
	float tamanho;
public:
    ConjuntoDeFaixas();
	void cria_faixas(int qtd_de_faixas);
    void cadastra_aresta_na_faixa(int f, int a);
	int size();
	void seta_tamanho(float len);
	float get_tamanho();
	Faixa get_faixa(int i);
};

#endif /* ConjuntoDeFaixas_hpp */
