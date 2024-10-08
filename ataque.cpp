#include "ataque.h"
#include "pokemon.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// Construtor padrão
Ataque::Ataque() : move(""), categoria(""), poder(0), precisao(0.0), tipo("") {}

// Construtor com parâmetros
Ataque::Ataque(const string& mv, const string& c, int pw, float pc, const string& t)
    : move(mv), categoria(c), poder(pw), precisao(pc), tipo(t) {}

// Getters
string Ataque::getMove() const { return move; }
string Ataque::getCategoria() const { return categoria; }
string Ataque::getTipo() const { return tipo; }
int Ataque::getPoder() const { return poder; }
float Ataque::getPrecisao() const { return precisao; }

// Setters
void Ataque::setPoder(int pw) { poder = pw; }
void Ataque::setPrecisao(float pc) { precisao = pc; }

// Método para carregar ataques de um arquivo
vector<Ataque> Ataque::carregarAtaques(const string& nome_arquivo) {
    vector<Ataque> ataques;
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return ataques;  // Retorna o vetor vazio em caso de erro
    }

    string linha;
    // Ignora a primeira linha (cabeçalho)
    getline(arquivo, linha);

    // Variáveis temporárias para armazenar os dados lidos
    string move, categoria, tipo;
    int poder;
    float precisao;

    // Ler as demais linhas do CSV
    while (getline(arquivo, linha)) {
        stringstream linha_stream(linha);
        string temp;

        try {
            // Leitura dos campos separados por vírgulas
            getline(linha_stream, move, ',');
            getline(linha_stream, categoria, ',');
            
            // Converte a string para inteiro (poder)
            getline(linha_stream, temp, ',');
            poder = stoi(temp);

            // Converte a string para float (precisão)
            getline(linha_stream, temp, ',');
            precisao = stof(temp);
            
            // Leitura do tipo
            getline(linha_stream, tipo, ',');

            // Adiciona o ataque ao vetor
            ataques.emplace_back(move, categoria, poder, precisao, tipo);

        } catch (const invalid_argument& e) {
            cerr << "Erro de conversão na linha: " << linha << endl;
            cerr << "Detalhes: " << e.what() << endl;
        }
    }

    arquivo.close();
    return ataques;
}

vector<Ataque> Ataque::sortearAtaques(const vector<Ataque>& vetor_ataques, const Pokemon& pokemon, size_t qtd_ataques) {
    vector<Ataque> sorteados;
    // Controle para evitar repetições
    vector<bool> ataques_selecionados(vetor_ataques.size(), false);

    //  Define a semente para gerar números aleatórios
    srand(time(0));

    while (sorteados.size() < qtd_ataques) {
        // Gera um índice aleatório
        int indice = rand() % vetor_ataques.size();
        const Ataque& atq_sorteado = vetor_ataques[indice];

        // Verifica se o ataque já foi sorteado
        if (!ataques_selecionados[indice]) {

            // Verifica se o ataque sorteado corresponde ao tipo "Normal" OU tipo1 OU tipo2 do pokemon
            if (atq_sorteado.getTipo() == "Normal" || atq_sorteado.getTipo() == pokemon.getTipo1() || atq_sorteado.getTipo() == pokemon.getTipo2()) {
                // Adiciona o ataque ao vetor de sorteados
                sorteados.push_back(vetor_ataques[indice]);

                // Marca o ataque como sorteado
                ataques_selecionados[indice] = true;
            }
        }
    }

    return sorteados;
}
