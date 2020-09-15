#include <random>

#include "Ponto.h"
#include "Poligono.h"

namespace Util
{
	double ProdEscalar(Ponto v1, Ponto v2);
	void ProdVetorial(Ponto v1, Ponto v2, Ponto& vresult);
	int intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t);
	bool HaInterseccao(Ponto k, Ponto l, Ponto m, Ponto n);
	void GeraPontos(int qtd, Poligono& ConjuntoDePonto, Ponto& Max, Ponto& Min);
	void GeraConvexHull();
	void MontaFaixas();
	void TestaForcaBruta(Poligono&ConjuntoDePonto, Poligono& Mapa);
	void TestaInclusao();
	void ClassificaPontosAleatorios();
}
