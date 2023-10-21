#ifndef MATRIZ_H
#define MATRIZ_H
#include <string>
#include <cmath>
namespace ams {
class Matriz
{
private:
    int **matriz;
    int linhas;
    int colunas;
public:
    Matriz(int linhas, int colunas);
    ~Matriz();
    void setElemento(int linha, int coluna, int elemento);
    int getElemento(int linha, int coluna)const;
    int getLinhas()const{return this->linhas;}
    int getColunas()const{return this->colunas;}
    std::string getMatriz() const;
    Matriz operator +(Matriz &matriz);
    Matriz operator-(Matriz &matriz);
    Matriz operator*(Matriz &matriz);
    Matriz operator*(int k);
    Matriz operator^(int k);
    std::string operator==(Matriz &matriz);
    std::string operator!=(Matriz &matriz);
    bool TriangularSuperior()const;
    bool TriangularInferior()const;
    Matriz calcularTransposta()const;
    bool Simetrica()const;
    bool Identidade()const;
};
}
#endif // MATRIZ_H
