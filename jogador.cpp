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

//Adiciona um Pokémon ao jogador
void Jogador::adicionarPokemon(const Pokemon& pokemon){
    pokemons.push_back(pokemon);
}

//Sorteia três Pokémons aleatórios de uma lista fornecida
void Jogador::sortearPokemons(const vector<Pokemon>& listaPokemons, size_t qtd_pokemons){
    pokemons.clear(); 
    vector<Pokemon> sorteados;
    vector<bool> pokemons_selecionados(listaPokemons.size(), false);

    srand(time(0));

    while (sorteados.size() < qtd_pokemons) {  // Corrigido para 'qtd_pokemons'
        // Gera um índice aleatório
        int indice = rand() % listaPokemons.size();  // Corrigido para 'listaPokemons'

        // Verifica se o pokemon já foi sorteado
        if (!pokemons_selecionados[indice]) {
            sorteados.push_back(listaPokemons[indice]);  // Corrigido para 'listaPokemons'
            // Marca o pokemon como sorteado
            pokemons_selecionados[indice] = true;
        }
    }
    pokemons = sorteados;
}

Pokemon& Jogador::escolherPokemon() {
    size_t indice;
    cout << "Escolha o índice do Pokémon para a batalha entre 0 e 2: ";
    cin >> indice;

    if (indice >= 0 && indice < pokemons.size()) {
        // Verifica se o Pokémon escolhido está derrotado
        if (pokemons[indice].estaDerrotado()) {
                cout << "Este Pokémon está derrotado. Escolha outro." << endl;
            return escolherPokemon(); // Chama a função novamente para escolher outro Pokémon
        }
        return pokemons[indice]; // Retorna o Pokémon escolhido
    } else {
        cout << "Índice inválido. Tente novamente." << endl;
        return escolherPokemon(); // Chama a função novamente para escolher outro Pokémon
    }
}

Pokemon& Jogador::pokemonCPU() {
    // Escolhe um pokemon para
    size_t indice = rand() % pokemons.size();
    return pokemons[indice];
}

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
