#include "pokemon.h"
#include "ataque.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    Pokemon pokemon;
    Ataque ataque;
    // Carregar lista de Pokemons e Ataques
    vector<Pokemon> vetor_pokemons = pokemon.carregarPokemons("pokemons.txt");
    vector<Ataque> lista_ataques = ataque.carregarAtaques("ataques.txt");

    // Sorteia 6 Pokemons, sendo 3 para o jogador e 3 para a CPU
    vector<Pokemon> pokemons_sorteados = pokemon.sortearPokemons(vetor_pokemons, 6);

    // Separar os 3 primeiros para o jogador e os 3 últimos para a CPU
    vector<Pokemon> pokemons_jogador(pokemons_sorteados.begin(), pokemons_sorteados.begin() + 3);
    vector<Pokemon> pokemons_cpu(pokemons_sorteados.begin() + 3, pokemons_sorteados.end());

    // Sortear ataques para os Pokémons do jogador
    cout << "Pokemons do jogador e seus ataques: " << endl;
    for (Pokemon& p : pokemons_jogador) {
        vector<Ataque> ataques_sorteados = ataque.sortearAtaques(lista_ataques, p, 4);
        cout << p.getNome() << " - " << p.getTipo1() << "/" << p.getTipo2() << "- Nível: " << p.getNivel() << endl;
        for (const Ataque& atq : ataques_sorteados) {
            cout << "  Move: " << atq.getMove() << " - Tipo: " << atq.getTipo() << endl;
            
            // Remover os pokemons que já foram sorteados para evitar repetições
            for (size_t i = 0; i < lista_ataques.size(); ++i) {
                if (lista_ataques[i] == atq) {  // Usamos a sobrecarga do operador "=="
                    lista_ataques.erase(lista_ataques.begin() + i);
                    break;
                }
            }
        }
        cout << endl;
    }

    // Sortear ataques para os Pokémons da CPU
    cout << "Pokemons da CPU e seus ataques: " << endl;
    for (Pokemon& p : pokemons_cpu) {
        vector<Ataque> ataques_sorteados = ataque.sortearAtaques(lista_ataques, p, 4);
        cout << p.getNome() << " - " << p.getTipo1() << "/" << p.getTipo2() << "- Nível: " << p.getNivel() << endl;
        for (const Ataque& atq : ataques_sorteados) {
            cout << "  Move: " << atq.getMove() << " - Tipo: " << atq.getTipo() << endl;

            // Remover os pokemons que já foram sorteados para evitar repetições
            for (size_t i = 0; i < lista_ataques.size(); ++i) {
                if (lista_ataques[i] == atq) {  // Usamos a sobrecarga do operador "=="
                    lista_ataques.erase(lista_ataques.begin() + i);
                    break;
                }
            }
        }
        cout << endl;
    }

    return 0;
}
