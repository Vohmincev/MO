#include <vector>
#include <iostream>
#include <cstdarg>
#include <cmath>
#include <cstring>
using std::cout;
using std::endl;
using std::vector;

class Vector;
class Matrix
{
protected:
    int height; // количество строк
    int width; // количество столюцов
    double** data; // массив для хранения значений матрицы

public:
    Matrix() {this->data = NULL; this->width = this->height = 0;};
    Matrix(int w, int h); // создание пустой матрицы заданного размера
    Matrix(int w, int h, double* arr); // создание матрицы заданного размера и занесение в нее значений массива
    Matrix(int w, int h, double a ...); // создание матрицы заданного размера с полным вводом значений всех элементов
    int getHeight(); // получение количества строк
    int getWidth(); // получение количества столбцов
    double& operator()(int i, int j); // переопределение оператора () - получение значения заданного элемента матрицы
    Matrix operator+(Matrix m); // операция "+" для матриц
    Matrix operator-(Matrix m); // операция "-" для матриц
    Matrix operator*(double d); // операция "*" для матрицы и числа
    Matrix operator*(Matrix m); // операция "+" для матрицы и матрицы
    Matrix operator/(Matrix); // оператор "деления". По сути в правой части всегда стоит матрица, состоящая из одного элемента
    Matrix operator/(double); // деление матрицы на число: по сути умножение на 1/d
    //Matrix operator=(Matrix m);
    operator Vector&(void); // оператор приведения типа матрицы к типу вектора
    Matrix makeTranspose(); // транспонирование матрицы
    void makeIdentity(); // создание единичной матрицы
    void makeInv();
    void print(); // вывод матрицы на экран
    double toDouble();
};
