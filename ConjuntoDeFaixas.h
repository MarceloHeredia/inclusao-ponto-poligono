

#ifndef ConjuntoDeFaixas_hpp
#define ConjuntoDeFaixas_hpp

#include <vector>
#include "Faixa.h"

class ConjuntoDeFaixas {
	std::vector<Faixa> TodasAsFaixas;
public:
    ConjuntoDeFaixas(int qtdDeFaixas);
    void CadastraArestaNaFaixa(int f, int a);
};

#endif /* ConjuntoDeFaixas_hpp */
