#ifndef PREDICADO_HPP
#define PREDICADO_HPP

#include <iostream>
#include <string>

class Predicado {
private: 

    std::string atributo;
    std::string operador;
    void* valor;
    std::string tipo;

public:
    
    Predicado* proximo;    

    Predicado(const std::string& atributo, const std::string& operador, void* valor, const std::string& t);
    ~Predicado();
    
    // Retorna os valores
    std::string getAtributo() const;
    std::string getOperador() const;
    std::string getValor() const;
    void* getValorFinal() const;
    std::string getTipo() const;

};

#endif