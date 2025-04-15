#include "armazenaVetores.hpp"

Vetor::Vetor(int* d, int t) : tamanho(t) {
    dados = new int[tamanho];
    int i;
    for(i = 0; i < tamanho; i++) {
        dados[i] = d[i];
    }
}

Vetor::~Vetor() {
    delete[] dados;
}

ArmazenaVetores::ArmazenaVetores() : count(0), capacidade(2) {
    Vetores = new Vetor*[capacidade];
}

ArmazenaVetores::~ArmazenaVetores() {
    int i;
    for(i = 0; i < count; i++) {
        delete Vetores[i];
    }
    delete[] Vetores;
}

void ArmazenaVetores::redefinir() {
    capacidade *= 2;
    Vetor** novoVetores = new Vetor*[capacidade];
    int i;
    for(i = 0; i < count; i++) {
        novoVetores[i] = Vetores[i];
    }
    delete[] Vetores;
    Vetores = novoVetores;
}

void ArmazenaVetores::adicionarVetor(int* vetor, int tamanho) {
    if (count == capacidade) {
        redefinir();
    }
    Vetores[count++] = new Vetor(vetor, tamanho);
}

int* ArmazenaVetores::encotrarIndicesComum(int& tamanhoVetorComum) {
    if (count == 0) {
        tamanhoVetorComum = 0;
        return nullptr;
    }

    int* vet = new int[Vetores[0]->tamanho];
    int vetCount = 0;
    int i, j, k;
    for(i = 0; i < Vetores[0]->tamanho; i++) {
        int valor = Vetores[0]->dados[i];
        bool encontradoEmTodos = true;

        for(j = 1; j < count && encontradoEmTodos; j++) {
            bool encontrou = false;
            for(k = 0; k < Vetores[j]->tamanho; k++) {
                if (Vetores[j]->dados[k] == valor) {
                    encontrou = true;
                    break;
                }
            }
            if (!encontrou) {
                encontradoEmTodos = false;
            }
        }

        if (encontradoEmTodos) {
            vet[vetCount++] = valor;
        }
    }
    tamanhoVetorComum = vetCount;
    return vet;
}
