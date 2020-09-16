#include "Faixa.h"

Faixa::Faixa() = default;

void Faixa::CadastraAresta(int a)
{
    ArestasNaFaixa.push_back(a);
}

vector<int> Faixa::get_arestas()
{
	return ArestasNaFaixa;
}
