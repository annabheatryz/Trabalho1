#include "ataque.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

Ataque::Ataque() : move(""), fisico(false), poder(0), precisao(0.0), tipo("") {}

Ataque::Ataque(const string& mv, bool f, int pw, float pc, const string& t) : move(mv), fisico(f), poder(pw), precisao(pc), tipo(t) {}

string Ataque::getMove() const { return move; }
bool Ataque::isFisico() const { return fisico; }
string Ataque::getTipo() const { return ipo; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }

void Ataque::setPoder(int pw) { poder = pw; }
void Ataque::setPrecisao(float pc) { precisao = pc; }


bool Ataque::acertou() {
    int chance = rand() % 100 + 1;

    if (chance <= precisao) {
        return true;  
    } else {
        return false;  
    }
}

int Ataque::calcularPoder(bool critico, float stab) const {
    int poderFinal = poder;

    if (critico) {
        poderFinal *= 2; 
    }

    poderFinal = static_cast<int>(poderFinal * stab);  

    return poderFinal;
}