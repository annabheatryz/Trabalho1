#include "pokemon.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

// Construtor padrão
Pokemon::Pokemon() : nome(""), tipo1(""), tipo2(""), hp(0), nivel(0), ataque(0), defesa(0), velocidade(0), ataque_especial(0), defesa_especial(0) {}

// Construtor com parâmetros
Pokemon::Pokemon(const string& n, const string& tp1, const string& tp2, int hp, int nvl, int atq, int dfs, int v, int atq_especial, int dfs_especial) : nome(n), tipo1(tp1), tipo2(tp2), hp(hp), nivel(nvl), ataque(atq), defesa(dfs), velocidade(v), ataque_especial(atq_especial), defesa_especial(dfs_especial) {}

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
void Pokemon::setHP(int hp) {this -> hp = hp;}
void Pokemon::setNivel(int nvl) {nivel = nvl;}
void Pokemon::setAtaque(int atq) {ataque = atq;}
void Pokemon::setDefesa(int dfs) {defesa = dfs;}
void Pokemon::setVelocidade(int v) {velocidade = v;}
void Pokemon::setAtaqueEspecial(int atq_especial) {ataque_especial = atq_especial;}
void Pokemon::setDefesaEspecial(int dfs_especial) {defesa_especial = dfs_especial;}

// Métodos para carregar e sortear os pokemons do arquivo txt
vector<Pokemon> carregarPokemons(const string& nome_arquivo) {
    vector<Pokemon> pokemons;
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return pokemons; // retorna o vetor vazio em caso de erro
    }

    string linha;
    // Ignora a primeira linha (cabeçalho)
    getline(arquivo, linha);

    // Variáveis temporárias para armazenar os dados lidos
    string nome, tipo1, tipo2;
    int hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial;

    // Ler as demais linhas do CSV
    while (getline(arquivo, linha)) {
        // Cria um objeto stringstream, permitindo que a linha inteira seja dividida em partes menores, separadas por vírgulas
        stringstream linha_stream(linha);
        string temp;

        // Leitura dos campos separados por vírgulas
        getline(linha_stream, nome, ',');
        getline(linha_stream, tipo1, ',');
        getline(linha_stream, tipo2, ',');
        getline(linha_stream, temp, ','); hp = stoi(temp);
        getline(linha_stream, temp, ','); nivel = stoi(temp);
        getline(linha_stream, temp, ','); ataque = stoi(temp);
        getline(linha_stream, temp, ','); defesa = stoi(temp);
        getline(linha_stream, temp, ','); velocidade = stoi(temp);
        getline(linha_stream, temp, ','); ataque_especial = stoi(temp);
        getline(linha_stream, temp, ','); defesa_especial = stoi(temp);

        pokemons.emplace_back(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial);
    }

    arquivo.close();
    return pokemons;
}

vector<Pokemon> sortearPokemons(const vector<Pokemon>& vetor_pokemons, int qtd_sorteio) {
    vector<Pokemon> sorteados;
    // Controle para evitar repetições
    vector<bool> pokemons_selecionados(vetor_pokemons.size(), false);

    // Define a semente para gerar números aleatórios
    srand(time(0));

    while (sorteados.size() < qtd_sorteio) {
        // Gera um índice aleatório
        int indice = rand() % vetor_pokemons.size();

        // Verifica se o pokemon já foi sorteado
        if (!pokemons_selecionados[indice]) {
            sorteados.push_back(vetor_pokemons[indice]);
            // Marca o pokemon como sorteado
            pokemons_selecionados[indice] = true;
        }
    }
    return sorteados;
}

int main() {
    vector<Pokemon> vetor_pokemons = carregarPokemons("pokemons.txt");

    // Sorteia 6 Pokemons, sendo 3 para o jogador e 3 para a CPU
    vector<Pokemon> pokemons_sorteados = sortearPokemons(vetor_pokemons, 6);

    // Separar os 3 primeiros para o jogador e os 3 últimos para a CPU
    vector<Pokemon> pokemons_jogador(pokemons_sorteados.begin(), pokemons_sorteados.begin() + 3);
    vector<Pokemon> pokemons_cpu(pokemons_sorteados.begin() + 3, pokemons_sorteados.end());

    // Exibir pokemons sorteados para o jogador
    cout << "Pokemons do jogador: " << endl;
    for (const auto& p : pokemons_jogador) {
        cout << p.getNome() << " - " << p.getTipo1() << "/" << p.getTipo2() << "- Nível: " << p.getNivel() << endl;
    }

    // Exibir pokemons sorteados para a pcu
    cout << "Pokemons da CPU: " << endl;
    for (const auto& p : pokemons_cpu) {
        cout << p.getNome() << " - " << p.getTipo1() << "/" << p.getTipo2() << "- Nível: " << p.getNivel() << endl;
    }

    return 0;
}
