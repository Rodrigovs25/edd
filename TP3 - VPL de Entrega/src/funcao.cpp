#include "funcao.hpp"

// Retorna o número de dias em um mês específico
int diasNoMes(int mes, int ano) {
    int vetorDias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return vetorDias[mes - 1];
}

char* converterStrChar(const std::string& str) {
    // Aloca memória para a cópia da string
    int tamanho = 0;
    while (str[tamanho] != '\0') {
        tamanho++;
    }
    char* aux = new char[tamanho + 1]; 

    // Copiar caractere por caractere
    int i;
    for (i = 0; i < tamanho; i++) {
        aux[i] = str[i];
    }
    // Adiciona o terminador nulo
    aux[tamanho] = '\0';  

    return aux;  
}


// Converte uma data em segundos desde a referência(2022-01-01T00:00:00)
int converterSegundos(const std::string& data) {
    char* dataChar = converterStrChar(data);
    int inicioMes=1, inicioDia=1;

    // Dividir a string
    int ano = (dataChar[0] - '0') * 1000 + (dataChar[1] - '0') * 100 + (dataChar[2] - '0') * 10 + (dataChar[3] - '0');
    int mes = (dataChar[5] - '0') * 10 + (dataChar[6] - '0');
    int dia = (dataChar[8] - '0') * 10 + (dataChar[9] - '0');
    int hora = (dataChar[11] - '0') * 10 + (dataChar[12] - '0');
    int minuto = (dataChar[14] - '0') * 10 + (dataChar[15] - '0');
    int segundo = (dataChar[17] - '0') * 10 + (dataChar[18] - '0');

    int totalSegundos = 0;

    // Adiciona segundos dos meses completos
    int i;
    for(i = inicioMes; i < mes; i++) {
        totalSegundos += diasNoMes(i, ano) * 24 * 3600;
    }

    // Adiciona segundos dos dias completos
    totalSegundos += (dia - inicioDia) * 24 * 3600;

    // Adiciona horas, minutos e segundos do dia atual
    totalSegundos += hora * 3600 + minuto * 60 + segundo;

    return totalSegundos;
}

int setDuracao(const std::string& partida, const std::string& chegada) {
    return converterSegundos(chegada) - converterSegundos(partida);
}

void troca(int& a, int& b) {
    int aux = a;
    a = b;
    b = aux;
}

void quickSort(int* vetor, int inicio, int fim) {
    if (inicio < fim) {
        // Pivô como último elemento
        int pivo = vetor[fim]; 
        int i = inicio - 1;
        int j;
        for(j = inicio; j < fim; j++) {
            if (vetor[j] < pivo) {
                i++;
                troca(vetor[i], vetor[j]); 
            }
        }
        troca(vetor[i + 1], vetor[fim]);
        int indicePivo = i + 1;

        quickSort(vetor, inicio, indicePivo - 1);
        quickSort(vetor, indicePivo + 1, fim);
    }
}

void ordenarVetor(int* vetor, int tamanho) {
    quickSort(vetor, 0, tamanho - 1);
}

// Une dois vetores e armazena o resultado em a
void unirVetores(int*& a, int& tamanhoA, int* b, int tamanhoB) {
    int* aux = new int[tamanhoA + tamanhoB]; 
    int i = 0, j = 0, k = 0;
    
    // Mesclar ordenadamente eliminando duplicatas
    while (i < tamanhoA && j < tamanhoB) {
        if (a[i] < b[j]) {
            aux[k++] = a[i++];
        } else if (a[i] > b[j]) {
            aux[k++] = b[j++];
        } else { 
            // Elementos iguais
            aux[k++] = a[i++];
            j++; 
        }
    }
    
    // Copia os elementos restantes de a
    while (i < tamanhoA) {
        aux[k++] = a[i++];
    }
    
    // Copia os elementos restantes de b
    while (j < tamanhoB) {
        aux[k++] = b[j++];
    }
    
    tamanhoA = k;
    delete[] a; 
    a = new int[tamanhoA];
    
    // Copia para o vetor final
    for(i = 0; i < tamanhoA; i++) {
        a[i] = aux[i];
    }
    
    delete[] aux; 
}
