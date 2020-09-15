#include "Util.h"

int r, g, b; //var auxiliares pra desenhar os vertices
// **********************************************************************
//    Calcula o produto escalar entre os vetores V1 e V2
// **********************************************************************
double Util::ProdEscalar(Ponto v1, Ponto v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
// **********************************************************************
//    Calcula o produto vetorial entre os vetores V1 e V2
// **********************************************************************
void Util::ProdVetorial(Ponto v1, Ponto v2, Ponto& vresult)
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
bool Util::HaInterseccao(Ponto k, Ponto l, Ponto m, Ponto n)
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
void Util::GeraPontos(int qtd, Poligono& ConjuntoDePonto, Ponto& Max, Ponto& Min)
{
    std::random_device rx;
    std::random_device ry;
    std::seed_seq seedx{ rx(),rx(),rx(),rx(),rx(),rx(),rx(),rx() };
    std::seed_seq seedy{ ry(),ry(),ry(),ry(),ry(),ry(),ry(),ry() };
    std::mt19937 engx(seedx);
    std::mt19937 engy(seedy);
    std::uniform_real_distribution<> distx(Min.x, Max.x);
    std::uniform_real_distribution<> disty(Min.y, Max.y);
    //cout << "MinX " << Min.x << " MinY " << Min.y << endl << "MaxX " << Max.x << " MaxY " << Max.y << endl;

    for (int i = 0; i < qtd; i++)
    {
        float x = distx(engx);
        float y = disty(engy);

        ConjuntoDePonto.insereVertice(Ponto(x, y));
    }
	
}



// **********************************************************************
// **********************************************************************
void Util::GeraConvexHull(Poligono& Mapa, Poligono& ConvexHull)
{



}
// **********************************************************************
// **********************************************************************
void Util::MontaFaixas()
{

}
// **********************************************************************
// **********************************************************************
void Util::TestaForcaBruta(Poligono& ConjuntoDePonto, Poligono& Mapa)
{
    for (int i = 0; i < ConjuntoDePonto.getNVertices(); i++)
    {
        r = 1;
        g = 1;
        b = 0;
        glPointSize(3);
        ConjuntoDePonto.desenhaVertice(r, g, b, i);
    }
}
// **********************************************************************
// **********************************************************************
void Util::TestaInclusao()
{
    //temporizar

    //TestaForcaBruta()
    //TestaConvexHull()
    //TestaFaixas()


}
// **********************************************************************
// **********************************************************************
void Util::ClassificaPontosAleatorios()
{

}