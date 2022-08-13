#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <time.h>
#include <array>
using namespace std; // Precisa ter cuidado com isso, pois pode vazar e estragar funções que contém o mesmo nome das funções std.

// Retirou daqui as variáveis globais

// Se uma variável na função for alterada, é preciso utilizar ponteiros para acontecer a alteração. (porque eles são os endereços de memória)

namespace Forca{ // declara a namespace "Forca" para evitar confusões com códigos de outras pessoas (como se fosse o Class.function() do python)
	string sortear_palavra() {
		ifstream arquivo;
		arquivo.open("palavras.txt");

		if (arquivo.is_open()){
			int quantidade;
			vector <string> palavras;
			string palavra_lida;
			arquivo >> quantidade;

			for (int i = 0; i < quantidade; i++){
				arquivo >> palavra_lida;
				palavras.push_back(palavra_lida);
			}

			arquivo.close();
			srand(time(NULL));
			return palavras[rand() % quantidade];
		}
		else {
			cout << "Nao foi possivel acessar o banco de palavras." << endl;
			exit(0);
		}
	}

	void add_file() {
		string nova_palavra;
		cout << "Escolha uma nova palavra: ";
		cin >> nova_palavra;

		ifstream arquivo;
		arquivo.open("palavras.txt");
		if (arquivo.is_open()){
			int quantidade;
			vector <string> palavras;
			string palavra_lida;

			arquivo >> quantidade;
			for (int i = 0; i < quantidade; i++){
				arquivo >> palavra_lida;
				palavras.push_back(palavra_lida);
			}
			arquivo.close();

			ofstream arquivo;
			arquivo.open("palavras.txt");
			if (arquivo.is_open()){
				arquivo << palavras.size() + 1 << endl;
				for (string palavra : palavras){
					arquivo << palavra << endl;
				}
				transform(nova_palavra.begin(), nova_palavra.end(), nova_palavra.begin(), ::toupper); // toupper para string
				arquivo << nova_palavra << endl;
				arquivo.close();
			}
			else {cout << "Nao foi possivel acessar o banco de palavras." << endl; exit(0);}
		}
		else {cout << "Nao foi possivel acessar o banco de palavras." << endl; exit(0);}
	}

	bool letra_existe(const char& letra, string PALAVRA_SECRETA){ // O const no parâmetro significa que NÃO mudaremos o valor da variável na função. Isso é para explicar pro C++ e evitar erros
		for (char l : PALAVRA_SECRETA){ // como se fosse um for each
			if (letra == l){
				return true;
			}
		}
		return false;
	}

	bool nao_acertou(string PALAVRA_SECRETA, const map <char, bool>& chutou){ // o & serve para chamar a referência (ponteiros) da variável, em vez de copiá-la e colá-la aqui. Ocupando menos memória.
		for (char l : PALAVRA_SECRETA){
			if (chutou.find(l) == chutou.end() || !chutou.at(l)){
				return true;
			}
		}
		return false;
	}
	
	int tamanho(array <char, 5> lista){
		int size = 0;
		for (char letra : lista){
			if (letra != '\0'){ // Utiliza esse \0 para significa um espaço vazio
				size++;
			}
		}
		return size;
	}
}