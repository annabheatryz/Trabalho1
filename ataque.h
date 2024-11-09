#ifndef ATAQUE_H
#define ATAQUE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ataque {
private:
    string move;
    bool fisico;
    int poder;
    float precisao;
    string tipo;
public: 
    Ataque();
    Ataque(const string& mv, bool f, int pw, float pc, const string& t);

    string getMove() const;
    bool isFisico() const;
    string getTipo() const;
    int getPoder() const;
    float getPrecisao() const;

    void setPoder(int pw);
    void setPrecisao(float pc);

    bool acertou();
    int calcularPoder(bool critico, float stab) const;
};

#endif