#include "Batalha.h"

using namespace std;

// Construtor
Batalha::Batalha(Jogador& jogador, Jogador& cpu, Dificuldade dificuldade)
    : jogador(jogador), cpu(cpu), dificuldade(dificuldade) {
    // Sorteia um Pokémon inicial para o jogador e para a CPU
    pokemonJogador = jogador.escolherPokemon();
    pokemonCPU = cpu.escolherPokemon();
}


// Exibe o status dos Pokémon em batalha
void Batalha::exibirStatus() const {
    cout << "Status atual:\n";
    cout << jogador.getNome() << " - " << pokemonJogador.getNome() 
         << " HP: " << pokemonJogador.getHP() << "\n";
    cout << "CPU - " << pokemonCPU.getNome() 
         << " HP: " << pokemonCPU.getHP() << "\n";
}

// Turno do jogador
void Batalha::turnoJogador() {
    cout << jogador.getNome() << ", escolha um ataque:\n";
    
    //  Exibir lista de ataques e obter escolha
    pokemonJogador.exibirAtaques();
    int escolha;
    cout << "Digite o número do ataque: ";
    cin >> escolha;

    Ataque ataqueEscolhido = pokemonJogador.sortearAtaques(escolha);
    int dano = pokemonJogador.calcularDano(ataqueEscolhido, pokemonCPU);
    pokemonCPU.reduzirHP(dano);

    cout << pokemonJogador.getNome() << " usou " << ataqueEscolhido.getMove() 
         << " causando " << dano << " de dano!\n";
}

// Turno da CPU
void Batalha::turnoCPU() {
    Ataque ataqueCPU;
    switch (dificuldade) {
        case FACIL:
            ataqueCPU = pokemonCPU.escolherAtaqueFraco();
            break;
        case MEDIO:
            ataqueCPU = pokemonCPU.escolherAtaqueAleatorio();
            break;
        case DIFICIL:
            ataqueCPU = pokemonCPU.escolherAtaqueForte();
            break;
    }

    int dano = pokemonCPU.calcularDano(ataqueCPU, pokemonJogador);
    pokemonJogador.reduzirHP(dano);

    cout << "CPU usou " << ataqueCPU.getMove() << " causando " << dano << " de dano!\n";
}

Ataque Batalha::escolherAtaqueFraco(Pokemon* pokemonOponente) {
    // Preencha os ataques primeiro
    sortearAtaques(vetor_ataques, 4);
    
    // Lógica para escolher um ataque fraco a partir do vetor de ataques sorteados
    // Por exemplo, você pode escolher o ataque com menor dano
    Ataque ataqueFraco;
    int danoMinimo = INT_MAX;

    for (const Ataque& ataque : ataque) {
        if (ataque.getDano() < danoMinimo) {
            danoMinimo = ataque.getDano();
            ataqueFraco = ataque;
        }
    }

    return ataqueFraco;
}

Ataque Batalha::escolherAtaqueForte(Pokemon* pokemonOponente) {
    // Preencha os ataques primeiro
    sortearAtaques(vetor_ataques, 4);
    
    // Lógica para escolher um ataque forte a partir do vetor de ataques sorteados
    // Por exemplo, você pode escolher o ataque com maior dano
    Ataque ataqueForte;
    int danoMaximo = -1;

    for (const Ataque& ataque : ataque) {
        if (ataque.getDano() > danoMaximo) {
            danoMaximo = ataque.getDano();
            ataqueForte = ataque;
        }
    }

    return ataqueForte;
}
