#include "parser.hpp"
#include "Vector.hpp"
#include <map>
#ifndef METHODS_HPP_INCLUDED
#define METHODS_HPP_INCLUDED
#define EPSILON 10e-6

class Methods
{
    typedef Vector (Methods::* Callback)(Vector, int&);
private:
    Parser parser; // объект класса синтаксического анализатора
    Vector xt; // "рабочий" вектор для методов оптимизации
    Vector pt; // вектор направления поиска

public:
    Methods() {};
    Methods(string expression, Vector x); // получение функции и начальной точки
    Vector getFunction(); // ввод функции с клавиатуры
    Vector findMinimum(string method, string expression, Vector start_x, int& k); // Поиск минимума для заданной функции взаданным методом в заданной точке

private:
    double f(Vector x); // вычисление значения данной функции в данной точке
    double y(double alpha); // вычисление значения функции в двумерной области
    double dy(int i, Vector x); // значение частной производной по i-той переменной в точке alpha
    double dy(double alpha); // производная для функции одной переменной
    double Differential(Vector idx, Vector x0, int _ord, double h );
    Vector gradient(Vector); // градиент в данной точке
    Matrix gess(Vector);
    double min( double a, double b ); // минимум из двух переменных
    double max( double a, double b ); // максимум из двух переменных
    void swann(double x, double &a, double &b); // метод Свена-1
    void swann2(double x, double &a, double &b); // метод Свена-2
    double dichotomy(double &a, double &b); // метод дихотомии
    double bolcano(double &a, double &b, int m); // метод Больцано
    double davidon(double a, double b); // Метод кубической интерполяции (Дэвидона)
    double davidon();
    Vector CCD(Vector, int&); // метод циклического покоординатного спуска - лаб. №4
    Vector Partan2(Vector, int&); // метод Партан-2 - лаб.№4
    Vector FR(Vector, int&); // Метод сопряженных градиентов по формуле Флетчера-Ривса - лаб. №8
    Vector DFP(Vector, int&); // метод переменной метрики, использующий формулу Дэвидона-Флетчера-Пауэла - лаб. № 7
    Vector Newton(Vector, int&);
    Vector Powell(Vector start_x, int& k);
    int maxArr(double *arr, int size);


};

#endif // METHODS_HPP_INCLUDED
