#ifndef EXPRESSAO_HPP
#define EXPRESSAO_HPP

#include <iostream>
#include <string>
#include "predicado.hpp"

// Armazenar os predicados de cada expressão lógica
class Expressao {
private:
    Predicado* cabeca;
    int tamanho;

    int stringInt(const std::string& val);
    float stringFloat(const std::string& val);

public:
    Expressao();
    ~Expressao();

    void adicionarPredicado(const std::string& atributo, const std::string& operador, const std::string& val);
    bool vazio() const;
    Predicado* remover();
    int getTamanho();
};

// Processar as expressoes dividinod em predicados
void processarExpressao(const std::string& expr, Expressao& expressao);

#endif 
