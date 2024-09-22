#include "pokemon.h"
#include <fstream>
#include <cstdlib>
#include <ctime>

// Construtor padrão
Pokemon::Pokemon() : nome(""), tipo1(""), tipo2(""), hp(""), nivel(""), ataque(""), defesa(""), velocidade(""), ataque_especial(""), defesa_especial("") {}

// Construtor com parâmetros
Pokemon::Pokemon(const string& n, const string& tp1, const string& tp2, int hp, int nvl, int atq, int dfs, int v, int atq_espcial, int dfs_especial) : nome(n), tipo1(tp1), tipo2(tp2), hp(hp), nivel(nvl), ataque(atq), defesa(dfs), velocidade(v), ataque_especial(atq_especial), defesa_especial(dfs_especial) {}

// Getters
string Pokemon::getNome() const {return nome;}
string Pokemon::getTipo1() const {return tipo1;}
string Pokemon::getTipo2() const {return tipo2;}
int Pokemon::getHP() const {return hp;}
int Pokemon::getNivel() const {return nivel;}
int Pokemon::getAtaque() const {return ataque;}
int Pokemon::getDefesa() const {return defesa;}
int Pokemon::getVelocidade() const {return velocidade;}
int Pokemon::getAtaqueEspecial() const {return ataque_especial;}
int Pokemon::getDefesaEspecial() const {return defesa_especial;}

// Setters
void Pokemon::setHP(int hp) {hp = hp;}
void Pokemon::setNivel(int nvl) {nivel = nvl;}
void Pokemon::setAtaque(int atq) {ataque = atq;}
void Pokemon::setDefesa(int dfs) {defesa = dfs;}
void setVelocidade(int v) {velocidade = v;}
void setAtaqueEspecial(int atq_especial) {ataque_especial = atq_especial;}
void setDefesaEspecial(int dfs_especial) {defesa_especial = dfs_especial;}

// Métodos para carregar e sortear os pokemons do arquivo txt
vector<Pokemon> carregarPokemons(const string& nove_arquivo) {
    vector<Pokemon> pokemons;
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    string nome, tipo1, tipo2;
    int hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial;

    while (nome >> tipo1 >> tipo2 >> hp >> nivel >> defesa >> velocidade >> ataque_espeical >> defesa_especial) {
        pokemons.emplace_back(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial);
    }

    arquivo.close();
    return pokemons;
}
int main() {
    vector<Pokemon> vetor_pokemons = carregarPokemons("pokemons.txt");

    cout << vetor_pokemons << endl;

    return 0;
}
//vector<Pokemon> sortearPokemons(const vector<Pokemon>& vetor_pokemons, int qtd_sorteio);