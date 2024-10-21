#ifndef BATALHA_H
#define BATALHA_H

#include <iostream>
#include <vector>
#include "pokemon.h"
#include "ataque.h"

using namespace std;

class Batalha {
private:
    vector<Pokemon> pokemons_jogador;
    vector<Pokemon> pokemons_cpu;
    int pokemon_jogador_atual;
    int pokemon_cpu_atual;

    bool fimDejogo;

    bool sorteioCritico();
    void turnoCPU();

public:
    // Construtores
    Batalha();
    Batalha(const vector<Pokemon>& pk_jogador, const vector<Pokemon>& pk_cpu, int atual_jogador, int atual_cpu);

    // Funções que implementam o fluxo da batalha
    void escolherPokemon();
    void iniciar();
    void atacar(int atq_escolhido);
    Ataque escolherAtaque(const Pokemon& atacante, int ataqueEscolhido);
    void mostrarStatus();
    int calcularDano(const Ataque& ataque, const Pokemon& atacante, const Pokemon& defensor);
};

#endif