#include "termo.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <chrono> 
#include <thread>
#include <random>

using namespace chrono;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

using namespace std;

void iniciarJogo(){
    cout << "╔══╗╔═╗╔═╗╔═╦═╗╔═╗" << endl;
    this_thread::sleep_for(milliseconds(150));
    cout << "╚╗╔╝║╦╝║╬║║║║║║║║║" << endl;
    this_thread::sleep_for(milliseconds(150));
    cout << "─║║─║╩╗║╗╣║║║║║║║║" << endl;
    this_thread::sleep_for(milliseconds(150));
    cout << "─╚╝─╚═╝╚╩╝╚╩═╩╝╚═╝" << endl;
    this_thread::sleep_for(milliseconds(150));
    cout << "──────────────────" << endl;
    this_thread::sleep_for(milliseconds(150));
    int gameMode;
    cout << "[1] Termo" << endl;
    cout << "[2] Dueto" << endl;
    cout << "[3] Quarteto" << endl;
    cout << "[4] Oiteto" << endl;
    cout << "[4] Como jogar?" << endl;
    cout << "Escolha uma opção: ";
    cin >> gameMode;
    switch(gameMode){
        case 1:
            termo();
            break;
        case 2:
            termoDois();
            break;
        case 3:
            termoTres();
            break;
        case 4:
            termoQuatro();
            break;
        case 5:
            cout << "Termo é um jogo de advinhação" << end;
            cout << "";
        default:
            cout << "Opção invalida.";
            break;
    }
}

void limparTela() {
	(void)system("clear");
}

string atualizarPalavra() {

	LDE <string> palavras;
    inicializarLDE(palavras);

	ifstream arquivo("palavras.txt");

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo." << endl;
	}

	string linha;
	while (getline(arquivo, linha)) {
		inserirFinalLDE(palavras, linha);
	}
	
	//int pos = rand() % contadorLDE(palavras);
	// Inicializa um gerador de números aleatórios com o Mersenne Twister
    random_device rd;   // Fonte de entropia para gerar uma semente aleatória
    mt19937 gen(rd());  // Gerador Mersenne Twister inicializado com a semente

    // Define um intervalo para os números aleatórios (por exemplo, de 1 a 100)
    uniform_int_distribution<> distrib(1, contadorLDE(palavras));

    // Gera um número aleatório
    int pos = distrib(gen);

	arquivo.close();
	return elementoPosicaoLDE(palavras, pos)->info;
}

template<typename T>
void inicializarLDE (LDE <T> &lista) {
	lista.comeco = NULL;
	lista.fim = NULL;
}

template<typename T>
bool inserirFinalLDE(LDE <T> &lista, T info) {
	No <T> *novo = new No <T>;

	if(novo == NULL) return false;
	novo->eloA = NULL;
	novo->info = info;
	novo->eloP = NULL;

	if(lista.comeco == NULL) {
		lista.comeco = novo;
		lista.fim = novo;
	} else {
		lista.fim->eloP = novo;
		novo->eloA = lista.fim;
		lista.fim = novo;
	}
	return true;
}

template<typename T>
bool inserirFinalListaLDE(LDE <LDE<T>> &listaDestino, LDE <T> &listaFonte) {
	No <LDE<T>> *novo = new No <LDE<T>>;

	if(novo == NULL) return false;
	novo->eloA = NULL;
	novo->info = listaFonte;
	novo->eloP = NULL;

	if(listaDestino.comeco == NULL) {
		listaDestino.comeco = novo;
		listaDestino.fim = novo;
	} else {
		listaDestino.fim->eloP = novo;
		novo->eloA = listaDestino.fim;
		listaDestino.fim = novo;
	}
	return true;
}

template<typename T>
bool inserirLDE(LDE <T> &lista, T info) {
	No <T> *novo = new No <T>;

	if(novo == NULL) return false;
	novo->eloA = NULL;
	novo->info = info;
	novo->eloP = NULL;

	if(lista.comeco == NULL) {
		lista.fim = novo;
	} else if(lista.comeco->info > novo->info) {
		lista.comeco->eloA = novo;
		novo->eloP = lista.comeco;
		lista.comeco = novo;
	} else if(lista.fim->info < novo->info) {
		lista.fim->eloP = novo;
		novo->eloA = lista.fim;
		lista.fim = novo;
	} else {
		No <T> *ant = lista.comeco;
		while(ant != NULL) {
			if(ant->info < novo->info && ant->eloP->info > novo->info) {
				novo->eloA = ant;
				novo->eloP = ant->eloP;
				ant->eloP->eloA = novo;
				ant->eloP = novo;
				break;
			}
			ant = ant->eloP;
		}
	}
	return true;
}

