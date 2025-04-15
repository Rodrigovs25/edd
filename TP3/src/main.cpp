#include "voo.hpp"
#include "funcao.hpp"
#include "avlTree.hpp"
#include "consulta.hpp"
#include "expressao.hpp"
#include "armazenaVetores.hpp"
#include "predicado.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[]){

    // Arquivo de entrada
    std::ifstream inf;
    inf.open(argv[1]);
    if(!inf){
        std::cerr << "Arquivo não pode ser aberto!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    int numeroVoos;
    inf >> numeroVoos;

    // Atributos Voo
    std::string origem;
    std::string destino;
    float preco;
    int assentos;
    std::string partida;  
    std::string chegada;    
    int paradas;
    int duracao;   

    // Arvores dos indices
    AvlTree<std::string> org;
    AvlTree<std::string> dst;
    AvlTree<float> prc;
    AvlTree<int> sea;
    AvlTree<std::string> dep;
    AvlTree<std::string> arr;
    AvlTree<int> sto;
    AvlTree<int> dur;

    Voo *voos = new Voo[numeroVoos];

    // Leitura dos voos
    int i, j;
    for(i = 0; i < numeroVoos; i++){
        // Ler os dados do voo
        inf >> origem;
        inf >> destino;
        inf >> preco;
        inf >> assentos;
        inf >> partida;
        inf >> chegada;
        inf >> paradas;
        // Valor da duracao
        duracao = setDuracao(partida, chegada);
        
        //Colocar voos na vetor
        voos[i] = Voo(origem, destino, preco, assentos, partida, chegada, paradas, duracao);
        
        //Inserir nas arvores
        org.inserir(origem, i);
        dst.inserir(destino, i);
        prc.inserir(preco, i);
        sea.inserir(assentos, i);
        dep.inserir(partida, i);
        arr.inserir(chegada, i);
        sto.inserir(paradas, i);
        dur.inserir(duracao, i);
    }   

    int qtdDeConsultas, qtdMaxVoos;
    std::string tiagrama, filtro;
    inf >> qtdDeConsultas;

    Consulta *consultas = new Consulta[qtdDeConsultas];

    // Leitura das consultas
    for(i = 0; i < qtdDeConsultas; i++){
        inf >> qtdMaxVoos;
        inf >> tiagrama;
        inf >> filtro;

        consultas[i] = Consulta(qtdMaxVoos, tiagrama, filtro);
    }

    inf.close();


    // Loop principal, faz o processamento da cada consulta
    for(i = 0; i < qtdDeConsultas; i++){
        Expressao expressoes;
        ArmazenaVetores armazenamento;

        std::cout << consultas[i];
        std::cout << std::endl;

        // Faz a flitragem processando cada expressao e dividindo ela em predicados
        processarExpressao(consultas[i].getFiltro(), expressoes);
        while(!expressoes.vazio()){
            Predicado* aux = expressoes.remover();
            // Faz o processamento de cada predicado
            // Dividir pelo operador
            if(aux->getOperador() == "=="){
                // Dividir pelo tipo str, float, int
                if (aux->getTipo() == "string") {
                    std::string valorPredicado = *static_cast<std::string*>(aux->getValorFinal());
                    // Vai acessar cada árvore pelo nome do atributo
                    if(aux->getAtributo() == "org"){
                        int tamanhoVetorOrg;
                        // Acessar os índices
                        int* vetorIndicesOrg = org.procurar(valorPredicado, tamanhoVetorOrg);
                        ordenarVetor(vetorIndicesOrg, tamanhoVetorOrg);
                        // Armazenar o vetor com os índices
                        armazenamento.adicionarVetor(vetorIndicesOrg, tamanhoVetorOrg);
                        
                    } else if(aux->getAtributo() == "dst"){
                        int tamanhoVetorDst;
                        int* vetorIndicesDst = dst.procurar(valorPredicado, tamanhoVetorDst);
                        ordenarVetor(vetorIndicesDst, tamanhoVetorDst);
                        armazenamento.adicionarVetor(vetorIndicesDst, tamanhoVetorDst);
                        
                    } else if(aux->getAtributo() == "dep"){
                        int tamanhoVetorDep;
                        int* vetorIndicesDep = dep.procurar(valorPredicado, tamanhoVetorDep);
                        ordenarVetor(vetorIndicesDep, tamanhoVetorDep);
                        armazenamento.adicionarVetor(vetorIndicesDep, tamanhoVetorDep);
                        
                    } else if(aux->getAtributo() == "arr"){
                        int tamanhoVetorArr;
                        int* vetorIndicesArr = arr.procurar(valorPredicado, tamanhoVetorArr);
                        ordenarVetor(vetorIndicesArr, tamanhoVetorArr);
                        armazenamento.adicionarVetor(vetorIndicesArr, tamanhoVetorArr);
                        
                    }
                } else if(aux->getTipo() == "int"){
                    // Vai acessar cada árvore pelo nome do atributo
                    int valorPredicado = *static_cast<int*>(aux->getValorFinal());
                    if(aux->getAtributo() == "sea"){
                        int tamanhoVetorSea;
                        int* vetorIndicesSea = sea.procurar(valorPredicado, tamanhoVetorSea);
                        ordenarVetor(vetorIndicesSea, tamanhoVetorSea);
                        armazenamento.adicionarVetor(vetorIndicesSea, tamanhoVetorSea);
                        
                    } else if(aux->getAtributo() == "sto"){
                        int tamanhoVetorSto;
                        int* vetorIndicesSto = sto.procurar(valorPredicado, tamanhoVetorSto);
                        ordenarVetor(vetorIndicesSto, tamanhoVetorSto);
                        armazenamento.adicionarVetor(vetorIndicesSto, tamanhoVetorSto);
                        
                    } else if(aux->getAtributo() == "dur"){
                        int tamanhoVetorDur;
                        int* vetorIndicesDur = dur.procurar(valorPredicado, tamanhoVetorDur);
                        ordenarVetor(vetorIndicesDur, tamanhoVetorDur);
                        armazenamento.adicionarVetor(vetorIndicesDur, tamanhoVetorDur);
                        
                    }
                } else {
                    float valorPredicado = *static_cast<float*>(aux->getValorFinal());
                    int tamanhoVetorPrc;
                    int* vetorIndicesPrc = prc.procurar(valorPredicado, tamanhoVetorPrc);
                    ordenarVetor(vetorIndicesPrc, tamanhoVetorPrc);
                    armazenamento.adicionarVetor(vetorIndicesPrc, tamanhoVetorPrc);
                    
                }
            // Acessar os operadores >= e <= para os tipos int e float
            } else {
                // Acessar o tipo float
                if(aux->getTipo() == "float"){    
                    float valorPredicado = *static_cast<float*>(aux->getValorFinal());
                    int qtdChavesPrc = prc.contarChaves(valorPredicado, aux->getOperador());
                    // Vetor com as chaves que atendem o filtro
                    float* vetorChavesPrc = prc.coletarChaves(valorPredicado, aux->getOperador(), qtdChavesPrc);
                    int tamanhoVetorFinalPrc = 0; 
                    // Vetor final com os indices
                    int* vetorFinalPrc = new int[tamanhoVetorFinalPrc]; 
                    
                    for(j = 0; j < qtdChavesPrc; j++){
                        int tamanhoVetorPrc;
                        // Vetor com indices de cada chave
                        int* vetorIndicesSea = prc.procurar(vetorChavesPrc[j], tamanhoVetorPrc);
                        // União dos vetores
                        unirVetores(vetorFinalPrc, tamanhoVetorFinalPrc, vetorIndicesSea, tamanhoVetorPrc);
                    }
                    // Adicionar o vetor de indices na estrutura
                    armazenamento.adicionarVetor(vetorFinalPrc, tamanhoVetorFinalPrc);
                    delete[] vetorFinalPrc;
                    
                } else if (aux->getTipo() == "int") {
                    if(aux->getAtributo() == "sea"){
                        int valorPredicado = *static_cast<int*>(aux->getValorFinal());
                        int qtdChavesSea = sea.contarChaves(valorPredicado, aux->getOperador());
                        int* vetorChavesSea = sea.coletarChaves(valorPredicado, aux->getOperador(), qtdChavesSea);
                        int tamanhoVetorFinalSea = 0; 
                        int* vetorFinalSea = new int[tamanhoVetorFinalSea]; 
                        
                        for(j = 0; j < qtdChavesSea; j++){
                            int tamanhoVetorSea;
                            int* vetorIndicesSea = sea.procurar(vetorChavesSea[j], tamanhoVetorSea);
                            unirVetores(vetorFinalSea, tamanhoVetorFinalSea, vetorIndicesSea, tamanhoVetorSea);
                        }
                        armazenamento.adicionarVetor(vetorFinalSea, tamanhoVetorFinalSea);
                        delete[] vetorFinalSea;
                        
                    } else if(aux->getAtributo() == "sto"){
                        int valorPredicado = *static_cast<int*>(aux->getValorFinal());
                        int qtdChavesSto = sto.contarChaves(valorPredicado, aux->getOperador());
                        int* vetorChavesSto = sto.coletarChaves(valorPredicado, aux->getOperador(), qtdChavesSto);
                        int tamanhoVetorFinalSto = 0; 
                        int* vetorFinalSto = new int[tamanhoVetorFinalSto]; 
                        
                        for(j = 0; j < qtdChavesSto; j++){
                            int tamanhoVetorSto;
                            int* vetorIndicesSto = sto.procurar(vetorChavesSto[j], tamanhoVetorSto);
                            unirVetores(vetorFinalSto, tamanhoVetorFinalSto, vetorIndicesSto, tamanhoVetorSto);
                        }
                        armazenamento.adicionarVetor(vetorFinalSto, tamanhoVetorFinalSto);
                        delete[] vetorFinalSto;
                        
                    } else if(aux->getAtributo() == "dur"){
                        int valorPredicado = *static_cast<int*>(aux->getValorFinal());
                        int qtdChavesDur = dur.contarChaves(valorPredicado, aux->getOperador());
                        int* vetorChavesDur = dur.coletarChaves(valorPredicado, aux->getOperador(), qtdChavesDur);                    
                        int tamanhoVetorFinalDur = 0; 
                        int* vetorFinalDur = new int[tamanhoVetorFinalDur]; 
                        
                        for(j = 0; j < qtdChavesDur; j++){
                            int tamanhoVetorDur;
                            int* vetorIndicesDur = dur.procurar(vetorChavesDur[j], tamanhoVetorDur);
                            unirVetores(vetorFinalDur, tamanhoVetorFinalDur, vetorIndicesDur, tamanhoVetorDur);
                        }
                        armazenamento.adicionarVetor(vetorFinalDur, tamanhoVetorFinalDur);
                        delete[] vetorFinalDur;
                
                    }
                }
            }
            
            delete aux;
        }
        // Verificação para achar os índices em comum
        int tamanhoVetorComum;
        
        // Vetor com indices que atendem a consulta
        int* commonElements = armazenamento.encotrarIndicesComum(tamanhoVetorComum);
        Voo *auxVoos = new Voo[tamanhoVetorComum];

        // Copiar os voos dos índices especificados para auxVoos
        for(j = 0; j < tamanhoVetorComum; j++) {
            int idx = commonElements[j];  // Índice do voo em voos
            if (idx >= 0 && idx < numeroVoos) {  // Verifica se o índice é válido
                auxVoos[j] = voos[idx];
            } 
        }
        
        // Faz a parte de ordenação da consulta
        auxVoos->ordenarVoos(tamanhoVetorComum, consultas[i].getTiagrama());

        // Faz a parte de impressão dos voos da consulta
        int qtdVoosPedidos = consultas[i].getNumeroVoos();
        for(j = 0; j < qtdVoosPedidos; j++){
            std::cout << auxVoos[j];
            std::cout << std::endl;
        }
        delete[] auxVoos;    
    }
    
    delete[] consultas;
    delete[] voos;

    return 0;

}
