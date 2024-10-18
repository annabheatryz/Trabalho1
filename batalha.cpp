#include "batalha.h"
#include <iostream>

using namespace std;

Batalha::Batalha() {}
Batalha::Batalha(const vector<Pokemon>& pk_jogador, const vector<Pokemon>& pk_cpu, int atual_jogador, int atual_cpu) : pokemons_jogador(pk_jogador), pokemons_cpu(pk_cpu), pokemon_jogador_atual(atual_jogador), pokemon_cpu_atual(atual_cpu) {}

void Batalha::escolherPokemon() {
    if (pokemons_jogador.empty()) {
        cerr << "Erro: Nenhum Pokémon disponível! Verifique a inicialização dos Pokémons.\n";
        return;
    }

    int novo_pokemon;

    while (true) {
        cout << "Escolha o novo Pokémon (0-" << static_cast<int>(pokemons_jogador.size() - 1) << "): ";
        cin >> novo_pokemon;

        // Verifica se a entrada é válida
        if (novo_pokemon < 0 || novo_pokemon >= static_cast<int>(pokemons_jogador.size())) {
            cerr << "Escolha inválida! O número deve estar entre 0 e " << static_cast<int>(pokemons_jogador.size() - 1) << ".\n";
            continue;
        }

        // Verifica se o Pokémon não está desmaiado
        if (pokemons_jogador[novo_pokemon].getHP() <= 0) {
            cerr << "O Pokémon escolhido já está desmaiado! Tente novamente.\n";
            continue;
        }

        // Se tudo estiver válido, sai do loop
        break;
    }

    pokemon_jogador_atual = novo_pokemon;
    cout << "O Pokémon escolhido foi: " << pokemons_jogador[pokemon_jogador_atual].getNome() << "!\n";
}

// void iniciar();
// void atacar(int atq_escolhido);
// void mostrarStatus();
// int calcularDano(const Ataque& ataque, const Pokemon& atacante, const Pokemon& defensor);