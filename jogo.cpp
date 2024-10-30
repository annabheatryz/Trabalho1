#include "jogo.h"

using namespace std;

Jogo::Jogo() : dificuldade(FACIL) {
    // Inicializa o gerador de números aleatórios
    srand(static_cast<unsigned>(time(0)));

    // Carrega os dados de Pokémon e ataques
    carregarPokemons();
    carregarAtaques();
}

void Jogo::mostrarMenu() {
    int opcao;
    do {
        cout << "=============================\n";
        cout << "        MENU PRINCIPAL       \n";
        cout << "=============================\n";
        cout << "1. Iniciar Batalha\n";
        cout << "2. Ajustar Dificuldade\n";
        cout << "3. Exibir Ranking\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                Jogador jogador = selecionarJogador();  // Função que seleciona ou cadastra jogador
                iniciarBatalha(jogador);
                break;
            }
            case 2:
                ajustarDificuldade();
                break;
            case 3:
                exibirRanking();
                break;
            case 4:
                salvarDados();
                cout << "Saindo do jogo...\n";
                break;
            default:
                cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 4);
}

void Jogo::iniciarBatalha(Jogador& jogador) {
    // Sorteia 3 Pokémon para o jogador e para a CPU
    jogador.sortearPokemons(pokemonsDisponiveis, 3);
    cpu.sortearPokemons(pokemonsDisponiveis, 3);

    // Escolhe o Pokémon inicial para ambos
    Pokemon* pokemonJogador = jogador.escolherPokemon();
    Pokemon* pokemonCPU = cpu.escolherPokemon();

    // Loop da batalha
    while (pokemonJogador->getHP() > 0 && pokemonCPU->getHP() > 0) {
        exibirStatus(pokemonJogador, pokemonCPU);
        turnoJogador(pokemonJogador, pokemonCPU);

        if (pokemonCPU->getHP() > 0) {
            turnoCPU(pokemonCPU, pokemonJogador);
        }
    }

    if (pokemonJogador->getHP() > 0) {
        cout << "Você venceu a batalha!\n";
        jogador.adicionarVitoria();
    } else {
        cout << "Você perdeu a batalha.\n";
        jogador.adicionarDerrota();
    }
}

void Jogo::ajustarDificuldade() {
    int escolha;
    cout << "Selecione a dificuldade:\n";
    cout << "1. Fácil\n";
    cout << "2. Médio\n";
    cout << "3. Difícil\n";
    cout << "Escolha uma dificuldade: ";
    cin >> escolha;

    switch (escolha) {
        case 1: dificuldade = FACIL; break;
        case 2: dificuldade = MEDIO; break;
        case 3: dificuldade = DIFICIL; break;
        default:
            cout << "Opção inválida. Mantendo dificuldade atual.\n";
            return;
    }

    cout << "Dificuldade ajustada!\n";
}

void Jogo::exibirRanking() {
    cout << "====== Ranking de Jogadores ======\n";
    for (const auto& jogador : jogadores) {
        cout << jogador.getNome() << " - Vitórias: " << jogador.getVitorias()
             << " - Derrotas: " << jogador.getDerrotas()
             << " - Pontuação: " << jogador.getPontuacao() << endl;
    }
}

void Jogo::salvarDados() {
    cout << "Dados salvos com sucesso!\n";
}

void Jogo::carregarPokemons() {
    ifstream arquivo("pokemons.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de pokémons.\n";
        return;
    }

    string linha;
    getline(arquivo, linha);  // Ignora cabeçalho

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome, tipo1, tipo2, temp;
        int hp, nivel, ataque, defesa;

        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');
        getline(ss, temp, ','); hp = stoi(temp);
        getline(ss, temp, ','); nivel = stoi(temp);
        getline(ss, temp, ','); ataque = stoi(temp);
        getline(ss, temp, ','); defesa = stoi(temp);

        pokemonsDisponiveis.emplace_back(nome, tipo1, tipo2, hp, nivel, ataque, defesa);
    }

    cout << "Pokémons carregados com sucesso.\n";
}

void Jogo::carregarAtaques() {
    ifstream arquivo("ataques.txt");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de ataques.\n";
        return;
    }

    string linha;
    getline(arquivo, linha);  // Ignora cabeçalho

    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string move, tipo, temp;
        int poder;
        float precisao;
        bool fisico;

        getline(ss, move, ',');
        getline(ss, tipo, ',');
        getline(ss, temp, ','); poder = stoi(temp);
        getline(ss, temp, ','); precisao = stof(temp);
        fisico = (tipo == "fisico");

        ataquesDisponiveis.emplace_back(move, fisico, poder, precisao, tipo);
    }

    cout << "Ataques carregados com sucesso.\n";
}

void Jogo::turnoJogador(Pokemon* atacante, Pokemon* defensor) {
    atacante->exibirAtaques();
    int escolha;
    cout << "Escolha um ataque: ";
    cin >> escolha;

    Ataque ataqueEscolhido = atacante->getAtaque(escolha);
    int dano = atacante->calcularDano(ataqueEscolhido, defensor);
    defensor->reduzirHP(dano);

    cout << atacante->getNome() << " usou " << ataqueEscolhido.getMove()
         << " causando " << dano << " de dano!\n";
}

void Jogo::turnoCPU(Pokemon* atacante, Pokemon* defensor) {
    Ataque ataqueEscolhido = atacante->escolherAtaqueAleatorio();
    int dano = atacante->calcularDano(ataqueEscolhido, defensor);
    defensor->reduzirHP(dano);

    cout << "CPU usou " << ataqueEscolhido.getMove() << " causando " << dano << " de dano!\n";
}

void Jogo::exibirStatus(const Pokemon* p1, const Pokemon* p2) const {
    cout << p1->getNome() << " HP: " << p1->getHP() << " | "
         << p2->getNome() << " HP: " << p2->getHP() << endl;
}
