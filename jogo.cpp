#include "jogo.h"

using namespace std;

// Vetor global de pokemons disponiveis
vector<Pokemon> pokemonsDisponiveis;

Jogo::Jogo() : dificuldade(FACIL) {   // Define a dificuldade padrão como FACIL
    carregarPokemons();
    carregarAtaques();
}

void Jogo::mostrarMenu() {
    int opcao = 0;
    do {
        cout << "=============================\n";
        cout << "        MENU PRINCIPAL       \n";
        cout << "=============================\n";
        cout << "1. Iniciar Batalha\n";
        cout << "2. Selecionar Dificuldade\n";
        cout << "3. Exibir Ranking\n";
        cout << "4. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                iniciarBatalha();
                break;
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

void Jogo::iniciarBatalha() {
    const size_t qtd_pokemons = 3;

    Jogador jogador = selecionarJogador();
    jogador.sortearPokemons(pokemonsDisponiveis, qtd_pokemons);
    cpu.sortearPokemons();

    Batalha batalha(jogador, cpu, dificuldade);
    batalha.iniciar();
}

void Jogo::ajustarDificuldade() {
    int escolha = 0;
    cout << "Selecione a dificuldade:\n";
    cout << "1. Fácil\n";
    cout << "2. Médio\n";
    cout << "3. Difícil\n";
    cout << "Escolha uma dificuldade: ";
    cin >> escolha;

    switch (escolha) {
        case 1:
            dificuldade = FACIL;
            break;
        case 2:
            dificuldade = MEDIO;
            break;
        case 3:
            dificuldade = DIFICIL;
            break;
        default:
            cout << "Opção inválida. Dificuldade mantida como "
                      << (dificuldade == FACIL ? "Fácil" : dificuldade == MEDIO ? "Médio" : "Difícil") << ".\n";
            return;
    }

    cout << "Dificuldade ajustada para " 
              << (dificuldade == FACIL ? "Fácil" : dificuldade == MEDIO ? "Médio" : "Difícil") << "!\n";
}

void Jogo::exibirRanking() {
    cout << "====== Ranking de Jogadores ======\n";
    for (const auto& jogador : jogadores) {
        cout << "Jogador: " << jogador.getNome() 
                  << " - Vitórias: " << jogador.getVitorias()
                  << " - Derrotas: " << jogador.getDerrotas()
                  << " - Pontuação: " << jogador.getPontuacao() << endl;
    }
}

void Jogo::salvarDados() {
    cout << "Dados salvos com sucesso!\n";
}

void Jogo::carregarPokemons() {
    ifstream arquivo("pokemons.csv");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de pokémons." << endl;
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora a linha de cabeçalho

    while (getline(arquivo, linha)) {
        stringstream linha_stream(linha);
        string nome, tipo1, tipo2, temp;
        int hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial;

        getline(linha_stream, nome, ',');
        getline(linha_stream, tipo1, ',');
        getline(linha_stream, tipo2, ',');
        getline(linha_stream, temp, ','); hp = stoi(temp);
        getline(linha_stream, temp, ','); nivel = stoi(temp);
        getline(linha_stream, temp, ','); ataque = stoi(temp);
        getline(linha_stream, temp, ','); defesa = stoi(temp);
        getline(linha_stream, temp, ','); velocidade = stoi(temp);
        getline(linha_stream, temp, ','); ataque_especial = stoi(temp);
        getline(linha_stream, temp, ','); defesa_especial = stoi(temp);

        pokemonsDisponiveis.emplace_back(nome, tipo1, tipo2, hp, nivel, ataque, defesa, velocidade, ataque_especial, defesa_especial);
    }

    arquivo.close();
    cout << "Pokémons carregados com sucesso." << endl;
}

void Jogo::carregarAtaques() {
     ifstream arquivo("ataques.csv");
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de ataques." << endl;
        return;
    }

    string linha;
    getline(arquivo, linha); // Ignora a linha de cabeçalho

    // Ler as demais linhas do CSV
    while (getline(arquivo, linha)) {
        stringstream linha_stream(linha);
        string move, categoria, tipo, temp;
        int poder;
        float precisao;
        bool fisico = false;

        try {
            // Leitura dos campos separados por vírgulas
            getline(linha_stream, move, ',');
            getline(linha_stream, categoria, ',');

            // Determina se o ataque é físico ou especial
            fisico = (categoria == "fisico");

            // Converte a string para inteiro (poder)
            getline(linha_stream, temp, ',');
            poder = stoi(temp);

            // Converte a string para float (precisão)
            getline(linha_stream, temp, ',');
            precisao = stof(temp);

            // Leitura do tipo
            getline(linha_stream, tipo, ',');

            // Adiciona o ataque ao vetor
            ataques.emplace_back(move, fisico, poder, precisao, tipo);
        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão na linha: " << linha << endl;
            cerr << "Detalhes: " << e.what() << endl;
        }
    }

    arquivo.close();
    cout << "Ataques carregados com sucesso." << endl;
}

int main() {
    Jogo jogo;

    // Teste 1: Carregar Pokémons
    cout << "Teste 1: Carregar Pokémons" << endl;
    jogo.carregarPokemons();  // Deve carregar os dados do arquivo e exibir uma mensagem de sucesso
    cout << "-------------------------------------\n";

/* 
    // Teste 2: Carregar Ataques
    cout << "Teste 2: Carregar Ataques" << endl;
    jogo.carregarAtaques();   // Deve carregar os dados do arquivo e exibir uma mensagem de sucesso
    cout << "-------------------------------------\n";

    // Teste 3: Ajustar Dificuldade
    cout << "Teste 3: Ajustar Dificuldade" << endl;
    jogo.ajustarDificuldade();  // Deve permitir ao usuário definir a dificuldade e confirmar o ajuste
    cout << "-------------------------------------\n";

    // Teste 4: Selecionar Jogador
    cout << "Teste 4: Selecionar Jogador" << endl;
    auto jogador = jogo.selecionarJogador();  // Deve permitir ao usuário escolher ou criar um jogador
    cout << "Jogador selecionado: " << jogador.getNome() << "\n";
    cout << "-------------------------------------\n";

    // Teste 5: Exibir Ranking
    cout << "Teste 5: Exibir Ranking" << endl;
    jogo.exibirRanking();  // Deve exibir o ranking dos jogadores (ainda pode estar vazio)
    cout << "-------------------------------------\n";

    // Teste 6: Salvar Dados
    cout << "Teste 6: Salvar Dados" << endl;
    jogo.salvarDados();  // Deve exibir uma mensagem de que os dados foram salvos
    cout << "-------------------------------------\n";

    // Teste 7: Iniciar Batalha
    cout << "Teste 7: Iniciar Batalha" << endl;
    jogo.iniciarBatalha();  // Deve iniciar uma batalha entre o jogador e a CPU
    cout << "-------------------------------------\n";

    // Teste 8: Mostrar Menu
    cout << "Teste 8: Mostrar Menu" << endl;
    jogo.mostrarMenu();  // Exibe o menu principal e permite escolher opções como em um fluxo de jogo normal
    cout << "-------------------------------------\n";
    
*/
    return 0;
}

