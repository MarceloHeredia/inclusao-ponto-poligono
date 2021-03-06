﻿#include <random>

#include "Ponto.h"
#include "Poligono.h"
#include "ConjuntoDeFaixas.h"

namespace Util
{
	double prod_escalar(Ponto v1, Ponto v2);
	void prod_vetorial(Ponto v1, Ponto v2, Ponto& vresult);
	int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t);
	bool ha_interseccao(Ponto k, Ponto l, Ponto m, Ponto n);
	bool testa_mid_intersec(Ponto& line, Poligono& mapa, int i, int j, int k);
	void gera_pontos(int qtd, Poligono& conjunto_de_ponto, Ponto& max, Ponto& min);
	void gera_convex_hull(Poligono& mapa, Poligono& convex_hull);
	void monta_faixas(ConjuntoDeFaixas& faixas, Poligono& mapa, float max, float min);
	bool in_range(float low, float high, float x, float y);
	void testa_forca_bruta(Poligono&randpontos, Poligono& mapa, Ponto& min);
	bool aux_forca_bruta(Poligono& mapa, Ponto& ponto, Ponto& min);
	void testa_convex_hull(Poligono& mapa, Poligono& convex_hull, Poligono& pontos, Ponto& min);
	void testa_faixas(ConjuntoDeFaixas& faixas, Poligono& randpontos, Poligono& mapa, Ponto& min);
	bool testa_inclusao_ponto(Poligono &ConvexHull, Ponto &p);
	int polar_angle(Ponto p, Ponto q, Ponto r);
}
