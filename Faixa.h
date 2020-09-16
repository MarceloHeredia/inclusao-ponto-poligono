

#ifndef Faixa_hpp
#define Faixa_hpp

using namespace std;
#include <vector>

class Faixa
{
	vector<int> ArestasNaFaixa;
	public:
		void CadastraAresta(int a);
		vector<int> get_arestas();
		Faixa();
};


#endif /* Faixa_hpp */