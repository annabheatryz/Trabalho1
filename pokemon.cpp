#include "pokemon.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <map>

Pokemon::Pokemon() : nome(""), tipo1(""), tipo2(""), hp(0), hpInicial(0), nivel(0), ataque(0), defesa(0), velocidade(0), ataque_especial(0), defesa_especial(0) {}

Pokemon::Pokemon(const string& n, const string& tp1, const string& tp2, int hp, int nvl, int atq, int dfs, int v, int atq_especial, int dfs_especial) : nome(n), tipo1(tp1), tipo2(tp2), hp(hp), hpInicial(hp), nivel(nvl), ataque(atq), defesa(dfs), velocidade(v), ataque_especial(atq_especial), defesa_especial(dfs_especial) {}

map<string, map<string, double>> efetividadeTabela = {
    {"Normal", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 0.5}, {"Fantasma", 0}, {"Dragão", 1}, {"Metal", 0.5}, {"Fada", 1}}},
    {"Fogo", {{"Normal", 1}, {"Fogo", 0.5}, {"Agua", 0.5}, {"Elétrico", 1}, {"Grama", 2}, {"Gelo", 2}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 2}, {"Rocha", 0.5}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 0.5}, {"Fada", 2}}},
    {"Agua", {{"Normal", 1}, {"Fogo", 2}, {"Agua", 0.5}, {"Elétrico", 0.5}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 2}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 2}, {"Fantasma", 1}, {"Dragão", 0.5}, {"Metal", 1}, {"Fada", 1}}},
    {"Elétrico", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 2}, {"Elétrico", 0.5}, {"Grama", 0.5}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 0}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Grama", {{"Normal", 1}, {"Fogo", 0.5}, {"Agua", 2}, {"Elétrico", 1}, {"Grama", 0.5}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 0.5}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 2}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Gelo", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 2}, {"Gelo", 0.5}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 2}, {"Metal", 1}, {"Fada", 1}}},
    {"Lutador", {{"Normal", 2}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 2}, {"Lutador", 1}, {"Venenoso", 0.5}, {"Terrestre", 1}, {"Voador", 0.5}, {"Psíquico", 0.5}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 0}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 0.5}}},
    {"Venenoso", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 2}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 0.5}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 2}}},
    {"Terrestre", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 2}, {"Grama", 0.5}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Voador", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 2}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 0.5}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Psíquico", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 0.5}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Inseto", {{"Normal", 1}, {"Fogo", 0.5}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 0.5}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 0.5}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 0.5}}},
    {"Rocha", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 0.5}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Fantasma", {{"Normal", 0}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 1}}},
    {"Dragão", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 2}, {"Metal", 1}, {"Fada", 0.5}}},
    {"Metal", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 0.5}, {"Fada", 2}}},
    {"Fada", {{"Normal", 1}, {"Fogo", 1}, {"Agua", 1}, {"Elétrico", 1}, {"Grama", 1}, {"Gelo", 1}, {"Lutador", 1}, {"Venenoso", 1}, {"Terrestre", 1}, {"Voador", 1}, {"Psíquico", 1}, {"Inseto", 1}, {"Rocha", 1}, {"Fantasma", 1}, {"Dragão", 1}, {"Metal", 1}, {"Fada", 0.5}}}
};

string Pokemon::getNome() const {return nome;}
string Pokemon::getTipo1() const {return tipo1;}
string Pokemon::getTipo2() const {return tipo2;}
int Pokemon::getHP() const {return hp;}
int Pokemon::getNivel() const {return nivel;}
int Pokemon::getDefesa() const {return defesa;}
int Pokemon::getVelocidade() const {return velocidade;}
int Pokemon::getAtaqueEspecial() const {return ataque_especial;}
int Pokemon::getDefesaEspecial() const {return defesa_especial;}

void Pokemon::setHP(int hp) {this -> hp = hp;}
void Pokemon::setNivel(int nvl) {nivel = nvl;}
void Pokemon::setAtaque(int atq) {ataque = atq;}
void Pokemon::setDefesa(int dfs) {defesa = dfs;}
void Pokemon::setVelocidade(int v) {velocidade = v;}
void Pokemon::setAtaqueEspecial(int atq_especial) {ataque_especial = atq_especial;}
void Pokemon::setDefesaEspecial(int dfs_especial) {defesa_especial = dfs_especial;}


int Pokemon::calcularDano(Ataque& ataque, const Pokemon& defensor) {
    float sorteioPrecisao = static_cast<float>(rand() % 100 + 1) / 100.0;
    if (sorteioPrecisao > ataque.getPrecisao()) {
        cout << "O ataque falhou!\n";
        return 0;
    }

    int A, D;

    if (ataque.isFisico()) {
        A = ataque.getPoder();
        D = defensor.defesa;
        cout << "Ataque físico: " << A << " vs Defesa física: " << D << endl;
    } else {
        A = ataque_especial;
        D = defensor.defesa_especial;
        cout << "Ataque especial: " << A << " vs Defesa especial: " << D << endl;
    }

    if (A == 0) A = 10;
    if (D == 0) D = 10;

    float critico = (rand() % 16 == 0) ? 2 : 1;
    if (critico == 2) cout << "Foi um golpe crítico!\n";

    float stab = (ataque.getTipo() == tipo1 || ataque.getTipo() == tipo2) ? 1.5 : 1;
    cout << "STAB: " << stab << endl;

    float tp1 = 1.0, tp2 = 1.0;
    if (efetividadeTabela.find(ataque.getTipo()) != efetividadeTabela.end()) {
        if (efetividadeTabela[ataque.getTipo()].find(defensor.getTipo1()) != efetividadeTabela[ataque.getTipo()].end()) {
            tp1 = efetividadeTabela[ataque.getTipo()][defensor.getTipo1()];
        }
        if (defensor.getTipo2() != "Nenhum" && efetividadeTabela[ataque.getTipo()].find(defensor.getTipo2()) != efetividadeTabela[ataque.getTipo()].end()) {
            tp2 = efetividadeTabela[ataque.getTipo()][defensor.getTipo2()];
        }
    }

    cout << "Efetividade de tipo: tipo 1 = " << tp1 << ", tipo 2 = " << tp2 << endl;

    if (tp1 == 0 || tp2 == 0) {
        cout << "O ataque não é efetivo!\n";
        return 0;
    }

    float random = (rand() % (255 - 217 + 1) + 217) / 255.0;
    cout << "Fator aleatório: " << random << endl;

    int dano = ((2 * nivel * ataque.getPoder() * A / D) / 50 + 2) * critico * stab * tp1 * tp2 * random;
    cout << "Dano final causado: " << dano << endl;

    return dano;
}

Ataque Pokemon::getAtaque(int i) const {
    return ataques.at(i); 
}

int Pokemon::getTotalAtaques() const {
    return ataques.size();
}

void Pokemon::adicionarAtaque(const Ataque& ataque) {
    ataques.push_back(ataque);
}

void Pokemon::reduzirHP(int dano) {
    hp -= dano;
    if (hp < 0){
        hp = 0;
        cout << getNome() << " recebeu " << dano << " de dano! HP restante: " << getHP() << endl;
    }
}

void Pokemon::limparAtaques() {
    ataques.clear();
}

void Pokemon::limparPokemons() {
    pokemons.clear();
}

void Pokemon::resetarHP() {
    hp = hpInicial;
}