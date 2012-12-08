#include <vector>
#include <iostream>
#include <cstdarg>
#include <cmath>
using std::cout;
using std::endl;
using std::vector;
class Vector
{
    vector<double> data;
    int size;
public:
    Vector();
    Vector(int s ...);
    void setValue(vector<double> x);
    void setValue(int s ...);
    void setSize(int s);
    void print();
    vector<double> getSTLvector();
    double getNorm();
    int getSize();
    Vector operator + (Vector v);
    Vector operator - (Vector v);
    double operator * (Vector v);
    Vector operator * (double value);
    double& operator[](int i);
};
