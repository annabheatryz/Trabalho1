#include "ataque.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Construtor padrão
Ataque::Ataque() : move(""), fisico(false), poder(0), precisao(0.0), tipo("") {}

// Construtor com parâmetros
Ataque::Ataque(const string& mv, bool f, int pw, float pc, const string& t) : move(mv), fisico(f), poder(pw), precisao(pc), tipo(t) {}

// Getters
string Ataque::getMove() const { return move; }
bool Ataque::isFisico() const { return fisico; }
string Ataque::getTipo() const { return tipo; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }

// Setters
void Ataque::setPoder(int pw) { poder = pw; }
void Ataque::setPrecisao(float pc) { precisao = pc; }

// Método para verificar se o ataque acertou
bool Ataque::acertou() {
    // Gera um número aleatório entre 1 e 100
    int chance = rand() % 100 + 1;
    
    // Verifica se o número gerado é menor ou igual à precisão
    if (chance <= precisao) {
        return true;  // O ataque acertou
    } else {
        return false;  // O ataque errou
    }
}

int Ataque::calcularPoder(bool critico, float stab) const {
    int poderFinal = poder;

    if (critico) {
        poderFinal *= 2;  // Golpe crítico dobra o poder
    }

    poderFinal = static_cast<int>(poderFinal * stab);  // Aplica STAB se houver

    return poderFinal;
}