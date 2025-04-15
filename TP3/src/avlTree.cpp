#include "avlTree.hpp"

// Limpa a árvore
template <typename T>
void AvlTree<T>::limpar(Node* node) {
    if (node) {
        limpar(node->esquerda);
        limpar(node->direita);
        delete node;
    }
    raiz = nullptr;
}

template <typename T>
int AvlTree<T>::getAltura(Node* node) {
    if (node) {
        return node->altura;
    }
    return 0;
}

template <typename T>
int AvlTree<T>::getBalanceamento(Node* node) {
    if(node){
        return getAltura(node->esquerda) - getAltura(node->direita);
    }
    return 0;
}

template <typename T>
void AvlTree<T>::atualizarAltura(Node* node) {
    if (!node) return;

    int alturaEsquerda = getAltura(node->esquerda);
    int alturaDireita = getAltura(node->direita);

    if (alturaEsquerda > alturaDireita) {
        node->altura = alturaEsquerda + 1;
    } else {
        node->altura = alturaDireita + 1;
    }
}


template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::rotacionarEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::rotacionarDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::inserir(Node* node, T chave, int indice) {
    if (!node) {
        return new Node(chave, indice);
    }

    if (chave < node->chave) {
        node->esquerda = inserir(node->esquerda, chave, indice);
    } else if (chave > node->chave) {
        node->direita = inserir(node->direita, chave, indice);
    } else {
        // Adiciona o atributo ao nó existente
        node->adicionarIndice(indice);
        return node;
    }

    atualizarAltura(node);
    int balance = getBalanceamento(node);

    // Balanceamento
    if (balance > 1 && chave < node->esquerda->chave) {
        return rotacionarDireita(node);
    }
    if (balance < -1 && chave > node->direita->chave) {
        return rotacionarEsquerda(node);
    }
    if (balance > 1 && chave > node->esquerda->chave) {
        node->esquerda = rotacionarEsquerda(node->esquerda);
        return rotacionarDireita(node);
    }
    if (balance < -1 && chave < node->direita->chave) {
        node->direita = rotacionarDireita(node->direita);
        return rotacionarEsquerda(node);
    }

    return node;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::procurar(Node* raiz, const T& chave) {
    if (!raiz || raiz->chave == chave) {
        return raiz;
    }
    if (chave < raiz->chave) {
        return procurar(raiz->esquerda, chave);
    }
    return procurar(raiz->direita, chave);
}

template <typename T>
void AvlTree<T>::inserir(T chave, int indice) {
    raiz = inserir(raiz, chave, indice);
}

template <typename T>
int* AvlTree<T>::procurar(T chave, int& tamanho) {
    Node* aux = procurar(raiz, chave);
    if (aux) {
        tamanho = aux->tamanhoIndices;
        return aux->indices;
    }
    tamanho = 0;
    return nullptr;
}

template <typename T>
int AvlTree<T>::contarChavesRec(Node* node, T valor, const std::string& op) {
    if (!node) return 0; 

    int count = 0;

    // Dependendo da operação, verificamos se devemos contar o nó atual
    if ((op == ">=" && node->chave >= valor) || (op == "<=" && node->chave <= valor)) {
        count = 1;
    }

    // Chama recursivamente para a esquerda e a direita
    return count + contarChavesRec(node->esquerda, valor, op) + contarChavesRec(node->direita, valor, op);
}

template <typename T>
int AvlTree<T>::contarChaves(T valor, const std::string& op) {
    return contarChavesRec(raiz, valor, op);
}

// Função recursiva para percorrer a árvore e coletar as chaves
template <typename T>
void AvlTree<T>::coletarChavesRec(Node* node, T valor, const std::string& op, int maxTamanho, T* vetor, int& vetorTamanho) {
    if (!node || vetorTamanho >= maxTamanho) return;  
    
    // Verifica a condição do operador
    bool conditionMet = false;
    if (op == ">=" && node->chave >= valor) {
        conditionMet = true;
    } else if (op == "<=" && node->chave <= valor) {
        conditionMet = true;
    }

    // Adiciona a chave ao vetor
    if (conditionMet) {
        vetor[vetorTamanho++] = node->chave;
    }

    // Faz a filtragem de acordo com o operador
    if (op == ">=") {
        coletarChavesRec(node->esquerda, valor, op, maxTamanho, vetor, vetorTamanho);  
        if (vetorTamanho < maxTamanho) {
            coletarChavesRec(node->direita, valor, op, maxTamanho, vetor, vetorTamanho); 
        }
    } else if (op == "<=") {
        coletarChavesRec(node->direita, valor, op, maxTamanho, vetor, vetorTamanho); 
        if (vetorTamanho < maxTamanho) {
            coletarChavesRec(node->esquerda, valor, op, maxTamanho, vetor, vetorTamanho); 
        }
    }
}

template <typename T>
T* AvlTree<T>::coletarChaves(T valor, const std::string& op, int maxTamanho) {
    // Criação de um vetor para armazenar as chaves
    T* vetor = new T[maxTamanho];  
    int vetorTamanho = 0;

    // Função auxiliar para percorrer a árvore e coletar as chaves
    coletarChavesRec(raiz, valor, op, maxTamanho, vetor, vetorTamanho);

    return vetor;
}

template class AvlTree<int>;
template class AvlTree<std::string>;
template class AvlTree<float>;