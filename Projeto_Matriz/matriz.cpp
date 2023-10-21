#include "matriz.h"
namespace ams{
Matriz::Matriz(int linhas, int colunas):
    matriz(0),
    linhas(0),
    colunas(0)
{
    try {
        if (linhas <= 0) throw std::string("O número de linhas precisa ser um número positivo");
        if (colunas <= 0) throw std::string("O número de colunas precisa ser un número positivo");
        matriz = new int*[linhas];
        for (int i = 0; i < linhas; i++){
            matriz[i] = new int[colunas];

        }
    } catch (std::bad_alloc &erro) {
        throw std::string("A nova matriz não pôde ser criada");
    }
    this->linhas = linhas;
    this->colunas = colunas;
}

Matriz::~Matriz()
{
    if (matriz){
        for (int i = 0; i < linhas; i++)
            delete [] matriz[i];
    }
}

void Matriz::setElemento(int linha, int coluna, int elemento)
{
    if (linha >= this->linhas || linha < 0) throw std::string("Posição da linha inválida.");
    if (coluna >= this->colunas || coluna < 0) throw std::string("Posição da coluna inválida.");
    matriz[linha][coluna] = elemento;
}

int Matriz::getElemento(int linha, int coluna) const
{
    if (linha >= this->linhas || linha < 0) throw std::string("Posição da linha inválida.");
    if (coluna >= this->colunas || coluna < 0) throw std::string("Posição da coluna inválida.");
    return matriz[linha][coluna];
}

std::string Matriz::getMatriz() const
{
    std::string saida = " ";
    for (int i = 0; i < this->linhas; i++){
        for (int j = 0; j < this->colunas; j++){
            saida += std::to_string(getElemento(i,j)) + "  ";
        }
        saida += "\n ";
    }
    return saida;
}

Matriz Matriz::operator +(Matriz &matriz)
{
    if (this->getLinhas() != matriz.getLinhas() || this->getColunas() != matriz.getColunas()) throw std::string("Não é possível somar as matrizes.");
    Matriz soma(linhas, colunas);
    for(int i = 0; i < this->getLinhas(); i++){
        for(int j = 0; j < this->getColunas(); j++){
            int elemento = this->getElemento(i,j)+matriz.getElemento(i,j);
            soma.setElemento(i,j,elemento);
        }
    }
    return soma;
}

Matriz Matriz::operator-(Matriz &matriz)
{

    if (this->getLinhas() != matriz.getLinhas() || this->getColunas() != matriz.getColunas()) throw std::string("Não é possível subtrair as matrizes.");
    Matriz subtracao(this->linhas, colunas);
    for(int i = 0; i < this->getLinhas(); i++){
        for(int j = 0; j < this->getColunas(); j++){
            int elemento = this->getElemento(i,j)-matriz.getElemento(i,j);
            subtracao.setElemento(i,j,elemento);
        }
    }
    return subtracao;
}

Matriz Matriz::operator*(Matriz &matriz)
{
    if (this->getColunas() != matriz.getLinhas()) throw std::string("Não é possível multiplicar as matrizes.");
    Matriz multiplicacao(this->getLinhas(), matriz.getColunas());
    for (int i = 0; i < this->getLinhas(); i++) {
        for (int j = 0; j < matriz.colunas; j++) {
            int elemento = 0;
            for (int k = 0; k < colunas; k++) {
                elemento += this->getElemento(i,k)*matriz.getElemento(k,j);
            }
            multiplicacao.setElemento(i,j,elemento);
        }
    }
    return multiplicacao;
}

Matriz Matriz::operator*(int k){
    Matriz multiplicacao(this->getLinhas(), this->getColunas());
    for (int i = 0; i < this->getLinhas(); i++){
        for (int j = 0; j <this->getColunas();j++){
            multiplicacao.setElemento(i,j,getElemento(i,j)*k);
        }
    }
    return multiplicacao;
}

Matriz Matriz::operator^(int k)
{
    if (k < 0) throw std::string("O número para a potência precisa ser positivo");
    Matriz potencia(this->getLinhas(),this->getColunas());
    for (int i = 0; i < this->getLinhas(); i++){
        for (int j = 0; j <this->getColunas();j++){
            potencia.setElemento(i,j,pow(getElemento(i,j),k));
        }
    }
    return potencia;
}

std::string Matriz::operator==(Matriz &matriz)
{
    if (this->linhas != matriz.getLinhas() || this->colunas != matriz.getColunas()) return "✖ As matrizes NÃO são iguais";
    for (int i = 0; i < this->linhas; i++){
        for (int j = 0; j < this->colunas; j++){
            if (getElemento(i,j) != matriz.getElemento(i,j)) return "✖ As matrizes NÃO são iguais";
        }
    }
    return "= As matrizes são iguais";
}

std::string Matriz::operator!=(Matriz &matriz)
{
    if (this->linhas != matriz.getLinhas() || this->colunas != matriz.getColunas()) return "≠ As matrizes são diferentes";
    for (int i = 0; i < this->linhas; i++){
        for (int j = 0; j < this->colunas; j++){
            if (getElemento(i,j) != matriz.getElemento(i,j)) return "✖ As matrizes são diferentes";
        }
    }
    return "≠ As matrizes NÃO são diferentes";
}

bool Matriz::TriangularSuperior() const
{
    if (this->linhas == 1 && this->colunas == 1) throw std::string("A matriz precisa ter pelo menos ordem 2");
    if (this->linhas != this->colunas) throw std::string("A matriz precisa ser quadrada");
    for (int i = 1; i < this->linhas; i++){
        for (int j = 0; j<i; j++){
            if (getElemento(i,j) != 0) {
                return false;
            }
        }
    }
    return true;
}

bool Matriz::TriangularInferior() const
{
    if (this->linhas == 1 && this->colunas == 1) throw std::string("A matriz precisa ter pelo menos ordem 2");
    if (this->linhas != this->colunas) throw std::string("A matriz precisa ser quadrada");
    for (int i = 0; i < this->linhas; i++) {
        for (int j = i + 1; j < this->colunas; j++) {
            if (getElemento(i,j) != 0) {
                return false;
            }
        }
    }
    return true;
}

Matriz Matriz::calcularTransposta() const
{
    ams::Matriz transposta(this->colunas, this->linhas);
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            transposta.matriz[j][i] = this->matriz[i][j];
        }
    }
    return transposta;
}

bool Matriz::Simetrica() const
{
    if (this->linhas != this->colunas) throw std::string("A matriz precisa ser quadrada");
    ams::Matriz transposta = calcularTransposta();
    for (int i = 0; i < this->linhas; i++) {
        for (int j = 0; j < this->colunas; j++) {
            if (this->matriz[i][j] != transposta.getElemento(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool Matriz::Identidade() const
{
    if (this->linhas != this->colunas) throw std::string("A matriz precisa ser quadrada");
    for (int i = 0; i < this->linhas; i++) { //se elementos fora da diagonal são != 0
            for (int j = 0; j < this->colunas; j++) {
                if (i != j && this->matriz[i][j] != 0) {
                    return false;
                }
            }
        }
    for (int i = 0; i < this->linhas; i++) { // se diagonal = 1
            if (this->matriz[i][i] != 1) {
                return false;
            }
        }
    return true;
}



}
