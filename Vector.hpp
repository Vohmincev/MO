#include "matrix.hpp"
using std::cout;
using std::endl;
using std::vector;

class Vector : public Matrix // вектор - матрица размером Nx1
{
public:
    Vector() { this->data = NULL; this->width = this->height = 0;};
    Vector(int s); // конструктор вектора
    Vector(int s, double a ...); // конструктор с вводом всех элементов вектора вручную
    void setValue(int s ...); // задание элементов вектора
    void setZero(); // сделать вектор состоящим из "0"
    int getSize(); // получение размера вектора
    void setSize(int); // задание размера вектора
    vector<double> getSTLvector(); // получить vector<double> - нужно для синтаксического анализатора
    double getNorm(); // вычисление нормы вектора
    void print(); // вывод значений вектора на экран
    Vector operator-(Vector v); // переопределение операциЙ
    Vector operator+(Vector v); // ---
    Vector operator*(double d); // ---
    Matrix operator*(Vector v) { return ((Matrix)*this * (Matrix)v); } // умножение вектора на вектор - для простоты всегда получаем матрицу
    double& operator[](int); // ---
    double operator[](int) const;
};

