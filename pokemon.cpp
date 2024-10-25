#include "pokemon.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

// Construtor padrão
Pokemon::Pokemon() : nome(""), tipo1(""), tipo2(""), hp(0), nivel(0), ataque(0), defesa(0), velocidade(0), ataque_especial(0), defesa_especial(0) {}

// Construtor com parâmetros
Pokemon::Pokemon(const string& n, const string& tp1, const string& tp2, int hp, int nvl, int atq, int dfs, int v, int atq_especial, int dfs_especial) : nome(n), tipo1(tp1), tipo2(tp2), hp(hp), nivel(nvl), ataque(atq), defesa(dfs), velocidade(v), ataque_especial(atq_especial), defesa_especial(dfs_especial) {}

// Getters
string Pokemon::getNome() const {return nome;}
string Pokemon::getTipo1() const {return tipo1;}
string Pokemon::getTipo2() const {return tipo2;}
int Pokemon::getHP() const {return hp;}
int Pokemon::getNivel() const {return nivel;}
int Pokemon::getDefesa() const {return defesa;}
int Pokemon::getVelocidade() const {return velocidade;}
int Pokemon::getAtaqueEspecial() const {return ataque_especial;}
int Pokemon::getDefesaEspecial() const {return defesa_especial;}

// Setters
void Pokemon::setHP(int hp) {this -> hp = hp;}
void Pokemon::setNivel(int nvl) {nivel = nvl;}
void Pokemon::setAtaque(int atq) {ataque = atq;}
void Pokemon::setDefesa(int dfs) {defesa = dfs;}
void Pokemon::setVelocidade(int v) {velocidade = v;}
void Pokemon::setAtaqueEspecial(int atq_especial) {ataque_especial = atq_especial;}
void Pokemon::setDefesaEspecial(int dfs_especial) {defesa_especial = dfs_especial;}

void Pokemon::sortearAtaques(const vector<Ataque>& vetor_ataques, size_t qtd_ataques) {
    ataques.clear(); //Limpa os ataques antes
    vector<Ataque> sorteados;
    vector<bool> ataques_selecionados(vetor_ataques.size(), false);

    // Define a semente para gerar números aleatórios
    srand(time(0));
    int tentativas = 0;  // Contador para tentativas de ataques compatíveis
    const int max_tentativas = 100; // Limite de tentativas para evitar loops infinitos

    while (sorteados.size() < qtd_ataques && tentativas < max_tentativas) {
        // Gera um índice aleatório
        int indice = rand() % vetor_ataques.size();
        const Ataque& atq_sorteado = vetor_ataques[indice];

        // Verifica se o ataque já foi sorteado
        if (!ataques_selecionados[indice]) {
            // Verifica se o ataque sorteado corresponde ao tipo "Normal", tipo1 ou tipo2 do Pokémon
            if (atq_sorteado.getTipo() == "Normal" || atq_sorteado.getTipo() == tipo1 || atq_sorteado.getTipo() == tipo2) {
                // Adiciona o ataque ao vetor de sorteados
                sorteados.push_back(vetor_ataques[indice]);

                // Marca o ataque como sorteado
                ataques_selecionados[indice] = true;
            }
        }
        tentativas++;
    }
     // Se ainda não completou os 4 ataques, sorteia mais ataques, independente do tipo
    while(sorteados.size() < qtd_ataques){
        int indice = rand() % vetor_ataques.size();
        if(!ataques_selecionados[indice]);
            //Adicionar ataque ao vetor de sorteados
            sorteados.push_back(vetor_ataques[indice]);

            ataques_selecionados[indice] = true;
    }

    // Atualiza o vetor de ataques do Pokémon com os sorteados
    ataques = sorteados;
}

void Pokemon::reduzirHP(int dano) {
    hp -= dano;  // Subtrai o dano do HP atual
    if (hp < 0){
        hp = 0;  // HP não pode ser negativo
        cout << getNome() << " recebeu " << dano << " de dano! HP restante: " << getHP() << endl;
    }
}

bool Pokemon::estaDerrotado() const {
    return hp <=0;
}

void Pokemon::exibirAtaques() const {
    cout << "Ataques do Pokémon " << nome << ":\n";
    for (size_t i = 0; i < ataques.size(); ++i) {
        cout << i + 1 << ". " << ataques[i].getMove() << " (Tipo: " << ataques[i].getTipo()
             << ", Poder: " << ataques[i].getPoder() << ", Físico: " << (ataques[i].isFisico() ? "Sim" : "Não") << ")\n";
    }
}

