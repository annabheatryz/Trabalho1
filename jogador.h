#ifndef JOGADOR_H
#define JOGADOR_H

#include <iostream>
#include <vector>
#include <string>
#include "pokemon.h"
#include "ataque.h"

using namespace std;

class Jogador {
private:
    string nome;
    int vitorias;
    int derrotas;
    int pontuacao;
    vector<Pokemon> pokemons;
public:
    Jogador(string nome = "");
   
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
    void registrarVitoria();
    void registrarDerrota();
    void exibirInfo() const;
    void exibirPokemons() const;

};

#endif