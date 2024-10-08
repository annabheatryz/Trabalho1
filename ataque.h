#ifndef ATAQUE_H
#define ATAQUE_H

#include <iostream>
#include <vector>
#include <string>
#include "pokemon.h"

using namespace std;

class Ataque {
private:
    string move;
    string categoria;
    int poder;
    float precisao;
    string tipo;
public: 
    // Construtor padrão
    Ataque();
    // Construtor com parâmetros
    Ataque(const string& mv, const string& c, int pw, float pc, const string& t);

    // Getters
    string getMove() const;
    string getCategoria() const;
    string getTipo() const;
    int getPoder() const;
    float getPrecisao() const;

    // Setters
    void setPoder(int pw);
    void setPrecisao(float pc);

    // Métodos para carregar os ataques e sortea-los para os pokemons
    vector<Ataque> carregarAtaques(const string& nome_arquivo);
    vector<Ataque> sortearAtaques(const vector<Ataque>& vetor_ataques, const Pokemon& pokemon, size_t qtd_ataques);
    // Sobrecarga do operador "==" para comparar ataques com base no nome
    bool operator==(const Ataque& outro) const {
        return move == outro.move;  // Compara os nomes dos ataques
    }
};

#endif