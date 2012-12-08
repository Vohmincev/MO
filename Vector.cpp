#include "Vector.hpp"

Vector::Vector(int s) : Matrix(1, s)
{
}

Vector::Vector(int s, double a ...)
{
    this->width = 1;
    this->height = s;
    this->data = new double*[s];
    for(int i = 0; i < s; i++)
    {
        this->data[i] = new double[1];
        memset(this->data[i], 0, sizeof(double)*1);
    }

    va_list p;
    va_start(p, a);
    for( int i=0; i<s; i++ )
    {
        for( int j=0; j<1; j++ )
        {
            this->data[i][j] = a;
            a = va_arg(p, double);
        }
    }
    va_end(p);
}

void Vector::setValue(int s ...)
{
    Vector v(s);
    va_list p;
    va_start(p, s);
    for(int i = 0; i < s; i++)
        v.data[i][0]=va_arg(p, double);
    va_end(p);
    *this = v;
}

void Vector::setZero()
{
    for(int i = 0; i < this->getHeight(); i++)
        this->data[i][0] = 0;
}

int Vector::getSize()
{
    return this->height;
}

void Vector::setSize(int h)
{
    this->width = 1;
    this->height = h;
    this->data = new double*[h];
    for(int i = 0; i < h; i++)
    {
        this->data[i] = new double[1];
        memset(this->data[i], 0, sizeof(double)*1);
    }
}

vector<double> Vector::getSTLvector()
{
    vector<double> out;
    for(int i = 0; i < this->height; i++)
    {
        out.push_back(this->data[i][0]);
    }
    return out;
}

double Vector::getNorm()
{
    double n=0.0;
    for(int i=0; i < this->height; i++)
        n += (data[i][0]*data[i][0]);
    return sqrt(n);
}


Vector Vector::operator-(Vector v)
{
    return ((Matrix)*this - (Matrix)v);
}

Vector Vector::operator+(Vector v)
{
    return ((Matrix)*this + (Matrix)v);
}

Vector Vector::operator*(double d)
{
    return (Matrix)*this * d;
}

double& Vector::operator[](int i)
{
    return this->data[i][0];
}

double Vector::operator[] (int i) const
{
    return this->data[i][0];
}

void ::Vector::print()
{
    cout << "(";
    for(int i =0; i < this->height; i++)
    {
        cout << this->data[i][0];
        if(i != (this->height-1)) cout << ", ";
    }
    cout << ")" << endl;
}
