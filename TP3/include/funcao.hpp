#ifndef FUNCAO_HPP
#define FUNCAO_HPP

#include <string>

// Retorna o número de dias em um mês específico
int diasNoMes(int mes, int ano);

// Converter um std::string para char* para ler uma string
char* converterStrChar(const std::string& str);

// Converte uma data no formato ISO 8601 em segundos desde a referência
int converterSegundos(const std::string& data);

// Estabelece a duração do voo
int setDuracao(const std::string& partida, const std::string& chegada);

// Troca elemento
void troca(int& a, int& b);

// Ordenação de vetores
void quickSort(int* vetor, int inicio, int fim);
void ordenarVetor(int* vetor, int tamanho);

// Une dois vetores no vetor a
void unirVetores(int*& a, int& tamanhoA, int* b, int tamanhoB);

#endif 
