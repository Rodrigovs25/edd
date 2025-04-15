#ifndef VECTOR_HPP
#define VECTOR_HPP

// Vetor base
class Vetor {
public:
    int* dados;
    int tamanho;

    Vetor(int* d, int t);
    ~Vetor();
};

// Armazena os vetores de índices, cada linha vai ter um vetor e o tamanho das linhas vai variar
class ArmazenaVetores {
private:
    Vetor** Vetores;
    int count;
    int capacidade;

    // Aumenta a estrutura de armazenamento de vetores 
    void redefinir();

public:
    ArmazenaVetores();
    ~ArmazenaVetores();

    // Adicionar outro vetor na estrutura
    void adicionarVetor(int* vetor, int tamanho);
    // Retorna um vetor com os índices que aparecem em todos os outros vetores
    int* encotrarIndicesComum(int& tamanhoVetorComum);
};

#endif 