int Pokemon::calcularDano(const Ataque& ataque, const Pokemon& defensor) {
    // Fórmula de dano base: ((2 * nível / 5 + 2) * poder * ataque / defesa) / 50 + 2
    int danoBase = (((2 * nivel / 5 + 2) * ataque.getPoder() * ataque_especial) / defensor.getDefesaEspecial()) / 50 + 2;

    // Multiplicadores de tipo
    float multiplicador = calcularMultiplicador(ataque, defensor);

    // Fator aleatório entre 0.85 e 1.0
    float random = (rand() % 16 + 85) / 100.0;
    
    // Dano final
    int danoFinal = static_cast<int>(danoBase * multiplicador * random);

    // Exibir o dano calculado
    cout << nome << " usou " << ataque.getMove() << " e causou " << danoFinal << " de dano!\n";

    return danoFinal;
}


// Função para calcular multiplicadores (vantagem de tipos)
float Pokemon::calcularMultiplicador(const Ataque& ataque, const Pokemon& defensor) {
    float multiplicador = 1.0f;

    // Exemplo de vantagem/desvantagem de tipos
    if (ataque.getTipo() == "Fogo" && (defensor.getTipo1() == "Grama" || defensor.getTipo2() == "Grama")) {
        multiplicador = 2.0f;  // Super eficaz
    } else if (ataque.getTipo() == "Fogo" && (defensor.getTipo1() == "Água" || defensor.getTipo2() == "Água")) {
        multiplicador = 0.5f;  // Não muito eficaz
    }

    // Exibir o multiplicador
    cout << "Multiplicador de tipo: " << multiplicador << "\n";
    return multiplicador;
}


int main() {
    // Criar uma lista de ataques disponíveis (pode vir de um arquivo, por exemplo)
    vector<Ataque> listaAtaques = {
        Ataque("Lança-chamas", false, 90, 1.0, "Fogo"),  // Ataque especial
        Ataque("Ataque de Asa", true, 60, 1.0, "Voador"),  // Ataque físico
        Ataque("Investida", true, 40, 1.0, "Normal"),  // Ataque físico
        Ataque("Raio Solar", false, 120, 0.75, "Grama"),  // Ataque especial
        Ataque("Terremoto", true, 100, 1.0, "Terrestre")  // Ataque físico
    };

    // Mostrar lista de ataques disponíveis
    cout << "Ataques disponíveis:\n";
    for (const auto& ataque : listaAtaques) {
        cout << "- " << ataque.getMove() << " (Tipo: " << ataque.getTipo()
             << ", Poder: " << ataque.getPoder() << ", Físico: " << (ataque.isFisico() ? "Sim" : "Não") << ")\n";
    }

    // Criar um Pokémon
    cout << "\nCriando o Pokémon Charizard...\n";
    Pokemon charizard("Charizard", "Fogo", "Voador", 180, 50, 180, 84, 78, 109, 85);

    // Mostrar status do Pokémon antes do sorteio de ataques
    cout << "Status do Pokémon Charizard:\n";
    cout << "Nome: " << charizard.getNome() << "\n"
         << "Tipo 1: " << charizard.getTipo1() << "\n"
         << "Tipo 2: " << charizard.getTipo2() << "\n"
         << "HP: " << charizard.getHP() << "\n";

    // Sortear ataques para o Charizard
    cout << "\nSorteando ataques para Charizard...\n";
    charizard.sortearAtaques(listaAtaques, 4);

    // Mostrar os ataques sorteados
    cout << "\nAtaques sorteados para Charizard:\n";
    charizard.exibirAtaques();  // Método para exibir os ataques sorteados

    // Criar outro Pokémon para a batalha (Bulbasaur)
    cout << "\nCriando o Pokémon Bulbasaur...\n";
    Pokemon bulbasaur("Bulbasaur", "Grama", "Venenoso", 150, 50, 49, 49, 45, 65, 65);

    // Mostrar status do Pokémon defensor
    cout << "Status do Pokémon Bulbasaur:\n";
    cout << "Nome: " << bulbasaur.getNome() << "\n"
         << "Tipo 1: " << bulbasaur.getTipo1() << "\n"
         << "Tipo 2: " << bulbasaur.getTipo2() << "\n"
         << "HP: " << bulbasaur.getHP() << "\n";

    // Simular um ataque (Charizard usa "Lança-chamas" contra Bulbasaur)
    cout << "\nCharizard ataca Bulbasaur com Lança-chamas!\n";
    charizard.calcularDano(listaAtaques[0], bulbasaur);

    cout << "\nPrograma executado com sucesso!\n";

    return 0;
}
