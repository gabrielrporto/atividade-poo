# Nome do executável
TARGET = loja_de_roupas

# Compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Diretório de código fonte
SRCDIR = src

# Diretório de objetos
OBJDIR = obj

# Arquivos fonte
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

# Objetos correspondentes aos arquivos fonte
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Regra para o alvo principal (o executável)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Regra de compilação dos objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	if not exist $(@D) mkdir $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar os arquivos objetos e o executável
clean:
	del /S /Q $(OBJDIR) $(TARGET)

# Indicar que 'clean' não é um arquivo alvo
.PHONY: clean
