#ifndef TERMO_HPP
#define TERMO_HPP
#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct No {
	No <T> *eloA;
	T info;
	No <T> *eloP;
};

template<typename T>
struct LDE {
	No <T> *comeco;
	No <T> *fim;
};

void iniciarJogo();

void limparTela();

void inicializarSemente();

string atualizarPalavra();

template<typename T>
void inicializarLDE (LDE <T> &lista);

template<typename T>
bool inserirFinalLDE(LDE <T> &lista, T info);

template<typename T>
bool inserirFinalListaLDE(LDE <LDE<T>> &listaDestino, LDE <T> &listaFonte);

template<typename T>
bool inserirLDE(LDE <T> &lista, T info);

template<typename T>
void inserirAlfabeto(LDE <T> &lista);

template<typename T>
void mostrarLDE(LDE <T> &lista);

template<typename T>
void liberarLDE(LDE <T> &lista);

template <typename T>
bool retirarLDE( LDE <T> &lista, T valor );

template<typename T>
bool pesquisarLDE(LDE <T> &lista, T info);

bool pesquisarString(string palavra, char letra);

template<typename T>
No <T> *elementoPosicaoLDE(LDE <T> &lista, int pos);

template<typename T>
No<LDE<T>>* elementoPosicaoLDE2(LDE<LDE<T>>& lista, int pos);

template<typename T>
No<T>* elelementoPosicaoListaLDE(LDE<LDE<T>>& lista, int p1, int p2);

template<typename T>
int contadorLDE(LDE <T> &lista);

template<typename T>
int contadorListaLDE(LDE <LDE<T>> &lista);

template<typename T>
LDE <T> palavraViraLista(string palavra);

template<typename T>
LDE <T> letrasCorretasLDE(string palavra, string palpite);

template<typename T>
void mostrarCoresListasLDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos);

template<typename T>
void mostrarCoresListas2LDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos, LDE<LDE<int>>& listaRetornos2);

template<typename T>
void mostrarCoresListas3LDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos, LDE<LDE<int>>& listaRetornos2, LDE<LDE<int>>& listaRetornos3);

template<typename T>
void verificarLetrasUsadas(LDE <T> &lista, string palpite);

template<typename T>
void verificarLetrasCorretas(LDE <T> &lista, string palpite, string palavra);

template<typename T>
void verificarLetrasPosCorretas(LDE <T> &lista, string palpite, string palavra);

LDE<int> formataAlfabeto(LDE<char> &alfabeto, LDE<char> &letrasUsadas, LDE<char> &letrasCorretas, LDE<char> &letrasPosCorreta);

template<typename T>
void mostrarCoresAlfabeto(LDE <T> &alfabeto, LDE <int> &retornoAlfabeto);

void termo();

void termoDois();

void termoTres();

void termoQuatro();

#endif