#include <iostream>
#include <string.h> // mesmo não precisando incluir, por causa do iostream, é recomendável sempre fazer isso
#include <map> // famoso dicionário
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>
using namespace std;

//! Funções
bool letra_existe(char letra);
bool nao_acertou();
bool nao_enforcou();
void read_file();
string sortear_palavra();
void add_file();

const string PALAVRA_SECRETA = sortear_palavra();
map <char, bool> chutou; //? map <tipo_da_chave, tipo_do_valor>
vector <char> chutes_errados; //? é uma lista de tipo único que tem valor indeterminado

int main(){
    char chute;

    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;

    do {
        cout << "Chutes errados: ";
        for (char l: chutes_errados){
            cout << l << " ";
        }

        cout << endl;

        for (char l : PALAVRA_SECRETA){
            if (chutou[l] == true){
                cout << l << " ";
            } 
            else if (!chutou[l]) {
                cout << "_ ";
            }
        }

        cout << endl;

        cout << "\nQual seu chute? ";
        cin >> chute;
        chute = toupper(chute);

        chutou[chute] = true;

        if (letra_existe(chute)){
            cout << "Voce acertou! " << chute << " existe na palavra secreta." << endl;
        } else {
            cout << "Voce errou! " << chute << " nao existe na palavra secreta." << endl;
            chutes_errados.push_back(chute);
        }

    } while (nao_acertou() && chutes_errados.size() < 5);

    cout << endl << "Fim de jogo!" << endl;
    if (nao_acertou()) { cout << "Voce perdeu! Tente novamente.\n"; }
    else {
        cout << "Parabens! Voce acertou a palavra secreta\n";
        cout << "Voce deseja adicionar uma nova palavra ao banco? [S/N]: ";
        char resposta;
        cin >> resposta;
        if (toupper(resposta) == 'S') {
            add_file();
        }
    }
    cout << endl << "A palavra secreta era: " << PALAVRA_SECRETA << endl;

    return 0;
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