template<typename T>
void inserirAlfabeto(LDE <T> &lista){
    inserirFinalLDE(lista, 'Q');
	inserirFinalLDE(lista, 'W');
	inserirFinalLDE(lista, 'E');
	inserirFinalLDE(lista, 'R');
	inserirFinalLDE(lista, 'T');
	inserirFinalLDE(lista, 'Y');
	inserirFinalLDE(lista, 'U');
	inserirFinalLDE(lista, 'I');
	inserirFinalLDE(lista, 'O');
	inserirFinalLDE(lista, 'P');
	inserirFinalLDE(lista, 'A');
	inserirFinalLDE(lista, 'S');
	inserirFinalLDE(lista, 'D');
	inserirFinalLDE(lista, 'F');
	inserirFinalLDE(lista, 'G');
	inserirFinalLDE(lista, 'H');
	inserirFinalLDE(lista, 'J');
	inserirFinalLDE(lista, 'K');
	inserirFinalLDE(lista, 'L');
	inserirFinalLDE(lista, 'Z');
	inserirFinalLDE(lista, 'X');
	inserirFinalLDE(lista, 'C');
	inserirFinalLDE(lista, 'V');
	inserirFinalLDE(lista, 'B');
	inserirFinalLDE(lista, 'N');
	inserirFinalLDE(lista, 'M');
}

template<typename T>
void mostrarLDE(LDE <T> &lista) {
	No <T> *aux = lista.comeco;
	while(aux != NULL) {
		cout << aux->info;
		aux=aux->eloP;
	}
	cout << endl;
}

template<typename T>
void liberarLDE(LDE <T> &lista) {
	No <T> *aux = lista.comeco;
	No <T> *aux2;
	while( aux != NULL ) {
		aux2 = aux;
		aux = aux->eloP;
		delete aux2;
	}
}

template <typename T>
bool retirarLDE( LDE <T> &lista, T valor ) {
	No <T> *aux = pesquisarLDE(lista, valor);
	if( aux == NULL ) return false;

	if( aux == lista.comeco ) {
		if( aux == lista.fim ) { // Caso a
			lista.comeco = NULL;
			lista.fim = NULL;
		} else {  // Caso b
			lista.comeco = aux->eloP;
			lista.comeco->eloA = NULL;
		}
	}
	else if( aux == lista.fim ) { // Caso c
		lista.fim = aux->eloA;
		lista.fim->eloP = NULL;
	}
	else { // Caso d
		No <T> *ant = aux->eloA;
		No <T> *prox = aux->eloP;
		ant->eloP = prox;
		prox->eloA = ant;
	}
	delete aux;
	return true;
}

template<typename T>
bool pesquisarLDE(LDE <T> &lista, T info) {
	No <T> *aux = lista.comeco;
	while(aux != NULL) {
		if(aux->info == info) {
			return true;
		}
		aux = aux->eloP;
	}
	return false;
}

bool pesquisarString(string palavra, char letra){
	for(int i = 0; i < palavra.length(); i++){
		if(palavra[i] == letra){
			return true;
		}
	}
	return false;
}

template<typename T>
No <T> *elementoPosicaoLDE(LDE <T> &lista, int pos) {
	No <T> *aux = lista.comeco;
	int cont = 1;
	while(aux != NULL) {
		if(cont == pos) return aux;
		cont++;
		aux = aux->eloP;
	}
	return NULL;
}

template<typename T>
No<LDE<T>>* elementoPosicaoLDE2(LDE<LDE<T>>& lista, int pos) {
    No<LDE<T>>* aux = lista.comeco;
    int cont = 1;
    while (aux != nullptr) {
        if (cont == pos) return aux;
        cont++;
        aux = aux->eloP;
    }
    return nullptr;
}

