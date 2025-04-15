#ifndef VOO_HPP
#define VOO_HPP

#include <iostream>
#include <string>

class Voo {
    private:
        std::string origem;
        std::string destino;
        float preco;
        int assentos;
        std::string partida;  
        std::string chegada;    
        int paradas;
        int duracao;   // chegada - partida

        // Ordenação do Voos
        bool compararVoos(const Voo& f1, const Voo& f2, const std::string& tiagrama);
        int partition(Voo* voos, int inicio, int fim, const std::string& tiagrama);
        void quickSort(Voo* voos, int inicio, int fim, const std::string& tiagrama);
    
    public:
        // Construtor
        Voo();
        Voo(std::string, std::string, float, int, std::string, std::string, int, int);

        // Gets
        float getPreco() const;
        int getParadas() const;
        int getDuracao() const;

        // Ordenação do Voos
        void ordenarVoos(int numeroVoos, const std::string& tiagrama);

        // Função para imprimir
        friend std::ostream& operator<<(std::ostream& os, const Voo& voo);
};

#endif