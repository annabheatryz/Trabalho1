#include "pokemon.h"
#include "ataque.h"
#include "batalha.h"
#include "jogo.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {

    // Carregar lista de Pokemons e Ataques
    Jogo::carregarPokemons();
    //vector<Ataque> lista_ataques = jogo.carregarAtaques("ataques.txt");

    return 0;
}