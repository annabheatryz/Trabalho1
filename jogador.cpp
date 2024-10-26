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

Pokemon& Jogador::escolherPokemon(){
    int indice;
    cout << "Escolha o índice do Pokémon para a batalha: ";
    cin >> indice;

    if(indice >= 0 && indice < pokemons.size()){
        return pokemons[indice];
    } else {
        cerr << "índice inválido! Usando o primeiro Pokémon da lista.\n";
        return pokemons[0];
    }
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

int main() {
    // Criar jogadores
    Jogador jogador("Ash");
    Jogador cpu("CPU");

    // Criar uma lista de pokémons disponíveis
    vector<Pokemon> listaPokemons = {
        Pokemon("Pikachu", "Elétrico", "N/A", 50, 120, 120, 55, 40, 50, 50),
        Pokemon("Charmander", "Fogo", "N/A", 40, 100, 100, 52, 43, 60, 50),
        Pokemon("Bulbasaur", "Grama", "N/A", 45, 110, 110, 49, 49, 65, 65),
        Pokemon("Squirtle", "Água", "N/A", 44, 110, 110, 48, 65, 50, 64),
    };

    // Sortear pokémons para os jogadores
    jogador.sortearPokemons(listaPokemons, 3);
    cpu.sortearPokemons(listaPokemons, 3);

    // Exibir os pokémons sorteados
    jogador.exibirPokemons(); 
    cout << endl;
    cpu.exibirPokemons();

    // Criar uma lista de ataques disponíveis
    vector<Ataque> listaAtaques = {
        Ataque("Lança-chamas", false, 90, 1.0, "Fogo"),  // Ataque especial
        Ataque("Ataque de Asa", true, 60, 1.0, "Voador"),  // Ataque físico
        Ataque("Investida", true, 40, 1.0, "Normal"),  // Ataque físico
        Ataque("Raio Solar", false, 120, 0.75, "Grama"),  // Ataque especial
        Ataque("Terremoto", true, 100, 1.0, "Terrestre")  // Ataque físico
    };

    // Mostrar lista de ataques disponíveis
    cout << "\nAtaques disponíveis:\n";
    for (const auto& ataque : listaAtaques) {
        cout << "- " << ataque.getMove() << " (Tipo: " << ataque.getTipo()
             << ", Poder: " << ataque.getPoder() << ", Físico: " << (ataque.isFisico() ? "Sim" : "Não") << ")\n";
    }

    // Criar um Pokémon
    cout << "\nCriando o Pokémon Charizard...\n";
    Pokemon charizard("Charizard", "Fogo", "Voador", 180, 50, 180, 84, 78, 109, 85);

    // Mostrar status do Pokémon antes do sorteio de ataques
    cout << "Status do Pokémon Charizard:\n";
    cout << "Nome: " << charizard.getNome() << "\n"
         << "Tipo 1: " << charizard.getTipo1() << "\n"
         << "Tipo 2: " << charizard.getTipo2() << "\n"
         << "HP: " << charizard.getHP() << "\n";

    // Sortear ataques para o Charizard
    cout << "\nSorteando ataques para Charizard...\n";
    charizard.sortearAtaques(listaAtaques, 4);

    // Mostrar os ataques sorteados
    cout << "\nAtaques sorteados para Charizard:\n";
    charizard.exibirAtaques();  // Método para exibir os ataques sorteados

    // Criar outro Pokémon para a batalha (Bulbasaur)
    cout << "\nCriando o Pokémon Bulbasaur...\n";
    Pokemon bulbasaur("Bulbasaur", "Grama", "Venenoso", 150, 50, 49, 49, 45, 65, 65);

    // Mostrar status do Pokémon defensor
    cout << "Status do Pokémon Bulbasaur:\n";
    cout << "Nome: " << bulbasaur.getNome() << "\n"
         << "Tipo 1: " << bulbasaur.getTipo1() << "\n"
         << "Tipo 2: " << bulbasaur.getTipo2() << "\n"
         << "HP: " << bulbasaur.getHP() << "\n";

    // Simular um ataque (Charizard usa "Lança-chamas" contra Bulbasaur)
    cout << "\nCharizard ataca Bulbasaur com Lança-chamas!\n";
    charizard.calcularDano(listaAtaques[0], bulbasaur);

    cout << "\nPrograma executado com sucesso!\n";

    return 0;
}