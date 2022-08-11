#include <iostream>
#include <string.h> // mesmo não precisando incluir, por causa do iostream, é recomendável sempre fazer isso
#include <map> // famoso dicionário
#include <time.h>
#include <vector>

#include "headers\letra_existe.hpp" // Esse arquivo possui somente as definições de função
#include "headers\add_file.hpp"
#include "headers\nao_acertou.hpp"
#include "headers\sortear_palavra.hpp"
using namespace std;


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