template<typename T>
No<T>* elelementoPosicaoListaLDE(LDE<LDE<T>>& lista, int p1, int p2) {
    No<LDE<T>>* subList = elementoPosicaoLDE2(lista, p1);
    if (subList == nullptr) return nullptr;

    No<T>* aux = subList->info.comeco;
    int cont = 1;
    while (aux != nullptr) {
        if (cont == p2) return aux;
        cont++;
        aux = aux->eloP;
    }
    return nullptr;
}

template<typename T>
int contadorLDE(LDE <T> &lista){
    No <T> *aux = lista.comeco;
    int cont = 0;
    while(aux != NULL){
        cont++;
        aux = aux->eloP;
    }
    
    return cont;
}

template<typename T>
int contadorListaLDE(LDE <LDE<T>> &lista){
    No <LDE<T>> *aux = lista.comeco;
    int cont = 0;
    while(aux != NULL){
        cont++;
        aux = aux->eloP;
    }
    
    return cont;
}

template<typename T>
LDE <T> palavraViraLista(string palavra) {
	LDE <T> temp;
	inicializarLDE(temp);
	for(int i = 0; i < palavra.length(); i++) {
		inserirFinalLDE(temp, palavra[i]);
	}
	return temp;
}

template<typename T>
LDE <T> letrasCorretasLDE(string palavra, string palpite) {
	// Lista temporaria
	LDE <T> temp;
	inicializarLDE(temp);

	// Lista palavra
	LDE <char> listaPalavra = palavraViraLista<char>(palavra);

	// Lista palpite
	LDE <char> listaPalpite = palavraViraLista<char>(palpite);

	for (int i = 0; i < palavra.length(); i++) {
		No<char> *palavraNo = elementoPosicaoLDE(listaPalavra, i + 1);
		No<char> *palpiteNo = elementoPosicaoLDE(listaPalpite, i + 1);

		if (palavraNo && palpiteNo) {
			if (pesquisarLDE(listaPalavra, palpiteNo->info)) {
				if (palavraNo->info == palpiteNo->info) {
					inserirFinalLDE(temp, 2);
				} else {
					inserirFinalLDE(temp, 1);
				}
			} else {
				inserirFinalLDE(temp, 0);
			}
		} else {
			inserirFinalLDE(temp, 0);
		}
	}
	return temp;
}

template<typename T>
void mostrarCoresListasLDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos) {
    int tamanhoLista = contadorListaLDE(listaPalpites);
    for (int i = 1; i <= tamanhoLista; i++) {
        No<LDE<T>>* aux = elementoPosicaoLDE2(listaPalpites, i);
        int tamanhoElemento = contadorLDE(aux->info);
        for (int j = 1; j <= tamanhoElemento; j++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, j);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos, i, j);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << endl;
    }
}

template<typename T>
void mostrarCoresListas2LDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos, LDE<LDE<int>>& listaRetornos2) {
    int tamanhoLista = contadorListaLDE(listaPalpites);
    for (int i = 1; i <= tamanhoLista; i++) {
        No<LDE<T>>* aux = elementoPosicaoLDE2(listaPalpites, i);
        int tamanhoElemento = contadorLDE(aux->info);
        for (int j = 1; j <= tamanhoElemento; j++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, j);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos, i, j);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int k = 1; k <= tamanhoElemento; k++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, k);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos2, i, k);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << endl;
    }
}

template<typename T>
void mostrarCoresListas3LDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos, LDE<LDE<int>>& listaRetornos2, LDE<LDE<int>>& listaRetornos3) {
    int tamanhoLista = contadorListaLDE(listaPalpites);
    for (int i = 1; i <= tamanhoLista; i++) {
        No<LDE<T>>* aux = elementoPosicaoLDE2(listaPalpites, i);
        int tamanhoElemento = contadorLDE(aux->info);
        for (int j = 1; j <= tamanhoElemento; j++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, j);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos, i, j);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int k = 1; k <= tamanhoElemento; k++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, k);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos2, i, k);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int q = 1; q <= tamanhoElemento; q++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, q);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos3, i, q);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << endl;
    }
}

