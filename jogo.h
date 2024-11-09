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
    vector<Pokemon> pokemonsDisponiveis; 
    vector<Ataque> ataquesDisponiveis;   
    vector<Jogador> jogadores;          
    Jogador cpu;                       
    Jogador jogador;
    Dificuldade dificuldade;            
    vector<Pokemon*> pokemons_jogador;
    vector<Pokemon*> pokemons_cpu;
    Pokemon* jogador_atual;
    Pokemon* atual_cpu;

public:
    Jogo();  


    const vector<Pokemon>& getPokemonsDisponiveis() const;
    const vector<Ataque>& getAtaquesDisponiveis() const;

    void mostrarMenu();
    void prepararBatalha();
    void iniciarBatalha(Jogador& jogador, Dificuldade dificuldade);
    void ajustarDificuldade();
    void exibirRanking();
    void carregarJogadores();
    void salvarDados();
    

    void carregarPokemons();
    void carregarAtaques();
    Pokemon& escolherPokemonJogador();
    Pokemon& escolherPokemonCPU();
    void sortearPokemons();
    void distribuirAtaques(Pokemon& pokemon);
    void turnoJogador(Pokemon* atacante, Pokemon* defensor);
    void turnoCPU(Pokemon* atacante, Pokemon* defensor);
    void exibirStatus(const Pokemon* p1, const Pokemon* p2) const;
    Jogador selecionarJogador();
    void exibirPokemons();
};

#endif  
