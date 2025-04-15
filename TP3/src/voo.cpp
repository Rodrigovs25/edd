#include "voo.hpp"

Voo::Voo(){
    this->origem = "";
    this->destino = "";
    this->preco = 0;
    this->assentos = 0;
    this->partida = "";  
    this->chegada = "";    
    this->paradas = 0;
    this->duracao = 0;   

}

// Construtor 
Voo::Voo(std::string origem, std::string destino, float preco, int assentos,
               std::string partida, std::string chegada, int paradas, int duracao)
    : origem(origem), destino(destino), preco(preco), assentos(assentos),
      partida(partida), chegada(chegada), paradas(paradas), duracao(duracao) {}

float Voo::getPreco() const {
    return this->preco;
}

int Voo::getParadas() const {
    return this->paradas;
}

int Voo::getDuracao() const {
    return this->duracao;
}

// Função de comparação personalizada
bool Voo::compararVoos(const Voo& f1, const Voo& f2, const std::string& tiagrama) {
    for (char c : tiagrama) {
        if (c == 'p') {  // Comparar preço
            if (f1.getPreco() != f2.getPreco())
                return f1.getPreco() < f2.getPreco();
        } else if (c == 'd') {  // Comparar duração
            if (f1.getDuracao() != f2.getDuracao())
                return f1.getDuracao() < f2.getDuracao();
        } else if (c == 's') {  // Comparar número de paradas
            if (f1.getParadas() != f2.getParadas())
                return f1.getParadas() < f2.getParadas();
        }
    }
    return false;
}

// Método auxiliar do QuickSort: Partição
int Voo::partition(Voo* voos, int inicio, int fim, const std::string& tiagrama) {
    Voo pivo = voos[fim]; // Escolhe o último elemento como pivô
    int i = inicio - 1;
    int j;
    for(j = inicio; j < fim; j++) {
        if (compararVoos(voos[j], pivo, tiagrama)) {
            i++;
            Voo aux = voos[i];
            voos[i] = voos[j];
            voos[j] = aux;
        }
    }
    Voo aux = voos[i + 1];
    voos[i + 1] = voos[fim];
    voos[fim] = aux;
    return i + 1;
}

// Implementação do QuickSort
void Voo::quickSort(Voo* voos, int inicio, int fim, const std::string& tiagrama) {
    if (inicio < fim) {
        int par = partition(voos, inicio, fim, tiagrama);
        quickSort(voos, inicio, par - 1, tiagrama);
        quickSort(voos, par + 1, fim, tiagrama);
    }
}

// Método público para ordenação
void Voo::ordenarVoos(int numeroVoos, const std::string& tiagrama) {
    quickSort(this, 0, numeroVoos - 1, tiagrama);
}

std::ostream& operator<<(std::ostream& os, const Voo& voo) {
    os << voo.origem 
       << " " << voo.destino
       << " " << voo.preco
       << " " << voo.assentos
       << " " << voo.partida
       << " " << voo.chegada
       << " " << voo.paradas;
       //<< " " << voo.duracao;
    return os;
}