template<typename T>
void mostrarCoresListas4LDE(LDE<LDE<T>>& listaPalpites, LDE<LDE<int>>& listaRetornos, LDE<LDE<int>>& listaRetornos2, LDE<LDE<int>>& listaRetornos3, LDE<LDE<int>>& listaRetornos4) {
    int tamanhoLista = contadorListaLDE(listaPalpites);
    for (int i = 1; i <= tamanhoLista; i++) {
        No<LDE<T>>* aux = elementoPosicaoLDE2(listaPalpites, i);
        int tamanhoElemento = contadorLDE(aux->info);
        for (int j = 1; j <= tamanhoElemento; j++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, j);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos, i, j);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int k = 1; k <= tamanhoElemento; k++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, k);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos2, i, k);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int q = 1; q <= tamanhoElemento; q++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, q);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos3, i, q);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << " ";
        for (int f = 1; f <= tamanhoElemento; f++) {
            No<T>* aux2 = elelementoPosicaoListaLDE(listaPalpites, i, f);
            No<int>* aux3 = elelementoPosicaoListaLDE(listaRetornos4, i, f);
            if (aux3->info == 0) {
                cout << RED << aux2->info << RESET;
            } else if (aux3->info == 1) {
                cout << YELLOW << aux2->info << RESET;
            } else if (aux3->info == 2) {
                cout << GREEN << aux2->info << RESET;
            }
        }
        cout << endl;
    }
}

template<typename T>
void verificarLetrasUsadas(LDE <T> &lista, string palpite){
	for(int i = 0; i < palpite.length(); i++){
		if(!pesquisarLDE(lista, palpite[i])){
			if(inserirFinalLDE(lista, palpite[i]));
			
		}
	}
}

template<typename T>
void verificarLetrasCorretas(LDE <T> &lista, string palpite, string palavra){
	for(int i = 0; i < palpite.length(); i++){
		if(pesquisarString(palavra, palpite[i]) && !pesquisarLDE(lista, palpite[i])){
			inserirFinalLDE(lista, palpite[i]);
		}
	}
}

template<typename T>
void verificarLetrasPosCorretas(LDE <T> &lista, string palpite, string palavra){
	for(int i = 0; i < palpite.length(); i++){
		if(palavra[i] == palpite[i] && !pesquisarLDE(lista, palpite[i])){
			inserirFinalLDE(lista, palpite[i]);
		}
	}
}

LDE<int> formataAlfabeto(LDE<char> &alfabeto, LDE<char> &letrasUsadas, LDE<char> &letrasCorretas, LDE<char> &letrasPosCorreta) {
    LDE<int> temp;
    inicializarLDE(temp);
    No<char>* aux = alfabeto.comeco;
    while (aux != NULL) {
        if (pesquisarLDE(letrasPosCorreta, aux->info)) {
            inserirFinalLDE(temp, 2);
        } else if (pesquisarLDE(letrasCorretas, aux->info)) {
            inserirFinalLDE(temp, 1);
        } else if (pesquisarLDE(letrasUsadas, aux->info)) {
            inserirFinalLDE(temp, 4);
        } else {
            inserirFinalLDE(temp, 0);
        }
        aux = aux->eloP;
    }
    return temp;
}

template<typename T>
void mostrarCoresAlfabeto(LDE <T> &alfabeto, LDE <int> &retornoAlfabeto){
	No <T> *aux = alfabeto.comeco;
	No <int> *aux2 = retornoAlfabeto.comeco;
	while(aux != NULL){
		if(aux2->info == 2){
			cout << GREEN << aux->info << RESET;
		} else if(aux2->info == 1){
			cout << YELLOW << aux->info << RESET;
		} else if(aux2->info == 4){
			cout << RED << aux->info << RESET;
		} else {
			cout << aux->info;
		}
		aux = aux->eloP;
		aux2 = aux2->eloP;
	}
	cout << endl;
}


