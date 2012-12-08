#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <sstream>
using std::vector;
using std::stack;
using std::string;
using std::cout;
using std::endl;

class Parser
{
public:
    Parser();
    Parser(std::string);
    double execute(double x=0); // вычисление значения выражения для какой либо переменной (либо, если нет переменных - просто вычисление выражения)
    double execute(vector<double> x); // вычисление значения многомерной функции
    int getDimension(); // получить количество переменных данного выражения
private:
    struct ELEM
    {
        int type; // 0 - value, 1 - operator, 2 - variable, 3 - function
        string data; // данные

        ELEM(string d)
        {
            data = d;
            type = 0;
        }

        ELEM(string d, int t)
        {
            data = d;
            type = t;
        }

        int getType(void)
        {
            return type;
        }
    };
    int dimension; // количество переменных данной функции
    vector<ELEM> out; // данная функция в виде обратной польской нотации
    bool inArray(const char c, string arr); // находится ли данный символ в данном масииве
    bool isDigit(const char c); // является ли данный символ цифрой
    bool isNumeric(const char c); // является ли данный символ цифрой или "точкой"
    bool inFunctions(string::iterator it, int& id, int& len); // явлется ли слудующее выражение математической функцией
    int prioritet(const char c); // получить приоритет операции
    double max(double a, double b);
};
#endif // MAIN_HPP_INCLUDED
