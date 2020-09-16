#include "Util.h"

int r, g, b; //var auxiliares pra desenhar os vertices


// **********************************************************************
//    Calcula o produto escalar entre os vetores V1 e V2
// **********************************************************************
double Util::prod_escalar(Ponto v1, Ponto v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// **********************************************************************
//    Calcula o produto vetorial entre os vetores V1 e V2
// **********************************************************************
void Util::prod_vetorial(Ponto v1, Ponto v2, Ponto& vresult)
{
	vresult.x = v1.y * v2.z - (v1.z * v2.y);
	vresult.y = v1.z * v2.x - (v1.x * v2.z);
	vresult.z = v1.x * v2.y - (v1.y * v2.x);
}
/* **********************************************************************
  Calcula a interseccao entre 2 retas (no plano "XY" Z = 0)
k : ponto inicial da reta 1
l : ponto final da reta 1
m : ponto inicial da reta 2
n : ponto final da reta 2

s: valor do par‰metro no ponto de interse‹o (sobre a reta KL)
 t: valor do par‰metro no ponto de interse‹o (sobre a reta MN)

********************************************************************** */
int Util::intersec2d(Ponto k, Ponto l, Ponto m, Ponto n, double& s, double& t)
{
	double det;

	det = (n.x - m.x) * (l.y - k.y) - (n.y - m.y) * (l.x - k.x);

	if (det == 0.0)
		return 0; // n‹o h‡ intersec‹o

	s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x)) / det;
	t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x)) / det;

	return 1; // h‡ intersec‹o
}

// **********************************************************************
bool Util::ha_interseccao(Ponto k, Ponto l, Ponto m, Ponto n)
{
	call_ha_intersec += 1; //incr 1 no numero de chamadas
	int ret;
	double s, t;
	ret = intersec2d(k, l, m, n, s, t);
	if (!ret) return false;
	if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0)
		return true;
	else return false;
}
// **********************************************************************
// **********************************************************************
bool Util::testa_mid_intersec(Ponto& line, Poligono& mapa, int i, int j, int k)
{
	if (line.y == mapa.get_vertice(j).y)
	{
		if ((mapa.get_vertice(i).y < mapa.get_vertice(j).y &&
			mapa.get_vertice(j).y < mapa.get_vertice(k).y) || (
				mapa.get_vertice(i).y > mapa.get_vertice(j).y &&
				mapa.get_vertice(j).y > mapa.get_vertice(k).y))
		{
			return true;
		}
	}
	return false;
}
// **********************************************************************
// **********************************************************************
void Util::gera_pontos(int qtd, Poligono& conjunto_de_ponto, Ponto& max, Ponto& min)
{
	std::random_device rx;
	std::random_device ry;
	std::seed_seq seedx{ rx(),rx(),rx(),rx(),rx(),rx(),rx(),rx() };
	std::seed_seq seedy{ ry(),ry(),ry(),ry(),ry(),ry(),ry(),ry() };
	std::mt19937 engx(seedx);
	std::mt19937 engy(seedy);
	std::uniform_real_distribution<> distx(min.x, max.x);
	std::uniform_real_distribution<> disty(min.y, max.y);
	//cout << "MinX " << Min.x << " MinY " << Min.y << endl << "MaxX " << Max.x << " MaxY " << Max.y << endl;

	for (int i = 0; i < qtd; i++)
	{
		float x = distx(engx);
		float y = disty(engy);

		conjunto_de_ponto.insere_vertice(Ponto(x, y));
	}
	//conjunto_de_ponto.insere_vertice(Ponto(1, 4)); //TODO remover essas linhas antes da entrega
	//conjunto_de_ponto.insere_vertice(Ponto(7, 4));
	//conjunto_de_ponto.insere_vertice(Ponto(15, 4));
}
// **********************************************************************
// **********************************************************************

