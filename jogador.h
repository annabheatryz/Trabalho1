#ifndef JOGADOR_H
#define JOGADOR_H

#include "pokemon.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Jogador {
public:
    string nome;
    int vitorias;
    int derrotas;
    int pontuacao;
    vector<Pokemon> pokemons;

    Jogador(const string& n);
    void adicionarPokemon(const Pokemon& p);
    void mostrarInfo() const;
};

#endif