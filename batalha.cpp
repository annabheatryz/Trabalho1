#include "batalha.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

// Tabela de efetividade entre tipos de Pokémon.
// Cada tipo tem efetividade (dano) diferente dependendo do tipo do oponente.
map<string, map<string, double>> efetividadeTipos = {
    {"Normal", {{"Pedra", 0.5}, {"Fantasma", 0}, {"Metal", 0.5}}},
    {"Fogo", {{"Fogo", 0.5}, {"Água", 0.5}, {"Grama", 2}, {"Gelo", 2}, {"Inseto", 2}, {"Metal", 2}}},
    {"Água", {{"Fogo", 2}, {"Água", 0.5}, {"Grama", 0.5}, {"Terrestre", 2}}},
    {"Elétrico", {{"Água", 2}, {"Elétrico", 0.5}, {"Grama", 0.5}, {"Voador", 2}, {"Terrestre", 0}}},
};

// Construtor padrão da classe Batalha (não faz nada específico).
Batalha::Batalha() {}

// Construtor que inicializa a batalha com dois vetores de Pokémon (do jogador e da CPU) e os índices dos Pokémon ativos.
Batalha::Batalha(const vector<Pokemon>& pk_jogador, const vector<Pokemon>& pk_cpu, int atual_jogador, int atual_cpu)
    : pokemons_jogador(pk_jogador), pokemons_cpu(pk_cpu), pokemon_jogador_atual(atual_jogador), pokemon_cpu_atual(atual_cpu), fimDejogo(false) {}

// Função para escolher um novo Pokémon durante a batalha.
void Batalha::escolherPokemon() {
    // Verifica se o jogador tem Pokémons disponíveis.
    if (pokemons_jogador.empty()) {
        cerr << "Erro: Nenhum Pokémon disponível! Verifique a inicialização dos Pokémons.\n";
        return;
    }

    int novo_pokemon;

    // Loop para garantir que o jogador escolha um Pokémon válido e que não esteja desmaiado.
    while (true) {
        cout << "Escolha o novo Pokémon (0-" << static_cast<int>(pokemons_jogador.size() - 1) << "): ";
        cin >> novo_pokemon;

        // Verifica se a escolha é válida dentro do intervalo permitido.
        if (novo_pokemon < 0 || novo_pokemon >= static_cast<int>(pokemons_jogador.size())) {
            cerr << "Escolha inválida! O número deve estar entre 0 e " << static_cast<int>(pokemons_jogador.size() - 1) << ".\n";
            continue;
        }

        // Verifica se o Pokémon escolhido ainda tem HP (não está desmaiado).
        if (pokemons_jogador[novo_pokemon].getHP() <= 0) {
            cerr << "O Pokémon escolhido já está desmaiado! Tente novamente.\n";
            continue;
        }

        // Se tudo estiver válido, sai do loop e escolhe o Pokémon.
        break;
    }

    // Atualiza o Pokémon ativo do jogador.
    pokemon_jogador_atual = novo_pokemon;
    cout << "O Pokémon escolhido foi: " << pokemons_jogador[pokemon_jogador_atual].getNome() << "!\n";

    // Após a troca, a CPU realiza seu turno.
    turnoCPU();
}

// Função que inicia a batalha.
void Batalha::iniciar() {
    cout << "Batalha Iniciada!\n";
    mostrarStatus();  // Exibe o status inicial dos Pokémon.
    
    // Loop principal da batalha, continua até o fim do jogo.
    while (!fimDejogo) {
        int escolha;
        cout << "\n 1 - Atacar\n 2 - Trocar Pokémon\n Escolha: ";
        cin >> escolha;

        // Escolha do jogador para atacar ou trocar Pokémon.
        if (escolha == 1) {
            int ataque;
            cout << "Escolha o ataque(0-3): ";
            cin >> ataque;
            atacar(ataque);  // Realiza o ataque com base no índice.
        } else if (escolha == 2) {
            escolherPokemon();  // Troca o Pokémon ativo.
        }

        turnoCPU();  // CPU realiza sua ação.
        mostrarStatus();  // Exibe o status após cada turno.

        // Verifica se o jogo acabou (todos os Pokémon de um jogador estão desmaiados).
        if (pokemons_cpu[pokemon_cpu_atual].getHP() <= 0) {
            cout << "Você venceu! :)\n";
            fimDejogo = true;
        } else if (pokemons_jogador[pokemon_jogador_atual].getHP() <= 0) {
            cout << "Você perdeu! :(\n";
            fimDejogo = true;
        }
    }
}

