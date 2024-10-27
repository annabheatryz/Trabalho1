#include "Batalha.h"

using namespace std;


// Construtor
Batalha::Batalha(Jogador& jogador, Jogador& cpu, Dificuldade dificuldade)
    : jogador(jogador), cpu(cpu), dificuldade(dificuldade) {
    // Sorteia um Pokémon inicial para o jogador e para a CPU
    pokemonJogador = jogador.escolherPokemon();
    pokemonCPU = cpu.escolherPokemon();
}

// Método para iniciar a batalha
void Batalha::iniciar() {
    cout << "A batalha começou entre " << jogador.getNome() << " e a CPU!\n";
    
    while (pokemonJogador->getHP() > 0 && pokemonCPU->getHP() > 0) {
        exibirStatus();
        turnoJogador();
        if (pokemonCPU->getHP() <= 0) break;
        turnoCPU();
    }
}


// Exibe o status dos Pokémon em batalha
void Batalha::exibirStatus() const {
    cout << "Status atual:\n";
    cout << jogador.getNome() << " - " << pokemonJogador->getNome() 
              << " HP: " << pokemonJogador->getHP() << "\n";
    cout << "CPU - " << pokemonCPU->getNome() 
              << " HP: " << pokemonCPU->getHP() << "\n";
}

// Turno do jogador
void Batalha::turnoJogador() {
    cout << jogador.getNome() << ", escolha um ataque:\n";
    pokemonJogador->listarAtaques();

    int escolha;
    cout << "Digite o número do ataque: ";
    cin >> escolha;

    Ataque ataqueEscolhido = pokemonJogador->escolherAtaque(escolha);
    int dano = calcularDano(ataqueEscolhido, pokemonJogador, pokemonCPU);
    pokemonCPU->receberDano(dano);

    cout << pokemonJogador->getNome() << " usou " << ataqueEscolhido.getNome() 
              << " causando " << dano << " de dano!\n";
}

// Turno da CPU
void Batalha::turnoCPU() {
    Ataque ataqueCPU;
    switch (dificuldade) {
        case FACIL:
            ataqueCPU = escolherAtaqueFraco(pokemonCPU);
            break;
        case MEDIO:
            ataqueCPU = pokemonCPU->escolherAtaqueAleatorio();
            break;
        case DIFICIL:
            ataqueCPU = escolherAtaqueForte(pokemonCPU);
            break;
    }

    int dano = calcularDano(ataqueCPU, pokemonCPU, pokemonJogador);
    pokemonJogador->receberDano(dano);

    cout << "CPU usou " << ataqueCPU.getNome() << " causando " << dano << " de dano!\n";
}

// Calcula o dano de um ataque
int Batalha::calcularDano(const Ataque& ataque, Pokemon* atacante, Pokemon* defensor) {
    int dano = ataque.getPoder();
    // Ajustes adicionais podem ser aplicados considerando tipo, nível, etc.
    return dano;
}