void termo() {
    
    bool acertou = false;
    int tentativas = 6;
    
    // Atualiza a palavra para palavra do dia
    string palavra = atualizarPalavra();
	
	// Atualiza o Alfabeto
	LDE <char> alfabeto;
	inicializarLDE(alfabeto);
	inserirAlfabeto(alfabeto);
	
	LDE<int> retornoAlfabeto;
	inicializarLDE(retornoAlfabeto);

    LDE<LDE<char>> listaPalpites;
    inicializarLDE(listaPalpites);
    LDE<LDE<int>> listaRetornos;
    inicializarLDE(listaRetornos);

	LDE <char> listaLetrasUsadas;
	inicializarLDE(listaLetrasUsadas);
	LDE <char> listaLetrasCorretas;
	inicializarLDE(listaLetrasCorretas);
	LDE <char> listaLetrasPosCorretas;
	inicializarLDE(listaLetrasPosCorretas);

    while (!acertou && tentativas > 0) {
        string palpite;
        cout << "Palpite: ";
        cin >> palpite;
        transform(palpite.begin(), palpite.end(), palpite.begin(), ::toupper);

        if (palpite.length() != palavra.length()) {
            cout << RED << "Seu palpite deve ter " << palavra.length() << " letras." << RESET << endl;
            continue;
        }

        LDE<int> retorno = letrasCorretasLDE<int>(palavra, palpite);
        LDE<char> listaPalpite = palavraViraLista<char>(palpite);

        inserirFinalListaLDE(listaPalpites, listaPalpite);
        inserirFinalListaLDE(listaRetornos, retorno);

		verificarLetrasUsadas(listaLetrasUsadas, palpite);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra);
	
		retornoAlfabeto = formataAlfabeto(alfabeto, listaLetrasUsadas, listaLetrasCorretas, listaLetrasPosCorretas);
		limparTela();
        cout << "==== TERMO ====" << endl;
        cout << "Tentativas restantes: " << tentativas-1 << endl;
		mostrarCoresAlfabeto(alfabeto, retornoAlfabeto);
        mostrarCoresListasLDE(listaPalpites, listaRetornos);

        if (palpite == palavra) {
            acertou = true;
            cout << GREEN << "Você ganhou!" << RESET << endl;
        }

        if (tentativas == 1 && !acertou) {
            cout << RED << "Suas tentativas acabaram, você perdeu!" << RESET << endl;
        }

        tentativas--;
    }
}

void termoDois(){
    
    bool acertou = false;
    bool acertou2 = false;
    int tentativas = 8;
    
    // Atualiza a palavra para palavra do dia
    string palavra = atualizarPalavra();
    string palavra2 = atualizarPalavra();
	
	// Atualiza o Alfabeto
	LDE <char> alfabeto;
	inicializarLDE(alfabeto);
	inserirAlfabeto(alfabeto);
	
	LDE<int> retornoAlfabeto;
	inicializarLDE(retornoAlfabeto);

    LDE<LDE<char>> listaPalpites;
    inicializarLDE(listaPalpites);
    LDE<LDE<int>> listaRetornos;
    LDE<LDE<int>> listaRetornos2;
    inicializarLDE(listaRetornos);
    inicializarLDE(listaRetornos2);

	LDE <char> listaLetrasUsadas;
	inicializarLDE(listaLetrasUsadas);
	LDE <char> listaLetrasCorretas;
	inicializarLDE(listaLetrasCorretas);
	LDE <char> listaLetrasPosCorretas;
	inicializarLDE(listaLetrasPosCorretas);

    while (!acertou && tentativas > 0) {
        string palpite;
        cout << "Palpite: ";
        cin >> palpite;
        transform(palpite.begin(), palpite.end(), palpite.begin(), ::toupper);

        if (palpite.length() != palavra.length()) {
            cout << RED << "Seu palpite deve ter " << palavra.length() << " letras." << RESET << endl;
            continue;
        }

        LDE<int> retorno = letrasCorretasLDE<int>(palavra, palpite);
        LDE<int> retorno2 = letrasCorretasLDE<int>(palavra2, palpite);
        LDE<char> listaPalpite = palavraViraLista<char>(palpite);

        inserirFinalListaLDE(listaPalpites, listaPalpite);
        inserirFinalListaLDE(listaRetornos, retorno);
        inserirFinalListaLDE(listaRetornos2, retorno2);

		verificarLetrasUsadas(listaLetrasUsadas, palpite);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra2);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra2);
	
		retornoAlfabeto = formataAlfabeto(alfabeto, listaLetrasUsadas, listaLetrasCorretas, listaLetrasPosCorretas);
		limparTela();
        cout << "==== TERMO ====" << endl;
        cout << "Tentativas restantes: " << tentativas-1 << endl;
		mostrarCoresAlfabeto(alfabeto, retornoAlfabeto);
        mostrarCoresListas2LDE(listaPalpites, listaRetornos, listaRetornos2);

        if (palpite == palavra) {
            acertou = true;
        }
        
        if(palpite == palavra2) {
            acertou2 = true;
        }
        
        if(acertou & acertou2){
            cout << GREEN << "Você ganhou!" << RESET << endl;
        }

        if (tentativas == 1 && !acertou) {
            cout << RED << "Suas tentativas acabaram, você perdeu!" << RESET << endl;
        }

        tentativas--;
    }
}

