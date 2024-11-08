#include "jogo.h"

using namespace std;

const vector<Pokemon>& Jogo::getPokemonsDisponiveis() const {
    return pokemonsDisponiveis;
}

const vector<Ataque>& Jogo::getAtaquesDisponiveis() const {
    return ataquesDisponiveis;
}

Jogo::Jogo() : dificuldade(Dificuldade::FACIL) {
    // Inicializa o gerador de números aleatórios
    srand(static_cast<unsigned>(time(0)));

    // Carrega os dados de Pokémon e ataques
    carregarPokemons();
    carregarAtaques();
    carregarJogadores();
}

void Jogo::mostrarMenu() {
    int opcao;
    do {
        cout << "\n=============================\n";
        cout << "        MENU PRINCIPAL       \n";
        cout << "=============================\n\n";
        cout << "1. Iniciar Batalha\n";
        cout << "2. Ajustar Dificuldade\n";
        cout << "3. Exibir Ranking\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: {
                Jogador jogador = selecionarJogador();  // Função que seleciona ou cadastra jogador
                iniciarBatalha(jogador, dificuldade);
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

// Função para carregar os jogadores do ranking
void Jogo::carregarJogadores() {
    ifstream arquivoEntrada("ranking.txt");
    string linha;

    if (arquivoEntrada.is_open()) {
        while (getline(arquivoEntrada, linha)) {
            istringstream iss(linha);
            string nome;
            int vitorias, derrotas, pontos;
            if (iss >> nome >> vitorias >> derrotas >> pontos) {
                Jogador jogador(nome, vitorias, derrotas, pontos);
                jogadores.push_back(jogador);
            }
        }
        arquivoEntrada.close();
    } else {
        cerr << "Erro ao abrir o arquivo de ranking.txt para leitura.\n";
    }
}


// Função para selecionar o jogador, que agora usa os dados carregados
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


void Jogo::prepararBatalha() {
    // Limpar ataques e status de cada Pokémon do jogador e da CPU
    for (auto* pokemon : pokemons_jogador) {
        if (pokemon) {
            pokemon->limparPokemons();  // Limpa dados do Pokémon do jogador
        }
    }
    for (auto* pokemon : pokemons_cpu) {
        if (pokemon) {
            pokemon->limparPokemons();  // Limpa dados do Pokémon da CPU
        }
    }
    
    // Limpar ataques dos Pokémon que estavam na batalha anterior
    for (auto& pokemon : pokemonsDisponiveis) {
        pokemon.limparAtaques();  // Remove ataques para evitar acúmulo de ataques antigos
    }

    // Esvaziar os vetores de Pokémon para uma nova seleção
    pokemons_jogador.clear();
    pokemons_cpu.clear();

    cout << "Preparação da batalha concluída. Dados dos Pokémon e vetores limpos e prontos para nova partida.\n";
}

void Jogo::iniciarBatalha(Jogador& jogador, Dificuldade dificuldade) {
    prepararBatalha();
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

        // Verifica se o Pokémon da CPU foi nocauteado
        if (atual_cpu->getHP() <= 0) {
            cout << atual_cpu->getNome() << " da CPU foi nocauteado!\n";
            
            // Verifica se a CPU tem outros Pokémon disponíveis
            bool algumPokemonCPUDisponivel = any_of(pokemons_cpu.begin(), pokemons_cpu.end(), [](Pokemon* p) {
                return p->getHP() > 0;
            });

            if (algumPokemonCPUDisponivel) {
                cout << "A CPU está escolhendo outro Pokémon...\n";
                atual_cpu = &escolherPokemonCPU();  // CPU escolhe outro Pokémon
                cout << "A CPU escolheu: " << atual_cpu->getNome() << " com " << atual_cpu->getHP() << " HP.\n";
            } else {
                cout << "Você venceu a batalha!\n";
                jogador.registrarResultado(jogador, true, dificuldade);
                break;  // Sai do loop se todos os Pokémon da CPU foram nocauteados
            }
        }
        // Turno da CPU, caso o Pokémon do jogador ainda esteja em pé
        turnoCPU(atual_cpu, jogador_atual);

        // Verifica se o Pokémon do jogador foi nocauteado
        if (jogador_atual->getHP() <= 0) {
            cout << jogador_atual->getNome() << " foi nocauteado!\n";
            
            // Verifica se há outros Pokémon com HP > 0 para continuar a batalha
            bool algumPokemonDisponivel = any_of(pokemons_jogador.begin(), pokemons_jogador.end(), [](Pokemon* p) {
                return p->getHP() > 0;
            });

            if (algumPokemonDisponivel) {
                cout << "Escolha outro Pokémon para continuar a batalha.\n";
                jogador_atual = &escolherPokemonJogador();  // Permite ao jogador escolher um novo Pokémon
            } else {
                cout << "Todos os seus Pokémons foram derrotados. Você perdeu a batalha.\n";
                jogador.registrarResultado(jogador, false, dificuldade);
                break;  // Sai do loop se todos os Pokémon do jogador foram nocauteados
            }
        }
        
        // Checa se o jogador deseja trocar de Pokémon após cada turno
        exibirStatus(jogador_atual, atual_cpu);
        cout << "Deseja trocar de Pokémon? (s/n): ";
        cin >> trocar;

        if (trocar == 's' || trocar == 'S') {
            jogador_atual = &escolherPokemonJogador();  // Permite ao jogador escolher um novo Pokémon
        }
    }
    // Restaura o HP de todos os Pokémons após o término da batalha
    for (auto& pokemon : pokemons_jogador) {
        pokemon->resetarHP();
    }
    for (auto& pokemon : pokemons_cpu) {
        pokemon->resetarHP();
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
        case 1: dificuldade = Dificuldade::FACIL; cout << endl; break;
        case 2: dificuldade = Dificuldade::MEDIO; break;
        case 3: dificuldade = Dificuldade::DIFICIL; break;
        default:
            cout << "Opção inválida. Mantendo dificuldade atual.\n";
            return;
    }

    cout << "Dificuldade ajustada!\n";
}

void Jogo::exibirRanking() {
    ifstream arquivo("ranking.txt");
    string linha;
    vector<Jogador> ranking;  // Vetor de jogadores

    cout << "====== Ranking de Jogadores ======\n\n";

    // Ler as linhas do arquivo
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string nome;
        int pontos, vitorias, derrotas;
        
        // Separando os campos da linha, que são separados por espaços
        ss >> nome >> pontos >> vitorias >> derrotas;

        // Armazenar o jogador no vetor
        ranking.push_back(Jogador(nome, pontos, vitorias, derrotas));
    }
    arquivo.close();

    // Ordenar o ranking com base na pontuação (ordem decrescente)
    sort(ranking.begin(), ranking.end(), [](const Jogador& a, const Jogador& b) {
        return a.getPontuacao() > b.getPontuacao();  // Ordenar pela pontuação (decrescente)
    });

    // Exibir o ranking
    for (const auto& jogador : ranking) {
        cout << jogador.getNome() << " - " << jogador.getPontuacao() << " pontos | "
             << jogador.getVitorias() << " vitórias | " << jogador.getDerrotas() << " derrotas\n";
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
        getline(ss, tipo1,',');
        getline(ss, tipo2,',');
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
        string move, tipo, temp, type;
        int poder;
        float precisao;
        bool fisico;

        getline(ss, move, ',');
        getline(ss, tipo, ',');
        getline(ss, temp, ','); poder = stoi(temp);
        getline(ss, temp, ','); precisao = stof(temp);
        getline(ss,type,',');
        fisico = (tipo == "fisico");
        type.pop_back();
        ataquesDisponiveis.emplace_back(move, fisico, poder, precisao, type);
    }

    cout << "Ataques carregados com sucesso.\n";
    arquivo.close();
}

