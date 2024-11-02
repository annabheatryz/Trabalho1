#include "jogador.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

//Construtor
Jogador::Jogador(string nome) : nome(nome), vitorias(0), derrotas(0), pontuacao(0){ 
    srand(time(0)); //inicializa o gerador de números aleatórios 
}

//Getters
string Jogador::getNome() const{return nome;}
int Jogador::getVitorias() const{return vitorias;}
int Jogador::getDerrotas() const {return derrotas;}
int Jogador::getPontuacao() const{return pontuacao;}

//setters
void Jogador::setNome(string nome){nome = nome;}
void Jogador::setVitorias(int v){vitorias=v;}
void Jogador::setDerrotas(int d){derrotas=d;}
void Jogador::setPontuacao(int p){pontuacao=p;}


//Atualizar a pontuação com base na dificuldade da partida
void Jogador::adicionarPontuacao(int pontos){
    pontuacao += pontos;
}

//Incrementa o controle de vitórias
void Jogador::registrarVitoria(){
    vitorias++;
}

//Incrementa o contador de derrotas
void Jogador::registrarDerrota(){
    derrotas++;
}

//Exibe informações do jogador
void Jogador::exibirInfo() const {
    cout << "Jogador: " << nome << "\n";
    cout << "Vitórias: " << vitorias << "\n";
    cout << "Derrotas: " << derrotas << "\n";
    cout << "Pontuação: " << pontuacao << "\n";
}

//Exibe os Pokémon do Jogador
void Jogador::exibirPokemons() const{
    cout << "Pokémons de " << getNome() <<":\n";
    for(size_t i = 0; i < pokemons.size(); i++){
        cout << i << ":" << pokemons[i].getNome() << " (HP: " << pokemons[i].getHP() << ")" << endl;
    }
}
