#include "jogador.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Jogador::Jogador(string nome) : nome(nome), vitorias(0), derrotas(0), pontuacao(0) {}

Jogador::Jogador(string nome, int vitorias, int derrotas, int pontuacao) 
    : nome(nome), vitorias(vitorias), derrotas(derrotas), pontuacao(pontuacao) {}

string Jogador::getNome() const { return nome; }
int Jogador::getVitorias() const { return vitorias; }
int Jogador::getDerrotas() const { return derrotas; }
int Jogador::getPontuacao() const { return pontuacao; }

void Jogador::setNome(string nome) { this->nome = nome; }
void Jogador::setVitorias(int v) { vitorias = v; }
void Jogador::setDerrotas(int d) { derrotas = d; }
void Jogador::setPontuacao(int p) { pontuacao = p; }

void Jogador::adicionarPontuacao(int pontos) {
    pontuacao += pontos;
}

void Jogador::carregarDadosDoRanking() {
    fstream arquivo("ranking.txt", ios::in);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir arquivo de ranking para leitura." << endl;
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        string nomeArquivo;
        int vit, der, pts;

        iss >> nomeArquivo >> vit >> der >> pts;
        if (nomeArquivo == nome) {
            vitorias = vit;
            derrotas = der;
            pontuacao = pts;
            break;
        }
    }
    arquivo.close();
}

void Jogador::registrarResultado(Jogador& jogador, bool vitoria, Dificuldade dificuldade) {
    jogador.carregarDadosDoRanking();

    int pontos = 0;

    if (dificuldade == Dificuldade::FACIL) {
        pontos = 10;
    } else if (dificuldade == Dificuldade::MEDIO) {
        pontos = 20;
    } else if (dificuldade == Dificuldade::DIFICIL) {
        pontos = 30;
    }

    int novasVitorias = jogador.getVitorias();
    int novasDerrotas = jogador.getDerrotas();
    int novaPontuacao = jogador.getPontuacao();

    if (vitoria) {
        cout << "Pontos ganhos: " << pontos << std::endl;
        novaPontuacao += pontos;
        novasVitorias++;
    } else {
        novasDerrotas++;
    }

    jogador.setPontuacao(novaPontuacao);
    jogador.setVitorias(novasVitorias);
    jogador.setDerrotas(novasDerrotas);

    jogador.salvarRanking();
}

void Jogador::salvarRanking() {
    fstream arquivo("ranking.txt", ios::in);
    vector<string> linhas;
    string linha;
    bool jogadorEncontrado = false;

    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        string nomeArquivo;
        int vit, der, pts;

        iss >> nomeArquivo >> vit >> der >> pts;

        if (nomeArquivo == nome) {
            jogadorEncontrado = true;
            linha = nome + " " + to_string(getVitorias()) + " " + to_string(getDerrotas()) + " " + to_string(getPontuacao());
        }
        linhas.push_back(linha);
    }

    if (!jogadorEncontrado) {
        linhas.push_back(nome + " " + to_string(getVitorias()) + " " + to_string(getDerrotas()) + " " + to_string(getPontuacao()));
    }

    arquivo.close();
    ofstream arquivoSaida("ranking.txt");

    for (const auto& l : linhas) {
        arquivoSaida << l << endl;
    }

    arquivoSaida.close();
    cout << "Pontuação atualizada: " << pontuacao << " pontos.\n";
}