void Jogo::sortearPokemons() {
    if (pokemonsDisponiveis.empty()) {
        cerr << "Erro: Não há Pokémons disponíveis para sortear.\n\n";
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
        
    }

    // Garantir que o Pokémon receba 4 ataques diferentes
    for (int i = 0; i < 4; ++i) {
        int index = rand() % ataquesValidos.size();
        pokemon.adicionarAtaque(ataquesValidos[index]);
        ataquesValidos.erase(ataquesValidos.begin() + index);  // Remover o ataque já usado para evitar repetição
    }
}


Pokemon& Jogo::escolherPokemonJogador() {
    size_t indice;
    exibirPokemons(); // Chama a função para mostrar os Pokémon disponíveis

    cout << "\nEscolha um Pokémon [0-2] para começar a batalha:\n";
    cin >> indice;

    // Validação do índice
    if (indice >= 0 && indice < pokemons_jogador.size()) {
        // Verifica se o Pokémon escolhido está derrotado
        if (pokemons_jogador[indice]->getHP() > 0) {
            return *pokemons_jogador[indice]; // Retorna o Pokémon escolhido
        } else {
            cout << "Este Pokémon está derrotado. Escolha outro." << endl;
            return escolherPokemonJogador(); // Chama a função novamente para escolher outro Pokémon
        }
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
    int ataqueEscolhido;
    
    cout << "\nEscolha um ataque [1-" << atacante->getTotalAtaques() << "]:\n";
    for (int i = 0; i < atacante->getTotalAtaques(); ++i) {
        cout << i+1 << ". " << atacante->getAtaque(i).getMove() << endl;
    }

    cin >> ataqueEscolhido;

    if (ataqueEscolhido < 0 || ataqueEscolhido > atacante->getTotalAtaques()) {  // Valida se a escolha é válida
        cout << "Ataque inválido. Escolha novamente.\n";
        turnoJogador(atacante, defensor);
        return;
    }

   Ataque ataque = atacante->getAtaque(ataqueEscolhido - 1);
    int dano = atacante->calcularDano(ataque, *defensor);
    defensor->reduzirHP(dano);

    cout << atacante->getNome() << " usou " << ataque.getMove() << " causando " << dano << " de dano!\n VEZ DO ADVERSÁRIO: \n";
}

void Jogo::turnoCPU(Pokemon* atacante, Pokemon* defensor) {
    cout << "\nTurno da CPU...\n";

    int indice = rand() % 4; // Escolhe um índice aleatório entre 0 e 3
    Ataque ataqueEscolhido = atacante->getAtaque(indice);
    int dano = atacante->calcularDano(ataqueEscolhido, *defensor);
    defensor->reduzirHP(dano);

    if (atacante->getTotalAtaques() < 4) {
        cerr << "Erro: Pokémon da CPU não tem ataques suficientes.\n";
        return;
    }

    cout << "CPU usou " << ataqueEscolhido.getMove() << " causando " << dano << " de dano!\n";
}

void Jogo::exibirStatus(const Pokemon* p1, const Pokemon* p2) const {
    cout << p1->getNome() << " HP: " << p1->getHP() << " | " << p2->getNome() << " HP: " << p2->getHP() << endl;
}

void Jogo::exibirPokemons() {
    cout << "\nPokémons disponíveis para escolha:\n";
    for (size_t i = 0; i < pokemons_jogador.size(); ++i) {
        const auto& pokemon = *pokemons_jogador[i];
        cout << i << ". Nome: " << pokemon.getNome()
             << ", HP: " << pokemon.getHP() << endl;
    }
}