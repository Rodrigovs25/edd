#include "consulta.hpp"
#include <iostream>

Consulta::Consulta(){
    this->numeroVoos = 0;
    this->tiagrama = "";
    this->filtro = "";
}

Consulta::Consulta(int numeroVoos, std::string tiagrama, std::string filtro)
    : numeroVoos(numeroVoos), tiagrama(tiagrama), filtro(filtro) {}

int Consulta::getNumeroVoos(){
    return this->numeroVoos;
}

std::string Consulta::getTiagrama(){
    return this->tiagrama;
}

std::string Consulta::getFiltro(){
    return this->filtro;
}

std::ostream& operator<<(std::ostream& os, const Consulta& consulta) {
    os << consulta.numeroVoos << " " << consulta.tiagrama
       << " " << consulta.filtro;
    return os;
}
