#ifndef JOGO_H
#define JOGO_H

using namespace std;

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "jogador.h"
#include "pokemon.h"
#include "ataque.h"
#inlcude "dificuldade.h"

class Jogo {
private:
    vector<Pokemon> pokemons;   // Vetor de Pokémon
    vector<Ataque> ataques;     // Vetor de Ataques
    vector<Jogador> jogadores;  // Lista de jogadores cadastrados
    Jogador cpu;                     // CPU controlada pelo jogo
    Dificuldade dificuldade;   // Enum de dificuldade (FACIL, MEDIO, DIFICIL)

public:
    Jogo();                          // Construtor padrão
   // void mostrarMenu();              // Exibe o menu principal do jogo
   // void iniciarBatalha();           // Inicia uma batalha
    void ajustarDificuldade();       // Ajusta a dificuldade do jogo
    void exibirRanking();            // Exibe o ranking dos jogadores
   // void salvarDados();              // Salva os dados do jogo ao sair
    void carregarPokemons();         // Carrega os Pokémon de um arquivo CSV
    void carregarAtaques();          // Carrega os ataques de um arquivo CSV
};

#endif // JOGO_H
