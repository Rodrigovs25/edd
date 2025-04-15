#include "predicado.hpp"

Predicado::Predicado(const std::string& atributo, const std::string& operador, void* valor, const std::string& t) 
    : atributo(atributo), operador(operador), valor(valor), tipo(t), proximo(nullptr) {}

Predicado::~Predicado() {
    if (tipo == "int") delete static_cast<int*>(valor);
    else if (tipo == "float") delete static_cast<float*>(valor);
    else if (tipo == "string") delete static_cast<std::string*>(valor);
}

std::string Predicado::getAtributo() const { return atributo; }
std::string Predicado::getOperador() const { return operador; }
std::string Predicado::getValor() const {
    if (tipo == "int") return std::to_string(*static_cast<int*>(valor));
    if (tipo == "float") return std::to_string(*static_cast<float*>(valor));
    if (tipo == "string") return *static_cast<std::string*>(valor);
    return "";
}
void* Predicado::getValorFinal() const { return valor; }
std::string Predicado::getTipo() const { return tipo; }
