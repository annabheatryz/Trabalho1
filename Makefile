# Variáveis de compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Diretivas de arquivos
TARGET = main
OBJECTS = main.o pokemon.o ataque.o jogo.o jogador.o  
HEADERS = pokemon.h ataque.h jogo.h jogador.h  

# Regra padrão
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Regras para gerar arquivos .o a partir dos .cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

pokemon.o: pokemon.cpp pokemon.h
	$(CXX) $(CXXFLAGS) -c pokemon.cpp

ataque.o: ataque.cpp ataque.h
	$(CXX) $(CXXFLAGS) -c ataque.cpp

jogo.o: jogo.cpp $(HEADERS)  
	$(CXX) $(CXXFLAGS) -c jogo.cpp

jogador.o: jogador.cpp jogador.h 
	$(CXX) $(CXXFLAGS) -c jogador.cpp

# Limpeza dos arquivos temporários
clean:
	rm -f $(TARGET) $(OBJECTS)

# Limpeza total, incluindo os arquivos de backup
cleanall: clean
	rm -f *~
