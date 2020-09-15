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
}
// **********************************************************************
// **********************************************************************
void Util::gera_convex_hull(Poligono& mapa, Poligono& convex_hull)
{



}
// **********************************************************************
// **********************************************************************
void Util::monta_faixas()
{

}
// **********************************************************************
// **********************************************************************
void Util::testa_forca_bruta(Poligono& randpontos, Poligono& mapa, Ponto& min)
{
    glPointSize(3);
    auto line = Ponto(min.x, 0, 0); //to create a vector to the left
    r = 1;
    g = 1;
    b = 1;
    for (auto i = 0; i < randpontos.size(); i++)
    {
        int num_intersec = 0;
        line.set(line.x, randpontos.get_vertice(i).y, line.z);
		for (auto j = 0; j < mapa.size()-1; j ++)
		{
            if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(j), mapa.get_vertice(j + 1)))
            {
                num_intersec++;
            }
		}
    	if (ha_interseccao(randpontos.get_vertice(i), line, mapa.get_vertice(mapa.size()-1),mapa.get_vertice(0)))
    	{
            num_intersec++;
    	}
    	if(num_intersec%2 == 0)
    	{
	        r = 1; g = 0; b = 0;
        }
        else
        {
	        r = 0; g = 0; b = 1;
        }
        randpontos.desenha_vertice(r, g, b, i);
    	
    }
}
// **********************************************************************
// **********************************************************************
void Util::testa_inclusao()
{
    //temporizar

    //TestaForcaBruta()
    //TestaConvexHull()
    //TestaFaixas()


}
// **********************************************************************
// **********************************************************************
void Util::classifica_pontos_aleatorios()
{

}