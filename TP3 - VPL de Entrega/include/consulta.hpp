#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>
#include "funcao.hpp"

class Consulta {
    private:
        int numeroVoos;
        std::string tiagrama;
        std::string filtro; 
    
    public:
        // Construtor
        Consulta();
        Consulta(int, std::string, std::string);

        int getNumeroVoos();
        std::string getTiagrama();
        std::string getFiltro();

        // Função para imprimir a consulta
        friend std::ostream& operator<<(std::ostream& os, const Consulta& consulta);
};

#endif