// Função que controla o turno da CPU.
void Batalha::turnoCPU() {
    Pokemon &atacante = pokemons_cpu[pokemon_cpu_atual];  // Pokémon da CPU.
    Pokemon &defensor = pokemons_jogador[pokemon_jogador_atual];  // Pokémon do jogador.

    Ataque ataque = escolherAtaque(atacante);  // A CPU escolhe um ataque.

    // Calcula o dano e reduz o HP do Pokémon do jogador.
    int dano = calcularDano(ataque, atacante, defensor);
    defensor.reduzirHP(dano);

    cout << atacante.getNome() << " causou " << dano << " de dano!\n";
}

// Função que calcula o dano causado por um ataque.
int Batalha::calcularDano(const Ataque& ataque, const Pokemon& atacante, const Pokemon& defensor) {
    int level = atacante.getNivel();
    int power = ataque.getPoder();
    int A = (ataque.getCategoria() == "Fisico") ? atacante.getAtaque() : atacante.getAtaqueEspecial();
    int D = (ataque.getCategoria() == "Fisico") ? defensor.getDefesa() : defensor.getDefesaEspecial();

    double critical = sorteioCritico() ? 2.0 : 1.0;  // Verifica se o ataque é crítico.
    double stab = (ataque.getTipo() == atacante.getTipo1()) ? 1.5 : 1.0;  // Bônus de tipo igual.

    // Calcula a efetividade do ataque baseado nos tipos do Pokémon defensor.
    double type1 = efetividadeTipos[ataque.getTipo()][defensor.getTipo1()];
    double type2 = efetividadeTipos[ataque.getTipo()][defensor.getTipo2()];

    // Se o ataque não for efetivo, retorna 0 de dano.
    if (type1 == 0 || type2 == 0) {
        cout << "O ataque não é efetivo!\n";
        return 0;
    }

    // Um valor aleatório para tornar o dano variável.
    double random = (rand() % 39 + 217) / 255.0;

    // Fórmula para calcular o dano.
    int dano = (((2 * level * power * A / D) / 50) + 2) * critical * stab * type1 * type2 * random;
    return dano > 0 ? dano : 1;  // O dano mínimo é 1.
}

// Função que escolhe um ataque para a CPU ou o jogador.
Ataque Batalha::escolherAtaque(const Pokemon& atacante, int ataqueEscolhido) {
    return atacante.getAtaque(ataqueEscolhido);  // Retorna o ataque baseado no índice.
}

// Função para o jogador realizar um ataque.
void Batalha::atacar(int ataqueEscolhido) {
    Pokemon &atacante = pokemons_jogador[pokemon_jogador_atual];
    Pokemon &defensor = pokemons_cpu[pokemon_cpu_atual];

    Ataque ataque = escolherAtaque(atacante, ataqueEscolhido);  // Escolhe o ataque.

    int dano = calcularDano(ataque, atacante, defensor);  // Calcula o dano.
    defensor.reduzirHP(dano);  // Reduz o HP do defensor.

    cout << atacante.getNome() << " causou " << dano << " de dano!\n";
}

// Função que decide se o ataque é crítico (chance de 1/16).
bool Batalha::sorteioCritico() {
    return (rand() % 16) == 0;
}

// Função que exibe o status atual dos Pokémon.
void Batalha::mostrarStatus() {
    cout << "\nStatus:\n";
    cout << pokemons_jogador[pokemon_jogador_atual].getNome() << " - HP: "
         << pokemons_jogador[pokemon_jogador_atual].getHP() << "\n";
    cout << pokemons_cpu[pokemon_cpu_atual].getNome() << " - HP: "
         << pokemons_cpu[pokemon_cpu_atual].getHP() << "\n";
}

int main() {
    // Cria dois ataques de teste.
Ataque ataque1("Chama", "Fogo", 50, 1.0, "Fisico");  // Adicione o parâmetro faltante (1.0).
Ataque ataque2("Jato de Água", "Água", 40, 1.0, "Especial");  // Adicione o parâmetro faltante (1.0).


    // Cria dois Pokémons de teste.
    Pokemon pikachu("Pikachu", "Elétrico", "", 100, 5, 40, 30, 90, 50, 40);
    Pokemon charmander("Charmander", "Fogo", "", 90, 5, 45, 35, 65, 60, 50);

    // Vetores de Pokémons do jogador e da CPU.
    vector<Pokemon> pokemons_jogador = {pikachu};
    vector<Pokemon> pokemons_cpu = {charmander};

    // Cria a batalha.
    Batalha batalha(pokemons_jogador, pokemons_cpu, 0, 0);

    // Inicia a batalha.
    batalha.iniciar();

    return 0;
}
