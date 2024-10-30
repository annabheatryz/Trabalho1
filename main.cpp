#include <iostream>
#include "jogo.h"
#include "pokemon.h"
#include "ataque.h"

using namespace std;

int main() {
    // Inicializa o jogo
    Jogo jogo;

    // Carrega os Pokémon e ataques disponíveis
    jogo.carregarPokemons();
    jogo.carregarAtaques();

    // Cria um Pokémon para teste
    Pokemon pikachu("Pikachu", "Elétrico", "", 100, 10, 55, 40, 90, 50, 50);

    // Sorteia ataques para o Pikachu a partir dos ataques disponíveis
    cout << "\nSorteando 4 ataques para Pikachu...\n";
    pikachu.sortearAtaques(jogo.getAtaquesDisponiveis(), 4);  // Chama o sorteio com 4 ataques

    // Exibe os ataques sorteados
    pikachu.exibirAtaques();

    return 0;
}
