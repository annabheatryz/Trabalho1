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
    sortearPokemons();
    char trocar;

    cout << "===================Iniciando batalha===================" << endl;

    // Escolhe um pokemon inicial para ambos
    jogador_atual = &escolherPokemonJogador();
    atual_cpu = &escolherPokemonCPU();

    // Imprimir o Pokémon da CPU selecionado e seu HP inicial
    cout << "A CPU escolheu: " << atual_cpu->getNome() << " com " << atual_cpu->getHP() << " HP.\n";

    // Loop da batalha
    while (true) {
        exibirStatus(jogador_atual, atual_cpu);
        turnoJogador(jogador_atual, atual_cpu); // Chama a função do jogador

        // Verifica se o Pokémon do CPU foi nocauteado
        if (atual_cpu->getHP() <= 0) {
            cout << "Você venceu a batalha!\n";
            jogador.registrarVitoria();
            break;  // Sai do loop se o Pokémon da CPU foi nocauteado
        }

        // O turno da CPU só ocorre se o Pokémon do jogador ainda está em pé
        turnoCPU(atual_cpu, jogador_atual);  // Passa a referência da CPU

        // Verifica se o Pokémon do jogador foi nocauteado
        if (jogador_atual->getHP() <= 0) {
            cout << "Você perdeu a batalha.\n";
            jogador.registrarDerrota();
            break;  // Sai do loop se o Pokémon do jogador foi nocauteado
        }
        
        // Checa se o jogador deseja trocar de Pokémon após cada turno
        cout << "Deseja trocar de Pokémon? (s/n): ";
        cin >> trocar;

        if (trocar == 's' || trocar == 'S') {
            jogador_atual = &escolherPokemonJogador();  // Permite ao jogador escolher um novo Pokémon
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
    arquivo.close();
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
    arquivo.close();
}

void Jogo::sortearPokemons() {
    if (pokemonsDisponiveis.empty()) {
        cerr << "Erro: Não há Pokémons disponíveis para sortear.\n";
        return;
    }

    cout << "Sorteando Pokémons para o jogador e a CPU..." << endl;

    
    vector<Pokemon*> copiaPokemons;
    for (auto& pokemon : pokemonsDisponiveis) {
        copiaPokemons.push_back(&pokemon);
    }

    // Sortear três Pokémon para o jogador sem repetição
    for (int i = 0; i < 3; ++i) {
        int index = rand() % copiaPokemons.size();
        pokemons_jogador.push_back(copiaPokemons[index]);
        distribuirAtaques(*pokemons_jogador[i]);
        copiaPokemons.erase(copiaPokemons.begin() + index);
    }

    // Sortear três Pokémon para a CPU sem repetição
    for (int i = 0; i < 3; ++i) {
        int index = rand() % copiaPokemons.size();
        pokemons_cpu.push_back(copiaPokemons[index]);
        distribuirAtaques(*pokemons_cpu[i]);
        copiaPokemons.erase(copiaPokemons.begin() + index);
    }
}


void Jogo::distribuirAtaques(Pokemon& pokemon) {
    vector<Ataque> ataquesValidos;
    vector<Ataque> ataquesNormais;

    // Verificar se há ataques disponíveis
    if (ataquesDisponiveis.empty()) {
        cerr << "Erro: Não há ataques disponíveis para distribuição.\n";
        return;
    } else {
        cout << "Número de ataques disponíveis: " << ataquesDisponiveis.size() << endl;
    }

    // Filtra ataques que correspondem aos tipos do Pokémon e ataques do tipo "Normal"
    for (const auto& ataque : ataquesDisponiveis) {
        if (ataque.getTipo() == "Normal") {
            ataquesNormais.push_back(ataque);  // Armazena ataques do tipo Normal
        }
        if (ataque.getTipo() == pokemon.getTipo1() || ataque.getTipo() == pokemon.getTipo2()) {
            ataquesValidos.push_back(ataque);
        }
    }

    // Se não houver ataques válidos suficientes, use ataques do tipo "Normal"
    while (ataquesValidos.size() < 4 && !ataquesNormais.empty()) {
        ataquesValidos.push_back(ataquesNormais.back());
        ataquesNormais.pop_back();
    }

    // Se ainda não houver ataques suficientes, exiba erro
    if (ataquesValidos.size() < 4) {
        cerr << "Erro: Não há ataques válidos suficientes disponíveis para o Pokémon " << pokemon.getNome() << ".\n";
        return;
    }

    // Garantir que o Pokémon receba 4 ataques diferentes
    for (int i = 0; i < 4; ++i) {
        int index = rand() % ataquesValidos.size();
        pokemon.adicionarAtaque(ataquesValidos[index]);
        ataquesValidos.erase(ataquesValidos.begin() + index);  // Remover o ataque já usado para evitar repetição
    }

    cout << "Ataques distribuídos com sucesso para o Pokémon " << pokemon.getNome() << "!\n";
}




Pokemon& Jogo::escolherPokemonJogador() {
    Jogador jogador;
    size_t indice;


    cout << "Número de Pokémons disponíveis: " << pokemons_jogador.size() << endl; //Verificando se o vetor estava sendo inicializado corretamente
    cout << "Escolha um Pokémon [0-2] para começar a batalha:\n";
    jogador.exibirPokemons();
    cin >> indice;

    if (indice >= 0 && indice < pokemons_jogador.size()) {
        // Verifica se o Pokémon escolhido está derrotado
        if (pokemons_jogador[indice]->getHP() <= 0) {
                cout << "Este Pokémon está derrotado. Escolha outro." << endl;
            return escolherPokemonJogador(); // Chama a função novamente para escolher outro Pokémon
        }
        return *pokemons_jogador[indice]; // Retorna o Pokémon escolhido
    } else {
        cout << "Índice inválido. Tente novamente." << endl;
        return escolherPokemonJogador(); // Chama a função novamente para escolher outro Pokémon
    }
}

Pokemon& Jogo::escolherPokemonCPU() {
    // Sorteia um índice entre 0 e 2 para escolher um dos três Pokémon da CPU
    int indice;
    do {
        indice = rand() % pokemons_cpu.size(); 
    } while (pokemons_cpu[indice]->getHP() <= 0);  // Garante que o Pokémon escolhido não esteja derrotado

    return *pokemons_cpu[indice];  
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