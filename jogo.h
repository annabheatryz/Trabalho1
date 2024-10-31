#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "jogador.h"
#include "pokemon.h"
#include "ataque.h"
#include "dificuldade.h"

using namespace std;

class Jogo {
private:
    vector<Pokemon> pokemonsDisponiveis;  // Lista de Pokémon
    vector<Ataque> ataquesDisponiveis;    // Lista de Ataques
    vector<Jogador> jogadores;            // Jogadores cadastrados
    Jogador cpu;                         // CPU controlada pelo jogo
    Dificuldade dificuldade;            // Enum de dificuldade

public:
    Jogo();  // Construtor padrão

    // Métodos de acesso aos vetores
    const vector<Pokemon>& getPokemonsDisponiveis() const;
    const vector<Ataque>& getAtaquesDisponiveis() const;

    // Funções principais do jogo
    void mostrarMenu();
    void iniciarBatalha(Jogador& jogador);
    void ajustarDificuldade();
    void exibirRanking();
    void salvarDados();

    // Funções auxiliares para carregar dados
    void carregarPokemons();
    void carregarAtaques();
    void turnoJogador(Pokemon* atacante, Pokemon* defensor);
    void turnoCPU(Pokemon* atacante, Pokemon* defensor);
    void exibirStatus(const Pokemon* p1, const Pokemon* p2) const;
    Jogador selecionarJogador();
};

#endif  // JOGO_H
