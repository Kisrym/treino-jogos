#include <iostream>
#include <time.h>
using namespace std;

int main(){
    cout << "***************************************\n";
    cout << "* Boas vindas ao Jogo da Adivinhacaoo! *\n";
    cout << "***************************************\n";

    cout << "Escolha seu nivel de dificuldade:\n";
    cout << "Facil (F), Medio (M), Dificil (D)\n";

    char dificuldade;
    int limite;

    cin >> dificuldade;
    dificuldade = toupper(dificuldade);

    switch (dificuldade){
        case 'F':
            limite = 15;
            break;
        case 'M':
            limite = 10;
            break;
        case 'D':
            limite = 5;
            break;

        default:
            limite = 10;
            break;
    }

    srand(time(NULL));
    const int NUMERO_SECRETO = rand() % 100; // o resto de divisão do rand sempre será entre 0 e 99, porque está sendo dividido por 100
    int chute;
    int tentativas = 0;
    double pontos = 1000.00;
    bool acertou = false;

    do {
        tentativas += 1;
        cout << "\nTentativa: " << tentativas << endl;

        cout << "Qual seu chute? ";
        cin >> chute;
        cout << "O valor do seu chute eh " << chute << endl;

        pontos -= abs(chute - NUMERO_SECRETO) / 2.0; // mudando o tipo do 2 para double para evitar a divisão errada (a que deixa resto)

        if (chute == NUMERO_SECRETO){
            cout << "Parabens! Voce acertou o numero secreto!" << endl;
            acertou = true;
        }

        else if (chute > NUMERO_SECRETO){
            cout << "Seu chute foi maior que o numero secreto" << endl;
        }

        else {
            cout << "Seu chute foi menor que o numero secreto" << endl;
        }
    } while (chute != NUMERO_SECRETO && tentativas < limite);

    cout << "\nFim de Jogo!\n";
    if (!acertou) {
        cout << "Voce perdeu! Tente novamente" << endl;
    }
    else {
        cout << "Voce acertou em " << tentativas << " tentativas" << endl;
        cout.precision(2); // para apresentar duas casas decimais no cout
        cout << fixed; // fixa a vírgula para não retornar um valor em notação cientifica
        cout << "Sua pontuacao foi de " << pontos << " pontos." << endl;
    }

    return 0;
}