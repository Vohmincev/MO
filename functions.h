#include <cmath>
#define EPSILON pow(10,-6)

double y(double alpha);
double dy(double alpha);

double min( double a, double b )
{
    return a > b ? b : a;
}

double max( double a, double b )
{
    return a < b ? b : a;
}

int swann(double x, double &a, double &b)
{
    int k;
    a=0; b=0;
    double h=0.0001;
    if( y(x) < y(x+h) ) // установление направления убывания функции
        h = -h;

    for( k=0; y(x+h) < y(x); k++ )
    {
        h *= 2;
        x += h;
    }
    a = min(x-h,x+h);
    b = max(x-h,x+h);
    return k;
}

int swann2(double x, double &a, double &b)
{
    int k;
    double h=0.01;
    if(dy(x)>0) h=-h;
    for( k=0; dy(x+h)*dy(x)>0; k++ )
    {
        h *= 2;
        x += h;
    }
    a = min(x-h,x+h);
    b = max(x-h,x+h);
    return k;
}

int swann3(double x, double &a, double &b, double &c, double d)
{
    double h=0.01;
    double mu, la;
    int k=0;
    if(d!=0) x=d;
    if (y(x+h)>y(x))
        h=-h;
    while(y(x+h) < y(x))
    {
        x=x+h;
        k++;
    }
    mu=(x+x+h)/2;
    la=x-0.5*h;
    if(y(x)<y(mu))
    {
        b=x;
        if(la<mu)
        {
            a=la;
            c=mu;
        }
        else
        {
            a=mu;
            c=la;
        }
    }
    else
    {
        b=mu;
        if(x<x+h)
        {
            a=x;
            c=x+h;
        }
        else
        {
            a=x+h;
            c=x;
        }
    }
    return k;
}


double DSK(double a, double b)
{
    double x=0, h=0.01, c=0, d=0;
    int k=0;
    double min;
    do
    {
        swann3(x,a,b,c,d);
        d = b+(0.5*(b-a)*(y(a)-y(c)))/(y(a)-2*y(b)+y(c));
        if ( (b-d)/b <=EPSILON && (y(b)-y(d))/y(b)<=EPSILON )
        {
            min=(b+d)/2;
            break;
        }
        else
        {
            if (y(b)<y(d))
                x=b;
            else
                x=d;
            h=h/2;
        }
        k++;
    }
    while(1);
    return min;
}

double davidon(double a, double b)
{
    double z=dy(a)+dy(b)+(3*(y(a)-y(b)))/(b-a);
    double w=pow(z*z-dy(a)*dy(b),0.5);
    double Y=(z-dy(a)+w)/(dy(b)-dy(a)+2*w);
    double d=a+Y*(b-a);
    double x=d;
    int k=0;
    while(dy(x)>EPSILON)
    {
        if(dy(d)>0) b=d;
        else a=d;
        z=dy(a)+dy(b)+(3*(y(a)-y(b)))/(b-a);
        w=pow(z*z-dy(a)*dy(b),0.5);
        Y=(z-dy(a)+w)/(dy(b)-dy(a)+2*w);
        d=a+Y*(b-a);
        k++;
    }
    return x=(a+b)/2;
}

double bolcano(double &a, double &b, int m)
{
    double x=(a+b)/2;
    int k=0;
    while(1)
    {
        if(m && k == 5) return 0;
        if(fabs(dy(x))<=EPSILON && fabs(b-a)<=EPSILON) break;
        x=(a+b)/2;
        if(dy(x)>0) b=x;
        else a=x;
        k++;
    }
    return x;
}

double ex_in(double a, double b, int &k)
{
    double c, h=0.0001, d;
    k=0;
    b=(a+b)/2;
    a=b-h;
    c=b+h;
    while(1)
    {
        d = (a+b)/2+(0.5*pow(y(a)-y(b),2)*(b-c)*(c-a))/(2*(b-a)*(y(b)-y(c))-(b-c)*(y(b)-y(a)));
        if(fabs((b-d)/b)<=EPSILON && fabs((y(b)-y(d))/y(b))<=EPSILON) return d;
        else b=d;
        k++;
    }
}
