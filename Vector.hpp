#include "matrix.hpp"
using std::cout;
using std::endl;
using std::vector;

class Vector : public Matrix // ������ - ������� �������� Nx1
{
public:
    Vector() { this->data = NULL; this->width = this->height = 0;};
    Vector(int s); // ����������� �������
    Vector(int s, double a ...); // ����������� � ������ ���� ��������� ������� �������
    void setValue(int s ...); // ������� ��������� �������
    void setZero(); // ������� ������ ��������� �� "0"
    int getSize(); // ��������� ������� �������
    void setSize(int); // ������� ������� �������
    vector<double> getSTLvector(); // �������� vector<double> - ����� ��� ��������������� �����������
    double getNorm(); // ���������� ����� �������
    void print(); // ����� �������� ������� �� �����
    Vector operator-(Vector v); // ��������������� ��������
    Vector operator+(Vector v); // ---
    Vector operator*(double d); // ---
    Matrix operator*(Vector v) { return ((Matrix)*this * (Matrix)v); } // ��������� ������� �� ������ - ��� �������� ������ �������� �������
    double& operator[](int); // ---
    double operator[](int) const;
};

