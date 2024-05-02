#include <iostream>
#include <string>
#include <vector>


using std::string;
using std::vector;
using std::cout;
using std::endl;


class Marca {
    string nome;
public:
    // Construtor
    Marca(const string& n) : nome(n) {}

    // Não é necessário liberar nenhum recurso alocado, pois a classe Marca não aloca nenhum recurso dinamicamente.
    ~Marca() {}

    // Getter e setter para o nome da marca
    string get_nome() const { return nome; }
    void set_nome(const string& n) { nome = n; }
};


class Roupa {
    string tipo;
    vector<Marca*> marcas;
    string tamanho;
public:
    // Construtor
    Roupa(const string& tip, const string& tam) : tipo(tip), tamanho(tam) {}

    // Destrutor virtual, pois Roupa é uma classe base herdada por outras classes
    virtual ~Roupa() {
        for (auto marca : marcas) {
            delete marca;
        }
    }

    // Getters e setters para tipo, tamanho e marcas
    string get_tipo() const { return tipo; }
    string get_tamanho() const { return tamanho; }
    vector<Marca*> get_marcas() const { return marcas; }
    void set_tipo(const string& tip) { tipo = tip; }

    // Método virtual puro para transformar a classe em abstrata
    virtual void set_tamanho(const string& tam) = 0;

    // Sobrecarga de operadores para adicionar e remover marcas
    void operator+(Marca* marca) { marcas.push_back(marca); }
    void operator-(Marca* marca) {
        for (auto it = marcas.begin(); it != marcas.end(); it++) { // Busca a marca que se deseja remover
            if (*it == marca) {
                marcas.erase(it);
                break;
            }
        }
    }
};


class RoupaAdulta : public Roupa {
    string tipo_tecido;
public:
    // Construtor
    RoupaAdulta(const string& tip, const string& tam, const string& tip_tecido)
        : Roupa(tip, tam), tipo_tecido(tip_tecido) {}

    // Getter e setter para o tipo de tecido
    string get_tipo_tecido() const { return tipo_tecido; }
    void set_tipo_tecido(const string& tip) { tipo_tecido = tip; }

    // Implementação do metodo virtual puro
    void set_tamanho(const string& tam) { set_tamanho(tam); }
};


class RoupaInfantil : public Roupa {
    string faixa_etaria;

public:
    // Construtor
    RoupaInfantil(const string& tip, const string& tam, const string& faix_etaria)
        : Roupa(tip, tam), faixa_etaria(faix_etaria) {}

    // Getter e setter para a faixa etária
    string get_faixa_etaria() const { return faixa_etaria; }
    void set_faixa_etaria(const string& faix_etaria) { faixa_etaria = faix_etaria; }

    // Implementação do metodo virtual puro
    void set_tamanho(const string& tam) { set_tamanho(tam); }
};


class Loja {
    vector<Roupa*> roupas;
public:
    // Construtor padrão
    Loja() {}
    // Destrutor
    ~Loja() {
        for (auto roupa : roupas) {
            delete roupa;
        }
    }

    // Método para adicionar uma roupa à loja
    void adicionar_roupa(Roupa* r) { roupas.push_back(r); }

    // Método para remover uma roupa da loja
    void remover_roupa(Roupa* r) {
        for (auto it = roupas.begin(); it != roupas.end(); it++) {
            if (*it == r) {
                roupas.erase(it);
                break;
            }
        }
    }

    // Sobrecarga de operadores para adicionar e remover roupas
    void operator+(Roupa* r) { adicionar_roupa(r); }
    void operator-(Roupa* r) { remover_roupa(r); }

    // Getter para a lista de roupas da loja
    vector<Roupa*> get_roupas() const { return roupas; }
};

int main() {
    Loja loja;

    // Exemplo de utilização
    Marca* adidas = new Marca("Adidas");
    Marca* nike = new Marca("Nike");

    RoupaAdulta* camiseta_adidas = new RoupaAdulta("Camiseta", "M", "Algodão");
    camiseta_adidas->operator+(adidas);

    RoupaInfantil* camiseta_nike = new RoupaInfantil("Camiseta", "2", "0-2 anos");
    camiseta_nike->operator+(nike);

    loja + camiseta_adidas;
    loja + camiseta_nike;

    cout << "Roupas na loja:" << endl;
    for (auto roupa : loja.get_roupas()) {
        cout << "Tipo: " << roupa->get_tipo() << ", Tamanho: " << roupa->get_tamanho() << endl;
        auto marcas = roupa->get_marcas();
        cout << "Marcas:";
        for (auto marca : marcas) {
            cout << " " << marca->get_nome();
        }
        cout << endl;
    }

    return 0;
}