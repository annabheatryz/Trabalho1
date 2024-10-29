#ifndef ATAQUE_H
#define ATAQUE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Ataque {
private:
    string move;
    bool fisico; //Indica se o ataque é fisico ou especial
    int poder;
    float precisao;
    string tipo;
public: 
    // Construtor padrão
    Ataque();
    // Construtor com parâmetros
    Ataque(const string& mv, bool f, int pw, float pc, const string& t);

    // Getters
    string getMove() const;
    bool isFisico() const;
    string getTipo() const;
    int getPoder() const;
    float getPrecisao() const;

    // Setters
    void setPoder(int pw);
    void setPrecisao(float pc);

    // Métodos
    bool acertou();
    int calcularPoder(bool critico, float stab) const;
};

#endif