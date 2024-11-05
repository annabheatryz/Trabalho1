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

// Atualizar a pontuação com base na dificuldade da partida
void Jogador::adicionarPontuacao(int pontos) {
    pontuacao += pontos;
}

void Jogador::registrarResultado(bool vitoria) {
    int pontos = 0;

    if (dificuldade == Dificuldade::DIFICIL) {
        pontos = 30;
    } else if (dificuldade == Dificuldade::MEDIO) {
        pontos = 20;
    } else if (dificuldade == Dificuldade::FACIL) {
        pontos = 10;
    }

    if (vitoria) {
        adicionarPontuacao(pontos);
        adicionarVitoria();
    } else {
        adicionarDerrota();
    }

    // Salva o jogador no arquivo após o resultado
    salvarJogador();
}

void Jogador::salvarJogador() {
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
            linha = nome + " " + to_string(vitorias) + " " + to_string(derrotas) + " " + to_string(pontuacao);
        }
        linhas.push_back(linha);
    }

    // Se o jogador não foi encontrado, adiciona ao final
    if (!jogadorEncontrado) {
        linha = nome + " " + to_string(vitorias) + " " + to_string(derrotas) + " " + to_string(pontuacao);
        linhas.push_back(linha);
    }

    // Fecha e reabre o arquivo para sobrescrever
    arquivo.close();
    ofstream arquivoSaida("ranking.txt");
    for (const auto& l : linhas) {
        arquivoSaida << l << endl;
    }
    arquivoSaida.close();
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

void Jogador::adicionarVitoria() {
    vitorias++;
}

void Jogador::adicionarDerrota() {
    derrotas++;
}