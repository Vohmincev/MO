#include "Vector.hpp"
/*using std::cout;
using std::endl;
using std::vector;*/

Vector::Vector()
{
    return;
}

Vector::Vector(int s ...)
{
    size = s;
    va_list p;
    va_start(p, s);
    for(int i = 0; i < s; i++)
        this->data.push_back(va_arg(p, double));
    va_end(p);
}

void Vector::setValue(vector<double> x)
{
    if(this->size == (int)x.size())
        this->data = x;
    else cout << "fuck you!\n";
}

void Vector::setValue(int s ...)
{
    size = s;
    Vector v(s);
    va_list p;
    va_start(p, s);
    for(int i = 0; i < s; i++)
        v.data[i]=va_arg(p, double);
    va_end(p);
    *this = v;
}

void Vector::setSize(int s)
{
    this->size = s;
    this->data.resize(s);
    for(int i = 0; i < s; i++)
        this->data[i] = 0.0;
}

void Vector::print()
{
    cout << "( ";
    for(unsigned int i = 0; i < this->data.size(); i++)
        cout << this->data[i] << ", ";
    cout << ")" << endl;;
}

vector<double> Vector::getSTLvector()
{
    return this->data;
}

double Vector::getNorm()
{
    unsigned int i;
    double n=0;
    for(i=0; i<data.size(); i++)
        n += (data[i]*data[i]);
    return sqrt(n);
}

int Vector::getSize()
{
    return this->size;
}

Vector Vector::operator + (Vector v)
{
    if(v.getSize() == this->getSize())
        for(int i = 0; i < this->getSize(); i++ )
        {
            v.data[i] += this->data[i];
        }
    else
    {
        cout << "demensions not equals!" << endl;
        return *this;
    }
    return v;
}

Vector Vector::operator - (Vector v)
{
    Vector vv((double)this->data.size());
    if(v.getSize() == this->getSize())
        for(int i = 0; i < this->getSize(); i++ )
        {
            vv.data[i] = this->data[i] - v.data[i];
        }
    else
    {
        cout << "demensions not equals!" << endl;
        return *this;
    }
    return vv;
}

double Vector::operator * (Vector v)
{
    double res = 0;
    if(v.getSize() == this->size)
    {
        for(int i = 0; i < this->size; i++)\
        {
            res = res + (this->data[i] * v.data[i]);
        }
    }
    return res;
}

Vector Vector::operator * (double value)
{
    Vector t((double)data.size());
    for(int i = 0; i < this->size; i++)
        t.data[i] = this->data[i] * value;
    return t;
}

double& Vector::operator[](int i)
{
    if(i < 0 || i > this->size)
    {
        cout << "Invalid index" << endl;
        //return NULL;
    }
    return data[i];
}

