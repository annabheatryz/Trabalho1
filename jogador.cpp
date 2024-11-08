#include "jogador.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Construtor
Jogador::Jogador(string nome) : nome(nome), vitorias(0), derrotas(0), pontuacao(0) {}

Jogador::Jogador(string nome, int vitorias, int derrotas, int pontuacao) 
    : nome(nome), vitorias(vitorias), derrotas(derrotas), pontuacao(pontuacao) {}

// Getters
string Jogador::getNome() const { return nome; }
int Jogador::getVitorias() const { return vitorias; }
int Jogador::getDerrotas() const { return derrotas; }
int Jogador::getPontuacao() const { return pontuacao; }

// Setters
void Jogador::setNome(string nome) { this->nome = nome; }
void Jogador::setVitorias(int v) { vitorias = v; }
void Jogador::setDerrotas(int d) { derrotas = d; }
void Jogador::setPontuacao(int p) { pontuacao = p; }

void Jogador::registrarResultado(Jogador& jogador, bool vitoria, Dificuldade dificuldade) {
    int pontos = 0;

    // Define pontuação baseada na dificuldade apenas se for uma vitória
    if (vitoria) {
        switch (dificuldade) {
            case Dificuldade::DIFICIL:
                pontos += 30;
                break;
            case Dificuldade::MEDIO:
                pontos += 20;
                break;
            case Dificuldade::FACIL:
                pontos += 10;
                break;
        }
        cout << "Pontos ganhos: " << pontos << std::endl;

        // Atualiza pontuação e vitórias apenas se o jogador vencer
        setPontuacao(getPontuacao() + pontos);
        setVitorias(getVitorias() + 1);
    } else {
        // Apenas incrementa derrotas em caso de perda
        setDerrotas(getDerrotas() + 1);
    }

    // Abrindo arquivo e lendo linhas para atualizar ou adicionar o jogador
    fstream arquivo("ranking.txt", ios::in | ios::out | ios::ate);
    vector<string> linhas;
    string linha;
    bool jogadorEncontrado = false;

    // Reposiciona para o início do arquivo para leitura
    arquivo.seekg(0, ios::beg);

    // Lê todas as linhas do arquivo
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        string nomeArquivo;
        int vit, der, pts;

        // Lê os dados de cada linha
        iss >> nomeArquivo >> vit >> der >> pts;

        // Se o jogador já está no arquivo, atualiza seus dados
        if (nomeArquivo == nome) {
            jogadorEncontrado = true;
            linha = nome + " " + to_string(getVitorias()) + " " + to_string(getDerrotas()) + " " + to_string(getPontuacao());
        }
        linhas.push_back(linha);
    }

    // Se o jogador não foi encontrado, adiciona ao final
    if (!jogadorEncontrado) {
        linhas.push_back(nome + " " + to_string(getVitorias()) + " " + to_string(getDerrotas()) + " " + to_string(getPontuacao()));
    }

    // Fecha o arquivo e reabre para sobrescrever
    arquivo.close();
    ofstream arquivoSaida("ranking.txt");
    for (const auto& l : linhas) {
        arquivoSaida << l << endl;
    }
    arquivoSaida.close();

    // Exibindo a pontuação atualizada para verificação
    cout << "Pontuação atualizada: " << pontuacao << " pontos.\n";
}

void Jogador::salvarRanking() {
    ofstream arquivo("ranking.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << nome << " - Vitórias: " << vitorias 
                << " - Derrotas: " << derrotas 
                << " - Pontuação: " << pontuacao << "\n";
        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo de ranking.\n";
    }
}