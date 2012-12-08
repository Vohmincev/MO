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
    int height; // ���������� �����
    int width; // ���������� ��������
    double** data; // ������ ��� �������� �������� �������

public:
    Matrix() {this->data = NULL; this->width = this->height = 0;};
    Matrix(int w, int h); // �������� ������ ������� ��������� �������
    Matrix(int w, int h, double* arr); // �������� ������� ��������� ������� � ��������� � ��� �������� �������
    Matrix(int w, int h, double a ...); // �������� ������� ��������� ������� � ������ ������ �������� ���� ���������
    int getHeight(); // ��������� ���������� �����
    int getWidth(); // ��������� ���������� ��������
    double& operator()(int i, int j); // ��������������� ��������� () - ��������� �������� ��������� �������� �������
    Matrix operator+(Matrix m); // �������� "+" ��� ������
    Matrix operator-(Matrix m); // �������� "-" ��� ������
    Matrix operator*(double d); // �������� "*" ��� ������� � �����
    Matrix operator*(Matrix m); // �������� "+" ��� ������� � �������
    Matrix operator/(Matrix); // �������� "�������". �� ���� � ������ ����� ������ ����� �������, ��������� �� ������ ��������
    Matrix operator/(double); // ������� ������� �� �����: �� ���� ��������� �� 1/d
    //Matrix operator=(Matrix m);
    operator Vector&(void); // �������� ���������� ���� ������� � ���� �������
    Matrix makeTranspose(); // ���������������� �������
    void makeIdentity(); // �������� ��������� �������
    void makeInv();
    void print(); // ����� ������� �� �����
    double toDouble();
};