int polar_angle(Ponto p, Ponto q, Ponto r)
{
	double val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0)
		return 0;
	return (val > 0) ? 1 : 2;
}
void Util::gera_convex_hull(Poligono& mapa, Poligono& convex_hull)
{
	int atual = mapa.menorPosicao;
	int prox = 0;
	do
	{
		convex_hull.insere_vertice(mapa.get_vertice(atual));
		prox = (atual + 1) % mapa.size();

		for (int i = 0; i < mapa.size(); i++)
		{
			if (polar_angle(mapa.get_vertice(atual), mapa.get_vertice(i), mapa.get_vertice(prox)) == 2)
			{
				prox = i;
			}
		}
		atual = prox;

	} while (atual != mapa.menorPosicao);
}
// **********************************************************************
// **********************************************************************
void Util::monta_faixas(ConjuntoDeFaixas& faixas, Poligono& mapa, float max, float min)
{
	faixas.seta_tamanho(abs(max - min) / faixas.size());

	for (auto j = 0; j < faixas.size(); j++)
	{
		for (auto i = 0; i < mapa.size() - 1; i++)
		{
			float low = mapa.get_vertice(i).y;
			float high = mapa.get_vertice(i + 1).y;

			if (in_range(low, high, ((j)*faixas.get_tamanho()) + min, ((j + 1) * faixas.get_tamanho()) + min))
			{
				faixas.cadastra_aresta_na_faixa(j, i);
			}
		}
		float low = mapa.get_vertice(mapa.size() - 1).y;
		float high = mapa.get_vertice(0).y;
		if (in_range(low, high, ((j)*faixas.get_tamanho()) + min, ((j + 1) * faixas.get_tamanho()) + min))
		{
			faixas.cadastra_aresta_na_faixa(j, mapa.size() - 1);
		}
	}
}
bool Util::in_range(float low, float high, float x, float y)
{
	if ((low < y && high >= x) ||
		(high < y && low >= x))
		return true;
	return false;
}
// **********************************************************************
// **********************************************************************
void Util::testa_faixas(ConjuntoDeFaixas& faixas, Poligono& randpontos, Poligono& mapa, Ponto& min)
{
	cout << "Inicio algoritmo testa_faixas" << endl;
	call_ha_intersec = 0; //inicializa numero de chamadas de ha intersec
	
	glPointSize(3);
	auto line = Ponto(min.x, 0, 0); //to create a vector to the left
	r = 1;
	g = 1;
	b = 1;
	for (auto i = 0; i < randpontos.size(); i++)
	{
		auto num_intersec = 0;
		line.set(line.x, randpontos.get_vertice(i).y);
		int position = (abs(randpontos.get_vertice(i).y - min.y)/ faixas.get_tamanho());
		auto arestas = faixas.get_faixa(position).get_arestas();
		for (int j = 0; j < arestas.size(); j++)
		{
			if (arestas[j] + 1 <= mapa.size() - 1)
			{
				if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(arestas[j]), mapa.get_vertice(arestas[j] + 1)))
				{
					if (arestas[j] < mapa.size() - 2)
					{
						if (!testa_mid_intersec(line, mapa, arestas[j], arestas[j] + 1, arestas[j] + 2))
						{
							num_intersec++;
						}
					}
					else
					{
						if (!testa_mid_intersec(line, mapa, arestas[j], arestas[j] + 1, 0))
						{
							num_intersec++;
						}
					}
				}
			}
			else
			{
				if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(arestas[j]), mapa.get_vertice(0)))
				{
					if (!testa_mid_intersec(line, mapa, mapa.size() - 1, 0, 1))
					{
						num_intersec++;
					}
				}
			}
		}
		if (num_intersec % 2 == 0)
		{
			r = 1; g = 0; b = 0;
		}
		else
		{
			r = 0; g = 0; b = 1;
		}
		cout << "Numero de chamadas de Ha_Intersec: " << call_ha_intersec << endl;
		randpontos.desenha_vertice(r, g, b, i);
	}
}
// **********************************************************************
// **********************************************************************
void Util::testa_forca_bruta(Poligono& randpontos, Poligono& mapa, Ponto& min)
{
	cout << "Inicio algoritmo testa_forca_bruta" << endl;
	call_ha_intersec = 0; //inicializa numero de chamadas de ha intersec
	
	glPointSize(3);
	auto line = Ponto(min.x, 0, 0); //to create a vector to the left
	r = 1;
	g = 1;
	b = 1;
	for (auto i = 0; i < randpontos.size(); i++)
	{
		auto num_intersec = 0;
		line.set(line.x, randpontos.get_vertice(i).y);
		for (auto j = 0; j < mapa.size() - 1; j++)
		{
			if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(j), mapa.get_vertice(j + 1)))
			{
				if (j < mapa.size() - 2)
				{
					if (!testa_mid_intersec(line, mapa, j, j + 1, j + 2))
					{
						num_intersec++;
					}
				}
				else
				{
					if (!testa_mid_intersec(line, mapa, j, j + 1, 0))
					{
						num_intersec++;
					}
				}
			}
		}
		if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(mapa.size() - 1), mapa.get_vertice(0)))
		{
			if (!testa_mid_intersec(line, mapa, mapa.size() - 1, 0, 1))
			{
				num_intersec++;
			}
		}
		if (num_intersec % 2 == 0)
		{
			r = 1; g = 0; b = 0;
		}
		else
		{
			r = 0; g = 0; b = 1;
		}
		cout << "Numero de chamadas de Ha_Intersec: " << call_ha_intersec << endl;
		randpontos.desenha_vertice(r, g, b, i);
	}
}
// **********************************************************************
// **********************************************************************
void Util::testa_convex_hull()
{
	//temporizar

	//TestaForcaBruta()
	//Testaconvex_hull()
	//TestaFaixas()


}