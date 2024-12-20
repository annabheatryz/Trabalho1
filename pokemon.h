#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <iostream>
#include "ataque.h"

using namespace std;

class Pokemon {
private:
    string nome;
    string tipo1;
    string tipo2;   // pode ser vazio, caso o pokemon tenha apenas um tipo
    int hp, hpInicial, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial; 
    vector<Ataque> ataques;  // Vetor para armazenar ataques do tipo Ataque    
    vector<Pokemon> pokemons;
public:
    // Construtor padrão
    Pokemon();
    // Construtor com paramêtros
    Pokemon(const string& n, const string& tp1, const string& tp2, int hp, int nvl, int atq, int dfs, int v, int atq_especial, int dfs_especial);

    // Getters
    string getNome() const;
    string getTipo1() const;
    string getTipo2() const;
    int getHP() const;
    int getNivel() const;
    Ataque getAtaque(int i) const;
    int getTotalAtaques() const;
    int getDefesa() const;
    int getVelocidade() const;
    int getAtaqueEspecial() const;
    int getDefesaEspecial() const;
    

    // Setters
    void setHP(int hp);
    void setNivel(int nvl);
    void setAtaque(int atq);
    void setDefesa(int dfs);
    void setVelocidade(int v);
    void setAtaqueEspecial(int atq_especial);
    void setDefesaEspecial(int dfs_especial);

    void adicionarAtaque(const Ataque& ataque);
    int calcularDano(Ataque& ataque, const Pokemon& defensor);
    float calcularMultiplicador(const Ataque& ataque, const Pokemon& defensor);
    void reduzirHP(int dano);
    void limparAtaques();
    void limparPokemons();
    void resetarHP();
};

#endif