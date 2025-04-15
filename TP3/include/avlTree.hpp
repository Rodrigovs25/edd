#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <string>

template <typename T>
class AvlTree {
private:
    struct Node {
        T chave;                // Chave (genérica): int, float, str
        int* indices;           // Lista de atributos (vetor dinâmico)
        int tamanhoIndices;     // Tamanho atual da lista de atributos
        int capacidadeIndices;  // Capacidade máxima da lista
        int altura;             // Altura do nó
        Node* esquerda;         // Ponteiro para o nó esquerdo
        Node* direita;          // Ponteiro para o nó direito

        Node(T k, int indice) : chave(k), altura(1), esquerda(nullptr), direita(nullptr) {
            tamanhoIndices = 1;
            capacidadeIndices = 10; // Capacidade inicial
            indices = new int[capacidadeIndices];
            indices[0] = indice;
        }

        ~Node() {
            delete[] indices;
        }
        
        // Adicionar o indice no vetor
        void adicionarIndice(int indice) {
            int i;
            if (tamanhoIndices == capacidadeIndices) {
                capacidadeIndices *= 2; // Dobra a capacidade
                int* novoIndices = new int[capacidadeIndices];
                for(i = 0; i < tamanhoIndices; ++i) {
                    novoIndices[i] = indices[i];
                }
                delete[] indices;
                indices = novoIndices;
            }
            // Insere o atributo de forma ordenada
            for(i = tamanhoIndices - 1; i >= 0 && indices[i] > indice; --i) {
                indices[i + 1] = indices[i];
            }
            indices[i + 1] = indice;
            tamanhoIndices++;
        }
    };

    Node* raiz; // Raiz

    void limpar(Node* node);

    int getAltura(Node* node);
    int getBalanceamento(Node* node);
    void atualizarAltura(Node* node);

    Node* rotacionarEsquerda(Node* x);
    Node* rotacionarDireita(Node* y);

    Node* inserir(Node* node, T chave, int indice);
    Node* procurar(Node* raiz, const T& chave);

    int contarChavesRec(Node* node, T valor, const std::string& op);
    void coletarChavesRec(Node* node, T valor, const std::string& op, int maxTamanho, T* vetor, int& vetorTamanho);

public:
    AvlTree() : raiz(nullptr) {}
    ~AvlTree() { limpar(raiz); }

    void inserir(T chave, int indice);
    // Retorna o array de atributos e define o tamanho por referência
    int* procurar(T chave, int& tamanho); 

    // Função contar as chaves que atendem ao operador
    int contarChaves(T valor, const std::string& op);

    // Função para encontrar as chaves que satifaz o operador 
    T* coletarChaves(T valor, const std::string& op, int maxTamanho);
};

#endif