void termoTres(){
    
    bool acertou = false;
    bool acertou2 = false;
    bool acertou3 = false;
    int tentativas = 10;
    
    // Atualiza a palavra para palavra do dia
    string palavra = atualizarPalavra();
    string palavra2 = atualizarPalavra();
    string palavra3 = atualizarPalavra();
	
	// Atualiza o Alfabeto
	LDE <char> alfabeto;
	inicializarLDE(alfabeto);
	inserirAlfabeto(alfabeto);
	
	LDE<int> retornoAlfabeto;
	inicializarLDE(retornoAlfabeto);

    LDE<LDE<char>> listaPalpites;
    inicializarLDE(listaPalpites);
    LDE<LDE<int>> listaRetornos;
    LDE<LDE<int>> listaRetornos2;
    LDE<LDE<int>> listaRetornos3;
    inicializarLDE(listaRetornos);
    inicializarLDE(listaRetornos2);
    inicializarLDE(listaRetornos3);

	LDE <char> listaLetrasUsadas;
	inicializarLDE(listaLetrasUsadas);
	LDE <char> listaLetrasCorretas;
	inicializarLDE(listaLetrasCorretas);
	LDE <char> listaLetrasPosCorretas;
	inicializarLDE(listaLetrasPosCorretas);

    while (tentativas > 0) {
        string palpite;
        cout << "Palpite: ";
        cin >> palpite;
        transform(palpite.begin(), palpite.end(), palpite.begin(), ::toupper);

        if (palpite.length() != palavra.length()) {
            cout << RED << "Seu palpite deve ter " << palavra.length() << " letras." << RESET << endl;
            continue;
        }


        LDE<int> retorno = letrasCorretasLDE<int>(palavra, palpite);
        LDE<int> retorno2 = letrasCorretasLDE<int>(palavra2, palpite);
        LDE<int> retorno3 = letrasCorretasLDE<int>(palavra3, palpite);
        LDE<char> listaPalpite = palavraViraLista<char>(palpite);

        inserirFinalListaLDE(listaPalpites, listaPalpite);
        inserirFinalListaLDE(listaRetornos, retorno);
        inserirFinalListaLDE(listaRetornos2, retorno2);
        inserirFinalListaLDE(listaRetornos3, retorno3);

		verificarLetrasUsadas(listaLetrasUsadas, palpite);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra2);
		verificarLetrasPosCorretas(listaLetrasCorretas, palpite, palavra3);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra2);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra3);
	
		retornoAlfabeto = formataAlfabeto(alfabeto, listaLetrasUsadas, listaLetrasCorretas, listaLetrasPosCorretas);
		limparTela();
        cout << "==== TERMO ====" << endl;
        cout << "Tentativas restantes: " << tentativas-1 << endl;
		mostrarCoresAlfabeto(alfabeto, retornoAlfabeto);
        mostrarCoresListas3LDE(listaPalpites, listaRetornos, listaRetornos2, listaRetornos3);

        if (palpite == palavra) {
            acertou = true;
        }
        
        if (palpite == palavra2) {
            acertou2 = true;

        }
        
        if (palpite == palavra3) {
            acertou3 = true;
        }
        
        if(acertou && acertou2 && acertou3){
            cout << GREEN << "Você ganhou!" << RESET << endl;
            break;
        }

        if (tentativas == 1 && !acertou) {
            cout << RED << "Suas tentativas acabaram, você perdeu!" << RESET << endl;
        }

        tentativas--;
    }
}

