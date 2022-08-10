#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

string sortear_palavra();

extern const string PALAVRA_SECRETA = sortear_palavra();
extern map <char, bool> chutou;

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

bool letra_existe(char letra){
    for (char l : PALAVRA_SECRETA){ // como se fosse um for each
        if (letra == l){
            return true;
        }
    }
    return false;
}

bool nao_acertou(){
    for (char l : PALAVRA_SECRETA){
        if (!chutou[l]){
            return true;
        }
    }
    return false;
}