#include "ConjuntoDeFaixas.h"

ConjuntoDeFaixas::ConjuntoDeFaixas() = default;

void ConjuntoDeFaixas::cria_faixas(int qtd_de_faixas)
{
    for (int i = 0; i < qtd_de_faixas; i++)
        TodasAsFaixas.push_back(Faixa());
}

void ConjuntoDeFaixas::cadastra_aresta_na_faixa(int f, int a)
{
    TodasAsFaixas[f].CadastraAresta(a);
}

int ConjuntoDeFaixas::size()
{
    return TodasAsFaixas.size();
}
void ConjuntoDeFaixas::seta_tamanho(float len)
{
    tamanho = len;
}
float ConjuntoDeFaixas::get_tamanho()
{
    return tamanho;
}

Faixa ConjuntoDeFaixas::get_faixa(int i)
{
    return TodasAsFaixas[i];
}