#ifndef BATALHA_H
#define BATALHA_H

#include <iostream>
#include <vector>
#include "jogador.h"
#include "pokemon.h"
#include "ataque.h"
#include "jogo.h"

class Batalha {
private:
    Jogador& jogador;           // Referência ao jogador
    Jogador& cpu;               // Referência à CPU (adversário)
    Jogo::Dificuldade dificuldade;    // Nível de dificuldade da batalha
    Pokemon* pokemonJogador;    // Pokémon atual do jogador
    Pokemon* pokemonCPU;        // Pokémon atual da CPU

public:
    // Construtor
    Batalha(Jogador& jogador, Jogador& cpu, Dificuldade dificuldade);

private:
    // Método para iniciar a batalha
    void iniciar();
    // Exibe o status dos Pokémon
    void exibirStatus() const;

    // Métodos para o turno de cada participante
    void turnoJogador();
    void turnoCPU();

    // Calcula o dano de um ataque
    int calcularDano(const Ataque& ataque, Pokemon* atacante, Pokemon* defensor);
    
    /*
    // Estratégias de escolha de ataque para a CPU
    Ataque escolherAtaqueFraco(Pokemon* pokemon);
    Ataque escolherAtaqueForte(Pokemon* pokemon);
    */
};

#endif // BATALHA_H