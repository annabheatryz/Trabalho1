#ifndef JOGO_H
#define JOGO_H

#include "jogador.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Dificuldade { FACIL, MEDIO, DIFICIL };

class Jogo {
private:
    vector<Jogador> jogadores;
    Dificuldade dificuldade;

public:
    Jogo();
    void adicionarJogador(const Jogador& jogador);
    void alterarDificuldade();
    void mostrarRanking();
    void iniciarBatalha();
    void salvarJogo();
};

void mostrarMenu();

#endif