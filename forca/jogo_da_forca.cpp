#include <iostream>
#include <string.h> // mesmo não precisando incluir, por causa do iostream, é recomendável sempre fazer isso
#include <map> // famoso dicionário
#include <array>

#include "headers/letra_existe.hpp" // Esse arquivo possui somente as definições de função
#include "headers/add_file.hpp"
#include "headers/nao_acertou.hpp"
#include "headers/sortear_palavra.hpp"
#include "headers/tamanho.hpp"
using namespace std;

// O static fala que essas variáveis só vão existir nessa translation unit, ou seja, vão deixar de ser globais para todo o projeto.
static const string PALAVRA_SECRETA = Forca::sortear_palavra(); 
static map <char, bool> chutou; //? map <tipo_da_chave, tipo_do_valor>
//static vector <char> chutes_errados; //? é uma lista de tipo único que tem valor indeterminado
static array <char, 5> chutes_errados; //? trocando de vector pra array pq o vector armazena as variáveis na heap, oq diminui a eficiência do código

int main(){
    char chute;
	int c = 0;

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

        if (Forca::letra_existe(chute, PALAVRA_SECRETA)){
            cout << "Voce acertou! " << chute << " existe na palavra secreta." << endl;
        } else {
            cout << "Voce errou! " << chute << " nao existe na palavra secreta." << endl;
            chutes_errados[c] = chute;
			c++;
        }
    } while (Forca::nao_acertou(PALAVRA_SECRETA, chutou) && Forca::tamanho(chutes_errados) < 5);

    cout << endl << "Fim de jogo!" << endl;
    if (Forca::nao_acertou(PALAVRA_SECRETA, chutou)) { cout << "Voce perdeu! Tente novamente.\n"; }
    else {
        cout << "Parabens! Voce acertou a palavra secreta\n";
        cout << "Voce deseja adicionar uma nova palavra ao banco? [S/N]: ";
        char resposta;
        cin >> resposta;
        if (toupper(resposta) == 'S') {
            Forca::add_file();
        }
    }
    cout << endl << "A palavra secreta era: " << PALAVRA_SECRETA << endl;

    return 0;
}