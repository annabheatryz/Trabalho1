#include "jogo.h"

using namespace std;

const vector<Pokemon>& Jogo::getPokemonsDisponiveis() const {
    return pokemonsDisponiveis;
}

const vector<Ataque>& Jogo::getAtaquesDisponiveis() const {
    return ataquesDisponiveis;
}

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

Jogador Jogo::selecionarJogador() {
    string nomeJogador;
    cout << "Digite o nome do jogador: ";
    cin >> nomeJogador;

    // Verifica se o jogador já está registrado na lista interna de jogadores
    auto it = find_if(jogadores.begin(), jogadores.end(),
                      [&nomeJogador](const Jogador& j) { return j.getNome() == nomeJogador; });

    if (it != jogadores.end()) {
        cout << "Bem-vindo de volta, " << nomeJogador << "!\n";
        return *it;  // Retorna o jogador já existente
    } else {
        cout << "Novo jogador criado: " << nomeJogador << "!\n";
        Jogador novoJogador(nomeJogador);
        jogadores.push_back(novoJogador);  // Adiciona à lista interna

        // Adiciona o novo jogador ao arquivo de ranking
        ofstream arquivoSaida("ranking.txt", ios::app);  // Abre em modo de append
        if (arquivoSaida.is_open()) {
            arquivoSaida << nomeJogador << " 0 0 0\n";  // Inicializa com 0 vitórias, derrotas e pontos
            arquivoSaida.close();
        } else {
            cerr << "Erro ao abrir o arquivo de ranking.txt para escrita.\n";
        }

        return novoJogador;
    }
}

void Jogo::iniciarBatalha(Jogador& jogador) {
    // Sorteia 3 Pokémon para o jogador e para a CPU
    jogador.sortearPokemons(pokemonsDisponiveis, 3);
    cpu.sortearPokemons(pokemonsDisponiveis, 3);

    // Escolhe o Pokémon inicial para ambos
    Pokemon pokemonJogador = jogador.escolherPokemon();
    Pokemon pokemonCPU = cpu.pokemonCPU();

    // Loop da batalha
    while (true) {
        exibirStatus(&pokemonJogador, &pokemonCPU);
        turnoJogador(&pokemonJogador, &pokemonCPU); // Chama a função do jogador

        // Verifica se o Pokémon do CPU foi nocauteado
        if (pokemonCPU.getHP() <= 0) {
            cout << "Você venceu a batalha!\n";
            jogador.registrarVitoria();
            break;  // Sai do loop se o Pokémon da CPU foi nocauteado
        }

        // O turno da CPU só ocorre se o Pokémon do jogador ainda está em pé
        turnoCPU(&pokemonCPU, &pokemonJogador);  // Passa a referência da CPU

        // Verifica se o Pokémon do jogador foi nocauteado
        if (pokemonJogador.getHP() <= 0) {
            cout << "Você perdeu a batalha.\n";
            jogador.registrarDerrota();
            break;  // Sai do loop se o Pokémon do jogador foi nocauteado
        }
        
        // Checa se o jogador deseja trocar de Pokémon após cada turno
        char trocar;
        cout << "Deseja trocar de Pokémon? (s/n): ";
        cin >> trocar;

        if (trocar == 's' || trocar == 'S') {
            pokemonJogador = jogador.escolherPokemon();  // Permite ao jogador escolher um novo Pokémon
        }
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
        int hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial;

        getline(ss, nome, ',');
        getline(ss, tipo1, ',');
        getline(ss, tipo2, ',');
        getline(ss, temp, ','); hp = stoi(temp);
        getline(ss, temp, ','); nivel = stoi(temp);
        getline(ss, temp, ','); ataque = stoi(temp);
        getline(ss, temp, ','); defesa = stoi(temp);
        getline(ss, temp, ','); velocidade = stoi(temp);
        getline(ss, temp, ','); ataque_especial = stoi(temp);
        getline(ss, temp, ','); defesa_especial = stoi(temp);

        pokemonsDisponiveis.emplace_back(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial);
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
    int dano = atacante->calcularDano(ataqueEscolhido, *defensor);
    defensor->reduzirHP(dano);

    cout << atacante->getNome() << " usou " << ataqueEscolhido.getMove()
         << " causando " << dano << " de dano!\n";
}

void Jogo::turnoCPU(Pokemon* atacante, Pokemon* defensor) {
    int indice = rand() % 4; // Escolhe um índice aleatório entre 0 e 3
    Ataque ataqueEscolhido = atacante->getAtaque(indice);
    int dano = atacante->calcularDano(ataqueEscolhido, *defensor);
    defensor->reduzirHP(dano);

    cout << "CPU usou " << ataqueEscolhido.getMove() << " causando " << dano << " de dano!\n";
}

void Jogo::exibirStatus(const Pokemon* p1, const Pokemon* p2) const {
    cout << p1->getNome() << " HP: " << p1->getHP() << " | "
         << p2->getNome() << " HP: " << p2->getHP() << endl;
}
