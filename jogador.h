#ifndef JOGADOR_H
#define JOGADOR_H

#include <iostream>
#include <vector>
#include <string>
#include "pokemon.h"
#include "ataque.h"
#include "dificuldade.h"

using namespace std;

class Jogador {
private:
    string nome;
    string dificuldade;
    int vitorias = 0;
    int derrotas = 0;
    int pontuacao = 0;
public:
    Jogador(string nome = "");
    Jogador(string nome, int vitorias, int derrotas, int pontos);
   
    string getNome() const;
    int getVitorias() const;
    int getDerrotas() const;
    int getPontuacao() const; 

    void setNome(string nome);
    void setVitorias(int v);
    void setDerrotas(int d);
    void setPontuacao(int p);
    

    void adicionarPontuacao(int pontos);
    void registrarResultado(Jogador& jogador, bool vitoria, Dificuldade dificuldade);
    void salvarRanking();
    void carregarDadosDoRanking();
};

#endif