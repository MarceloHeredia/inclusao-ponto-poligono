// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************


#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <random>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Ponto.h"
#include "Poligono.h"
#include "Util.h"
#include "Temporizador.h"
#include "ConjuntoDeFaixas.h"
Temporizador T;
double AccumDeltaT=0;
int nfaixas = 10; //cria 10 faixas por defini�ao, pode ser mudado
Poligono Mapa;
Poligono ConvexHull;
Poligono ConjuntoDePonto;
ConjuntoDeFaixas faixas;
// Limites l�gicos da �rea de desenho
Ponto Min, Max;

// **********************************************************************
// **********************************************************************
void LeMapa(const char* nome)

{
    ifstream input;
    input.open(nome, ios::in);
    if (!input)
    {
        cout << "Erro ao abrir " << nome << ". " << endl;
        exit(0);
    }
    cout << "Lendo arquivo " << nome << "...";
    string S;
    unsigned int qtdVertices;

    input >> qtdVertices;
    double x, y;

    // Le a primeira linha apenas para facilitar o calculo do limites
    input >> x >> y;

    Min = Ponto(x, y);
    Max = Ponto(x, y);
    Mapa.initialize(Ponto(x, y));
    Mapa.menorPosicao = 0;
    for (int i = 0; i < qtdVertices; i++)
    {
        // Le cada elemento da linha
        input >> x >> y;
        // atualiza os limites
        if (x < Min.x) Min.x = x;
        if (y < Min.y) Min.y = y;

        if (x > Max.x) Max.x = x;
        if (y > Max.y) Max.y = y;

    	if(Mapa.get_left().x > x)
    	{
            Mapa.menorPosicao = i + 1;
    	}
        if (!input)
            break;
        //cout << "Arquivo: " << x << " " << y << endl;
        Mapa.insere_vertice(Ponto(x, y));
    }
    cout << "leitura concluida." << endl;
    //cout << "Linhas lidas: " << nLinha << endl;
    //cout << "Limites:" << endl;
    cout << "Minimo:"; Min.imprime();
    cout << "\tMaximo:"; Max.imprime();
    cout << endl;
}

// **********************************************************************
//
// **********************************************************************
void init()
{
    // Define a cor do fundo da tela PRETO para melhor visualiza�ao das cores dos vertices e arestas
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
   LeMapa("Arquivos/PoligonoDeTeste.txt");
   // LeMapa("Arquivos\\EstadoRS.txt");
   /* Min.x--;Min.y--;
    Max.x++;Max.y++;*/
    cout << "Vertices no Vetor: " << Mapa.size() << endl;

    faixas.cria_faixas(nfaixas);//cria dez faixas
    //Util::monta_faixas(faixas, Mapa, Max.y, Min.y);
    Util::gera_pontos(200,ConjuntoDePonto, Max, Min);
    Util::gera_convex_hull(Mapa, ConvexHull);
    //Ponto test = Ponto(2, 7); // Ponto está dentro do poligono
    Ponto test = Ponto(2, 8); // Ponto está dentro do poligono
    ConvexHull.insere_vertice(test);
    printf("resultado é %d\n ", Util::testa_inclusao_ponto(ConvexHull, test));
    
}
// **********************************************************************
//  void init(void)
//  Inicializa os parametros globais de OpenGL
// **********************************************************************
void initOLD(void)
{
	// Define a cor do fundo da tela (AZUL)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Leitura do arquivo
    Mapa.insere_vertice(Ponto(0,0));
    Mapa.insere_vertice(Ponto(-3,5));
    Mapa.insere_vertice(Ponto(5,5));
    Mapa.insere_vertice(Ponto(8,-3));
    Mapa.insere_vertice(Ponto(-4,-3));

    // Seta os limites da �rea de desenho
    Min = Ponto(-10, -10, 0);
    Max = Ponto( 10,  10, 1);
}


double nFrames=0;
double TempoTotal=0;
// **********************************************************************
//
// **********************************************************************
void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0/30) // fixa a atualiza��o da tela em 30
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: "  << TempoTotal << " segundos. " ;
        cout << "Nros de Frames sem desenho: " << nFrames << endl;
        cout << "FPS(sem desenho): " << nFrames/TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}
// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// **********************************************************************
//
// **********************************************************************
void desenha_eixos()
{
    Ponto Meio;
    Meio.x = (Max.x+Min.x)/2;
    Meio.y = (Max.y+Min.y)/2;
    Meio.z = (Max.z+Min.z)/2;

    glBegin(GL_LINES);
    //  eixo horizontal
        glVertex2f(Min.x,Meio.y);
        glVertex2f(Max.x,Meio.y);
    //  eixo vertical
        glVertex2f(Meio.x,Min.y);
        glVertex2f(Meio.x,Max.y);
    glEnd();
}

void desenha_faixas()
{
    glLineWidth(1);
    glColor3f(1, 1, 1); // R, G, B  [0..1]
    glBegin(GL_LINES);
    for (int i = 0; i < faixas.size(); i++)
    {
        glVertex2f(Mapa.get_left().x, i * faixas.get_tamanho());
        glVertex2f(Mapa.get_right().x, i * faixas.get_tamanho());
    }
    glEnd();
}
// **********************************************************************
//  void display( void )
//
// **********************************************************************
void display( void )
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites l�gicos da �rea OpenGL dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	glLineWidth(1);
	glColor3f(1,1,1); // R, G, B  [0..1]
    desenha_eixos();

    glLineWidth(2);
    glColor3f(1,1,0); // R, G, B  [0..1]
    Mapa.desenha_poligono();

	//Util::testa_forca_bruta(ConjuntoDePonto,Mapa,Min);
    //Util::testa_faixas(faixas,ConjuntoDePonto, Mapa, Min);

    //desenha_faixas();
	//se Vertice[i] = minimo do vetor & Vertice[i] = maximo do proximo vetor, soma 1
	//se nao soma 2 //minimo local ou maximo local

    glPointSize(6);
    glColor3f(1, 0, 0);
    ConvexHull.desenha_vertices();

	glutSwapBuffers();
}
// **********************************************************************
// ContaTempo(double tempo)
//      conta um certo n�mero de segundos e informa quanto frames
// se passaram neste per�odo.
// **********************************************************************
void ContaTempo(double tempo)
{
    Temporizador T;

    unsigned long cont = 0;
    cout << "Inicio contagem de " << tempo << "segundos ..." << flush;
    while(true)
    {
        tempo -= T.getDeltaT();
        cont++;
        if (tempo <= 0.0)
        {
            cout << "fim! - Passaram-se " << cont << " frames." << endl;
            break;
        }
    }

}
// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
// **********************************************************************

void keyboard ( unsigned char key, int x, int y )
{

	switch ( key )
	{
		case 27:        // Termina o programa qdo
			exit ( 0 );   // a tecla ESC for pressionada
			break;
        case 't':
            ContaTempo(3);
            break;
		default:
			break;
	}
}
// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:       // Se pressionar UP
			glutFullScreen ( ); // Vai para Full Screen
			break;
	    case GLUT_KEY_DOWN:     // Se pressionar UP
								// Reposiciona a janela
            glutPositionWindow (50,50);
			glutReshapeWindow ( 700, 500 );
			break;
		default:
			break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
// **********************************************************************
int  main ( int argc, char** argv )
{
    cout << "Programa OpenGL" << endl;

    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);

    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  ( 650, 500);

    // Cria a janela na tela, definindo o nome da
    // que aparecera na barra de t�tulo da janela.
    glutCreateWindow    ( "Inclusao de Pontos em Poligono" );

    // executa algumas inicializa��es
    init ();

    // Define que o tratador de evento para
    // o redesenho da tela. A funcao "display"
    // ser� chamada automaticamente quando
    // for necess�rio redesenhar a janela
    glutDisplayFunc ( display );

    // Define que o tratador de evento para
    // o invalida��o da tela. A funcao "display"
    // ser� chamada automaticamente sempre que a
    // m�quina estiver ociosa (idle)
    glutIdleFunc(animate);

    // Define que o tratador de evento para
    // o redimensionamento da janela. A funcao "reshape"
    // ser� chamada automaticamente quando
    // o usu�rio alterar o tamanho da janela
    glutReshapeFunc ( reshape );

    // Define que o tratador de evento para
    // as teclas. A funcao "keyboard"
    // ser� chamada automaticamente sempre
    // o usu�rio pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );

    // Define que o tratador de evento para
    // as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" ser� chamada
    // automaticamente sempre o usu�rio
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
