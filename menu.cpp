#include "pokemon.h"
#include "jogo.h"
#include "jogador.h"
#include <iostream>
#include <cstdlib> 


using namespace std;



// Implementação do construtor de Jogador
Jogador::Jogador(const string& n) : nome(n), vitorias(0), derrotas(0), pontuacao(0) {}

void Jogador::adicionarPokemon(const Pokemon& p) {
    pokemons.push_back(p);
}

void Jogador::mostrarInfo() const{
    cout << "Jogador: " << nome << ", Vitórias: " << vitorias << ", Derrotas: " << derrotas << ", Pontuação: " << pontuacao << endl;
}

// Implementação do construtor de Jogo
Jogo::Jogo() : dificuldade(FACIL) {}

void Jogo::adicionarJogador(const Jogador& jogador) {
    jogadores.push_back(jogador);
}

void Jogo::alterarDificuldade() {
    int escolha;
    cout << "Escolha a dificuldade: 1 - Fácil, 2 - Médio, 3 - Difícil: ";
    cin >> escolha;
    switch(escolha) {
        case 1: dificuldade = FACIL; cout << "Dificuldade ajustada para Fácil." << endl; break;
        case 2: dificuldade = MEDIO; cout << "Dificuldade ajustada para Médio." << endl; break;
        case 3: dificuldade = DIFICIL; cout << "Dificuldade ajustada para Difícil." << endl; break;
        default: cout << "Escolha inválida, mantendo dificuldade padrão (Fácil)." << endl;
    }
}

void Jogo::mostrarRanking() {
    cout << "===== Ranking de Jogadores =====" << endl;
    for (const auto& jogador : jogadores) {
        jogador.mostrarInfo();
    }
}

void Jogo::iniciarBatalha() {
    if (jogadores.empty()) {
        cout << "Nenhum jogador cadastrado. Por favor, cadastre um jogador primeiro." << endl;
        return;
    }

    cout << "Escolha um jogador para iniciar a batalha: " << endl;
    for (size_t i = 0; i < jogadores.size(); ++i) {
        cout << i + 1 << ". " << jogadores[i].nome << endl;
    }

    int escolhaJogador;
    cin >> escolhaJogador;

    if (escolhaJogador < 1 || escolhaJogador > jogadores.size()) {
        cout << "Escolha inválida!" << endl;
        return;
    }

    Jogador& jogador = jogadores[escolhaJogador - 1];
    Pokemon cpuPokemon("Charizard", (dificuldade == FACIL) ? 5 : (dificuldade == MEDIO) ? 10 : 15, 100);

    cout << "Iniciando batalha entre " << jogador.nome << " e CPU." << endl;
    //cpuPokemon.mostrarInfo();

    Pokemon& pokemonJogador = jogador.pokemons[0];
    //pokemonJogador.mostrarInfo();

    if (pokemonJogador.getNivel() >= cpuPokemon.getNivel()) {
        cout << jogador.nome << " venceu a batalha!" << endl;
        jogador.vitorias++;
        jogador.pontuacao += (dificuldade == FACIL) ? 10 : (dificuldade == MEDIO) ? 20 : 30;
    } else {
        cout << jogador.nome << " perdeu a batalha!" << endl;
        jogador.derrotas++;
    }
}

void Jogo::salvarJogo() {
    cout << "Salvando o estado do jogo..." << endl;
}

void mostrarMenu() {
    cout << "===== Menu Principal =====" << endl;
    cout << "1. Iniciar Batalha" << endl;
    cout << "2. Alterar Dificuldade" << endl;
    cout << "3. Ver Ranking" << endl;
    cout << "4. Sair" << endl;
}


int main() {
    Jogo jogo;
    int opcao;

    // Adicionar um jogador e Pokémons de exemplo
    Jogador jogador1("Ash");
    jogador1.adicionarPokemon(Pokemon("Pikachu", 10, 100));
    jogo.adicionarJogador(jogador1);

    do {
        mostrarMenu();
        cin >> opcao;

        switch(opcao) {
            case 1:
                jogo.iniciarBatalha();
                break;
            case 2:
                jogo.alterarDificuldade();
                break;
            case 3:
                jogo.mostrarRanking();
                break;
            case 4:
                jogo.salvarJogo();
                cout << "Saindo do jogo..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
        }
    } while (opcao != 4);

    return 0;
}
