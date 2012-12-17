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
    Parser parser; // ������ ������ ��������������� �����������
    Vector xt; // "�������" ������ ��� ������� �����������
    Vector pt; // ������ ����������� ������

public:
    Methods() {};
    Methods(string expression, Vector x); // ��������� ������� � ��������� �����
    Vector getFunction(); // ���� ������� � ����������
    Vector findMinimum(string method, string expression, Vector start_x, int& k); // ����� �������� ��� �������� ������� ��������� ������� � �������� �����

private:
    double f(Vector x); // ���������� �������� ������ ������� � ������ �����
    double y(double alpha); // ���������� �������� ������� � ��������� �������
    double dy(int i, Vector x); // �������� ������� ����������� �� i-��� ���������� � ����� alpha
    double dy(double alpha); // ����������� ��� ������� ����� ����������
    double Differential(Vector idx, Vector x0, int _ord, double h );
    Vector gradient(Vector); // �������� � ������ �����
    Matrix gess(Vector);
    double min( double a, double b ); // ������� �� ���� ����������
    double max( double a, double b ); // �������� �� ���� ����������
    void swann(double x, double &a, double &b); // ����� �����-1
    void swann2(double x, double &a, double &b); // ����� �����-2
    double dichotomy(double &a, double &b); // ����� ���������
    double bolcano(double &a, double &b, int m); // ����� ��������
    double davidon(double a, double b); // ����� ���������� ������������ (��������)
    double davidon();
    Vector CCD(Vector, int&); // ����� ������������ ��������������� ������ - ���. �4
    Vector Partan2(Vector, int&); // ����� ������-2 - ���.�4
    Vector FR(Vector, int&); // ����� ����������� ���������� �� ������� ��������-����� - ���. �8
    Vector DFP(Vector, int&); // ����� ���������� �������, ������������ ������� ��������-��������-������ - ���. � 7
    Vector Newton(Vector, int&);
    Vector Powell(Vector start_x, int& k);
    int maxArr(double *arr, int size);


};

#endif // METHODS_HPP_INCLUDED
