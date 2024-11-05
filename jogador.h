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
    Dificuldade dificuldade;
    int vitorias = 0;
    int derrotas = 0;
    int pontuacao = 0;
public:
    Jogador(string nome = "");
    Jogador(string nome, int vitorias, int derrotas, int pontos);
   
    //Getters
    string getNome() const;
    int getVitorias() const;
    int getDerrotas() const;
    int getPontuacao() const; 

    //Setters
    void setNome(string nome);
    void setVitorias(int v);
    void setDerrotas(int d);
    void setPontuacao(int p);
    

    void adicionarPontuacao(int pontos);
    void registrarResultado(bool vitoria);
    void salvarJogador();
    void salvarRanking();
    void adicionarDerrota();
    void adicionarVitoria();

};

#endif