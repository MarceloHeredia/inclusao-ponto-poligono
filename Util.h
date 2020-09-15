#include <random>

#include "Ponto.h"
#include "Poligono.h"

namespace Util
{
	double prod_escalar(Ponto v1, Ponto v2);
	void prod_vetorial(Ponto v1, Ponto v2, Ponto& vresult);
	int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t);
	bool ha_interseccao(Ponto k, Ponto l, Ponto m, Ponto n);
	void gera_pontos(int qtd, Poligono& conjunto_de_ponto, Ponto& max, Ponto& min);
	void gera_convex_hull(Poligono& mapa, Poligono& convex_hull);
	void monta_faixas();
	void testa_forca_bruta(Poligono&randpontos, Poligono& mapa, Ponto& min);
	void testa_inclusao();
	void classifica_pontos_aleatorios();
}
