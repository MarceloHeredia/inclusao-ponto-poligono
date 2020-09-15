#include "ConjuntoDeFaixas.h"

ConjuntoDeFaixas::ConjuntoDeFaixas(int qtdDeFaixas)
{
    for (int i = 0; i < qtdDeFaixas; i++)
        TodasAsFaixas.push_back(Faixa());
}

void ConjuntoDeFaixas::CadastraArestaNaFaixa(int f, int a)
{
    TodasAsFaixas[f].CadastraAresta(a);
}