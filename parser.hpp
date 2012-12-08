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
    double execute(double x=0); // ���������� �������� ��������� ��� ����� ���� ���������� (����, ���� ��� ���������� - ������ ���������� ���������)
    double execute(vector<double> x); // ���������� �������� ����������� �������
    int getDimension(); // �������� ���������� ���������� ������� ���������
private:
    struct ELEM
    {
        int type; // 0 - value, 1 - operator, 2 - variable, 3 - function
        string data; // ������

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
    int dimension; // ���������� ���������� ������ �������
    vector<ELEM> out; // ������ ������� � ���� �������� �������� �������
    bool inArray(const char c, string arr); // ��������� �� ������ ������ � ������ �������
    bool isDigit(const char c); // �������� �� ������ ������ ������
    bool isNumeric(const char c); // �������� �� ������ ������ ������ ��� "������"
    bool inFunctions(string::iterator it, int& id, int& len); // ������� �� ��������� ��������� �������������� ��������
    int prioritet(const char c); // �������� ��������� ��������
    double max(double a, double b);
};
#endif // MAIN_HPP_INCLUDED