void termoQuatro(){
    
    bool acertou = false;
    bool acertou2 = false;
    bool acertou3 = false;
    bool acertou4 = false;
    int tentativas = 12;
    
    // Atualiza a palavra para palavra do dia
    string palavra = atualizarPalavra();
    string palavra2 = atualizarPalavra();
    string palavra3 = atualizarPalavra();
    string palavra4 = atualizarPalavra();
	
	// Atualiza o Alfabeto
	LDE <char> alfabeto;
	inicializarLDE(alfabeto);
	inserirAlfabeto(alfabeto);
	
	LDE<int> retornoAlfabeto;
	inicializarLDE(retornoAlfabeto);

    LDE<LDE<char>> listaPalpites;
    inicializarLDE(listaPalpites);
    LDE<LDE<int>> listaRetornos;
    LDE<LDE<int>> listaRetornos2;
    LDE<LDE<int>> listaRetornos3;
    LDE<LDE<int>> listaRetornos4;
    inicializarLDE(listaRetornos);
    inicializarLDE(listaRetornos2);
    inicializarLDE(listaRetornos3);
    inicializarLDE(listaRetornos4);

	LDE <char> listaLetrasUsadas;
	inicializarLDE(listaLetrasUsadas);
	LDE <char> listaLetrasCorretas;
	inicializarLDE(listaLetrasCorretas);
	LDE <char> listaLetrasPosCorretas;
	inicializarLDE(listaLetrasPosCorretas);

    while (tentativas > 0) {
        string palpite;
        cout << "Palpite: ";
        cin >> palpite;
        transform(palpite.begin(), palpite.end(), palpite.begin(), ::toupper);

        if (palpite.length() != palavra.length()) {
            cout << RED << "Seu palpite deve ter " << palavra.length() << " letras." << RESET << endl;
            continue;
        }


        LDE<int> retorno = letrasCorretasLDE<int>(palavra, palpite);
        LDE<int> retorno2 = letrasCorretasLDE<int>(palavra2, palpite);
        LDE<int> retorno3 = letrasCorretasLDE<int>(palavra3, palpite);
        LDE<int> retorno4 = letrasCorretasLDE<int>(palavra4, palpite);
        LDE<char> listaPalpite = palavraViraLista<char>(palpite);

        inserirFinalListaLDE(listaPalpites, listaPalpite);
        inserirFinalListaLDE(listaRetornos, retorno);
        inserirFinalListaLDE(listaRetornos2, retorno2);
        inserirFinalListaLDE(listaRetornos3, retorno3);
        inserirFinalListaLDE(listaRetornos4, retorno4);

		verificarLetrasUsadas(listaLetrasUsadas, palpite);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra);
		verificarLetrasCorretas(listaLetrasCorretas, palpite, palavra2);
		verificarLetrasPosCorretas(listaLetrasCorretas, palpite, palavra3);
		verificarLetrasPosCorretas(listaLetrasCorretas, palpite, palavra4);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra2);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra3);
		verificarLetrasPosCorretas(listaLetrasPosCorretas, palpite, palavra4);
	
		retornoAlfabeto = formataAlfabeto(alfabeto, listaLetrasUsadas, listaLetrasCorretas, listaLetrasPosCorretas);
		limparTela();
        cout << "==== TERMO ====" << endl;
        cout << "Tentativas restantes: " << tentativas-1 << endl;
		mostrarCoresAlfabeto(alfabeto, retornoAlfabeto);
        mostrarCoresListas4LDE(listaPalpites, listaRetornos, listaRetornos2, listaRetornos3, listaRetornos4);

        if (palpite == palavra) {
            acertou = true;
        }
        
        if (palpite == palavra2) {
            acertou2 = true;

        }
        
        if (palpite == palavra3) {
            acertou3 = true;
        }
        
        if (palpite == palavra4) {
            acertou4 = true;
        }
        
        if(acertou && acertou2 && acertou3 && acertou4){
            cout << GREEN << "Você ganhou!" << RESET << endl;
            break;
        }

        if (tentativas == 1 && !acertou) {
            cout << RED << "Suas tentativas acabaram, você perdeu!" << RESET << endl;
        }

        tentativas--;
    }
}

