#include "expressao.hpp"
#include "funcao.hpp"

Expressao::Expressao() : cabeca(nullptr) {}

Expressao::~Expressao() {
    while (cabeca) {
        Predicado* temp = cabeca;
        cabeca = cabeca->proximo;
        tamanho--;
        delete temp;
    }
}

// Converter string para int 
int Expressao::stringInt(const std::string& val) {
    int resultado = 0;
    char* str = converterStrChar(val);
    // Converte cada caractere para o número correspondente
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            return 0; 
        }
        resultado = resultado * 10 + (*str - '0'); 
        str++;
    }

    return resultado;
}

// Converter string para float
float Expressao::stringFloat(const std::string& val) {
    float resultado = 0.0f;
    // Usado para calcular a parte decimal
    float decimal = 0.1f;  

    char* str = converterStrChar(val);
    // Converte a parte inteira
    while (*str != '\0' && (*str >= '0' && *str <= '9')) {
        resultado = resultado * 10.0f + (*str - '0');
        str++;
    }

    // Processa a parte decimal
    if (*str == '.') {
        // Pula o ponto decimal
        str++;  
        while (*str != '\0' && (*str >= '0' && *str <= '9')) {
            resultado += (*str - '0') * decimal;
            // Move o ponto decimal para a direita
            decimal /= 10.0f;  
            str++;
        }
    }

    return resultado;
}

void Expressao::adicionarPredicado(const std::string& atributo, const std::string& operador, const std::string& val) {
    void* valor;
    std::string tipo;
    
    if (atributo == "sea" || atributo == "sto" || atributo == "dur") {
        valor = new int(stringInt(val));
        tipo = "int";
    } else if (atributo == "prc") {
        valor = new float(stringFloat(val));
        tipo = "float";
    } else {
        std::string* aux = new std::string(val);
        valor =  aux;
        tipo = "string";
    }

    Predicado* newPredicado = new Predicado(atributo, operador, valor, tipo);
    newPredicado->proximo = cabeca;
    cabeca = newPredicado;
    tamanho++;
}

bool Expressao::vazio() const {
    return cabeca == nullptr;
}

Predicado* Expressao::remover() {
    if (vazio()){
        std::cerr << "A lista está vazia" << std::endl;
        return nullptr;
    }
    Predicado* temp = cabeca;
    cabeca = cabeca->proximo;
    temp->proximo = nullptr;
    tamanho--;
    return temp;
}

// Função para processar uma expressão
void processarExpressao(const std::string& expr, Expressao& expressao) {
    char* exprLogi = converterStrChar(expr);
    while (*exprLogi) {
        while (*exprLogi && (*exprLogi == ' ' || *exprLogi == '(' || *exprLogi == ')')){
            exprLogi++;
        }
        if (!*exprLogi) break;

        // Ignorar operadores lógicos (&&)
        if (*exprLogi == '&' && *(exprLogi + 1) == '&') {
            exprLogi += 2;
            continue;
        }

        const char* start = exprLogi;
        while (*exprLogi && *exprLogi != ' ' && *exprLogi != '=' && *exprLogi != '<' && *exprLogi != '>'){
            exprLogi++;
        }
        std::string atributo(start, exprLogi - start);

        while (*exprLogi && (*exprLogi == ' ')){ 
            exprLogi++;
        }
        std::string operador;
        if (*exprLogi == '=' || *exprLogi == '<' || *exprLogi == '>') {
            operador += *exprLogi++;
            if (*exprLogi == '=') operador += *exprLogi++;
        }
        
        while (*exprLogi && (*exprLogi == ' ')){
            exprLogi++;
        } 
        start = exprLogi;
        while (*exprLogi && *exprLogi != ' ' && *exprLogi != ')' && *exprLogi != '('){ 
            exprLogi++;
        }
        std::string valor(start, exprLogi - start);
        //std::cout << atributo <<  " " << oper << " " << valor << std::endl;
        expressao.adicionarPredicado(atributo, operador, valor);
    }
}