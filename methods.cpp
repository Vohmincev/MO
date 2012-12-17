#include "methods.hpp"

Methods::Methods(string expression, Vector x)
{
    parser = Parser(expression);
    if(x.getSize() != parser.getDimension()) // количество введенных значений не совпадает с количеством переменных
    {
        cout << "Size of value vector != dimension of function!\n";
    }
    this->xt = x;
    this->pt.setSize(x.getSize()); //= Vector((double)x.getSize());
}

double Methods::f(Vector x)
{
    return parser.execute(x.getSTLvector());
}

double Methods::y(double alpha)
{
    Vector x;
    x.setSize(xt.getSize());
    x = this->xt + (this->pt * alpha);
    return f(x);
}

double Methods::dy(double alpha)
{
    double h = /*max(pow(10,-7), pow(10,-5)*fabs(alpha));*/ 0.0005;
    //return (y(alpha+h)-y(alpha-h))/(2.0*h);
    return (-y(alpha+2.0*h)+8.0*y(alpha+h)-8.0*y(alpha-h)+y(alpha-2.0*h))/(12.0*h);
}

double Methods::dy(int i, Vector x)
{
    double h = /*max(pow(10,-5), 0.000001*fabs(x[i]));*/ 0.00001;
    Vector e;
    e.setSize(x.getSize());
    e[i] = 1;
    return (-f(x + (e*(2.0*h)) )+8.0*f(x + (e*h) )-8.0*f(x - (e*h) )+f( x - (e*(2.0*h)) ))/(12.0*h);
}

Vector Methods::gradient(Vector x)
{
    Vector y(x.getSize());
    for(int i = 0; i < x.getSize(); i++)
    {
        y[i] = dy(i, x);
    }
    return y;
}

double Methods::Differential(Vector idx, Vector x0, int _ord = 0, double h = 0.0005 )
{
    Vector x1(x0.getSize());
    Vector x2(x0.getSize());
    x1 = x0;
    x2 = x0;
    /*if(idx[0] == idx[1])
    {
        Vector e(2, 1.0, 1.0);
        return (f(x0 + e*h*2) - 2*f(x0 + e*h) +f(x0) ) / (h*h);
    }*/
    x1[idx[_ord]] += h;
    x2[idx[_ord]] -= h;
    if( idx.getSize() == _ord+1 )
    {
        return ( f( x1 ) - f( x2 ) ) / (2 * h); // Get fuckin' central again
    }
    else
        return ( this->Differential( idx, x1, _ord+1 ) - this->Differential( idx, x2, _ord+1 ) ) / (2 * h);
}

Matrix Methods::gess(Vector x)
{
    double h = 0.0005;
    int n = x.getSize();
    Matrix H(n, n);
    double curValue = f(x);
    double fPlus[n];
    double fMinus[n];
    Vector ort1(n), ort2(n);
    for(int i = 0; i < n; i++)
    {
        ort1.setZero();
        ort1[i] = 1;
        //vec = x + (ort1 * h);
        fPlus[i] = f(x + (ort1 * h));
        fMinus[i] = f(x - (ort1 * h));
        H(i, i) = (fPlus[i] - 2 * curValue + fMinus[i]) / (h * h);
    }

    for (int i = 0; i < n; i++)
        //Так как гессиан симметричен, вычисляем только его половину
        for (int j = i + 1; j < n; j++)
        {
            ort1.setZero();
            ort2.setZero();
            ort1[i] = 1;
            ort2[j] = 1;
            double xx = f(x + (ort1 + ort2) * h);
            H(i, j) = (xx - fPlus[i] - fPlus[j] + f(x)) / (h * h);
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            H(i, j) = H(j, i);
    return H;
}

double Methods::min( double a, double b )
{
    return a > b ? b : a;
}

double Methods::max( double a, double b )
{
    return a < b ? b : a;
}

Vector Methods::getFunction()
{
    string function;
    string method;
    Vector start_x;
    Vector min;
    int k;
    cout << "Enter function: ";
    std::cin >> function;
    this->parser = Parser(function);
    start_x.setSize(parser.getDimension());
    cout << endl << "Enter start point:" << endl;
    for(int i = 0; i < parser.getDimension(); i++)
    {
        cout << "Value: ";
        std::cin >> start_x[i];
    }
    cout << endl << "Enter method: ";
    std::cin >> method;
    return Methods(function, start_x).findMinimum(method, function, start_x, k);
}

Vector Methods::findMinimum(string method, string expression, Vector start_x, int& k)
{
    std::map<string, Callback> map;
    map["Partan2"] = &Methods::Partan2;
    map["CCD"] = &Methods::CCD;
    map["DFP"] = &Methods::DFP;
    map["FR"] = &Methods::FR;
    map["Newton"] = &Methods::Newton;
    map["p"] = &Methods::Powell;
    //map["з"] = &Methods::Powell;
    Callback function = map[method];
    return (this->*function)(start_x, k);
}


void Methods::swann(double x, double &a, double &b)
{
    a=0;
    b=0;
    double h=0.001;
    if( y(x) < y(x+h) ) // установление направления убывания функции
        h = -h;

    for(int k=0; y(x+h) < y(x); k++ )
    {
        h *= 2;
        x += h;
    }
    a = min(x-h, x+h);
    b = max(x-h, x+h);
}

void Methods::swann2(double x, double &a, double &b)
{
    double h=0.001;
    if(dy(x)>0) h=-h;
    for(int k=0; dy(x+h)*dy(x)>0; k++ )
    {
        h *= 2;
        x += h;
    }
    a = min(x-h, x+h);
    b = max(x-h, x+h);
}

double Methods::dichotomy(double &a, double &b)
{
    double d=EPSILON;
    double a1,b1;
    int k=0;
    while(k <5)
    {
        a1=(a+b-d)/2;
        b1=(a+b+d)/2;
        if(y(a1) < y(b1)) b=b1;
        else a=a1;
        k++;
    }
    return((a+b)/2);
}

double Methods::bolcano(double &a, double &b, int m)
{
    double x;
    int k=0;
    while(1)
    {
        x=(a + b) / double(2);
        if(m && k == 4) return x;
        if( ( fabs(dy(x) ) <= EPSILON ) && ( fabs(b - a) <= EPSILON ) ) break;
        if(dy(x) > 0) b=x;
        else a=x;
        k++;
    }
    return x;
}

double Methods::davidon()
{
    double a=0.0, b=0.0;
    return this->davidon(a,b);
}

double Methods::davidon(double a, double b)
{
    double x;
    this->swann(0.0, a, b);
    x = this->bolcano(a, b, 1);
    double z=dy(a)+dy(b)+(double(3)*(y(a)-y(b)))/(b-a);
    double w=pow(z*z-dy(a)*dy(b),0.5);
    double Y=(z-dy(a)+w)/(dy(b)-dy(a)+double(2)*w);
    if( (Y>0) && (Y<1) ) x=a+Y*(b-a);
    else if(Y<0) x = a;
    else if(Y>0) x = b;
    int k=0;
    while(1)
    {
        if(dy(x) <= EPSILON || x == a || x == b) break;
        if(dy(x)>0) b=x;
        else a=x;

        z=dy(a)+dy(b)+(double(3)*(y(a)-y(b)))/(b-a);
        w=pow(z*z-dy(a)*dy(b),0.5);
        Y=(z-dy(a)+w)/(dy(b)-dy(a)+double(2)*w);

        if( (Y>0) && (Y<1) ) x=a+Y*(b-a);
        else if(Y<0) x = a;
        else if(Y>0) x = b;
        k++;
    }
    return x;
}

Vector Methods::CCD(Vector start, int& k)
{
    double alpha;
    int n = start.getSize();
    Vector zeros(n);
    Vector last(n);
    xt = start;
    k = 0;
    while(1)
    {
        last = this->xt;
        zeros.setZero();
        pt = zeros;
        pt[k % n] = 1;
        alpha = this->davidon();
        this->xt = this->xt + this->pt * alpha;
        k++;

        if(k%100==0)
        {
            cout << "calculating...   k=" << k << endl;
        };

        if(this->gradient(xt).getNorm() <= EPSILON)
        {
            break;
        }
    }
    return this->xt;
}

Vector Methods::Partan2(Vector start, int& k)
{
    double alpha;
    Vector d(xt.getSize());
    Vector x(xt.getSize());
    k = 1;
    xt = start;
    pt = (this->gradient(xt) * (-1));
    alpha = this->davidon();
    this->xt = this->xt + this->pt * alpha;
    while(1)
    {
        pt = (this->gradient(xt) * (-1));
        alpha = this->davidon();
        this->xt = this->xt + this->pt * alpha;
        d = this->xt - start;
        alpha = davidon();
        this->xt = this->xt + d * alpha;
        if(d.getNorm() <= EPSILON) break;
        else start = xt;
        cout << "x = ";
        xt.print();
        //cout << "\nKOP = " << d.getNorm() << endl;
        k++;
        //system("pause");
    }
    return xt;
}

Vector Methods::FR(Vector start, int& k)
{
    double alpha;
    int n = start.getSize();
    k = 1;
    int c = 0;
    Vector x_last = start;
    Vector grad_curr;
    Vector grad_last = gradient(x_last);
    pt.setValue(2, 0.0, 0.0);
    while(1)
    {
        Vector grad_curr = this->gradient(xt);
        if(k == c*n+1)
        {
            //cout << "k = " << k << endl;
            pt = grad_curr * (-1);
            c++;
        }
        else
        {
            //cout << "k = " << k << endl;
            //cout << "gradient = "; grad_curr.print();
            Vector b = (grad_curr.makeTranspose() * grad_curr) / (grad_last.makeTranspose() * grad_last);
            double beta = b.toDouble();
            pt = grad_curr * (-1) + pt * beta;
            //cout << "p = "; pt.print(); cout << "beta = " << beta << endl;
        }
        grad_last = grad_curr;
        x_last = xt;
        alpha = this->davidon();
        this->xt = this->xt + this->pt * alpha;
        k++;
        cout << "x = ";
        xt.print();
        //if(this->gradient(xt).getNorm() <= EPSILON) break;
        if((xt - x_last).getNorm() <= EPSILON ) break;
    }
    return xt;
}

Vector Methods::DFP(Vector start_x, int& k)
{
    xt = start_x;
    int n = start_x.getSize();
    Vector x_last(n);
    Matrix A(n, n);
    Matrix E(n, n);
    E.makeIdentity();
    A.makeIdentity();
    //pt.setZero();
    double alpha;
    k = 1;
    int c = 0;
    while(1)
    {
        if( k == c*n+1 )
        {
            A.makeIdentity();
            c++;
        }
        else
        {
            Vector dx = xt - x_last;
            Vector g = this->gradient(xt) - this->gradient(x_last);
            //cout << "dg = "; g.print();
            Matrix s = A * g;

            //cout << "dx = "; dx.print();
            //cout << "\ng = "; g.print();
            //cout << "\ns = "; s.print();

            // Формула Бройдена-Флетчера-Шено
            //Matrix B = E - ( dx * g.makeTranspose()) / (g.makeTranspose() * dx);
            //A = B*A*B + ( ( dx * dx.makeTranspose() ) / (dx.makeTranspose() * g) );

            //Формула Дэвидона-Флетчера-Пауэлла (ДФП)
            A = A + ( ( dx * dx.makeTranspose() ) / (dx.makeTranspose() * g) ) - ( ( s * s.makeTranspose() ) / ( s.makeTranspose() * g ) );

            //cout << "\nmatr1 = "; ( ( dx * dx.makeTranspose() ) / (dx.makeTranspose() * g) ).print();
            //cout << "matr2 = "; ( ( s * s.makeTranspose() ) / ( s.makeTranspose() * g ) ).print();
            //cout << endl;

            //Формула Пирсона-2
            //A = A + ( (dx - s) * (dx.makeTranspose()) ) / ( g.makeTranspose() * s );

            // формула Бройдена-Флетчера-Гольдфабра-Шенно
            //A = A + (( 1 + (s.makeTranspose() * g) / (g.makeTranspose() * dx) ) * ( (dx * dx.makeTranspose())/(dx.makeTranspose * g) )) - (dx*s.makeTranspose() + s*dx.makeTranspose()) / (dx.makeTranspose() * g);
        }
        x_last = xt;
        //cout << "A" << k << "= \n"; A.print();
        //cout << "gradient = "; this->gradient(xt).print();
        //cout << "gradient last = "; this->gradient(x_last).print();
        pt = (A * (-1.0) * this->gradient(xt));
        pt = pt / pt.getNorm();
        alpha = davidon();
        //cout << "alpha = "<< alpha << endl;
        xt = xt + pt * alpha;
        cout << "x = ";
        xt.print();
        //cout << "last = "; x_last.print();
        //cout << "pt = "; pt.print();
        //cout << "KOP: " << this->gradient(xt).getNorm() << endl;
        //system("pause");
        k++;
        if((xt - x_last).getNorm() <= EPSILON) break;
        //if(this->gradient(xt).getNorm() <= EPSILON) break;
    }
    return xt;
}

Vector Methods::Newton(Vector start_x, int& k)
{
    xt = start_x;
    Vector xlast = start_x;
    int n = start_x.getSize();
    Matrix H(n, n);
    double alpha;
    k = 1;
    while(1)
    {
        H = this->gess(xt);
        H.print();
        //system("pause");
        H.makeInv();
        cout << "H inverted = \n";
        H.print();
        //system("pause");
        pt = (H * gradient(xt)) * (-1);
        alpha = davidon();
        xlast = xt;
        xt = xt + pt * alpha;
        cout << "xt = "; xt.print();
        k++;
        //if(gradient(xt).getNorm() <= EPSILON) break;
        if((xt - xlast).getNorm() <= EPSILON) break;
        cout << "KOP = " << (xt - xlast).getNorm() << endl;
        system("pause");
    }
    return xt;
}

Vector Methods::Powell(Vector start_x, int& k)
{
    k = 1;
    int n = start_x.getSize();
    xt = start_x;
    Vector x_last(n);
    //формирование массива ортов
    Vector* pi[n];
    Vector d(n);
    double A[n];
    double M[n];
    double alpha;
    for(int i = 0; i < n; i++)
    {
        pi[i] = new Vector(n);
        pi[i]->setValue(i,1);
        //cout << " pi["<<i<<" = "; pi[i]->print();
    }
    //pi[n] = new Vector(n);
    //pi[n]->setValue(0,1);
while(1) {
    for(int i = 0; i < n; i++) //система одномерных поисков вдоль направлений pi
    {
        x_last = xt;
        alpha = davidon();
        xt = xt + *pi[i] * alpha;
        A[i] = alpha;
        M[i] = f(x_last) - f(xt);
        //cout << "M["<<i<<"] = " << M[i] << endl;
    }
    //alpha = davidon();
    //xt = xt + *pi[0] * alpha;
    x_last = xt;
    d = xt - start_x;
    //cout << "d = "; d.print();
    alpha = davidon();
    xt = xt + d*alpha;
    //alpha = davidon();
    //cout << "KOP: " << d.getNorm() << endl;
    if( (alpha <= EPSILON) && (fabs( (f(x_last) - f(start_x))/f(x_last) ) <=EPSILON) ) return xt;
    int max = maxArr(A, n);
    pt = *pi[max];
    if(4*M[max]*(f(x_last)-f(xt)) >= pow((f(start_x)-f(x_last)-M[max]),2))
    {
        //pt = d/d.getNorm();
        //*pi[0] = ;
        cout << "Imma here!" << endl;
        d = d/d.getNorm();
        //for(int i = 1; i <= n; i++)
        //{
            //cout << "Imma here!2" << endl;
            //*pi[i] = *pi[i-1];
        //}
        *pi[n-1] = d;
        //*pi[max] = d;
    }
    k++;
    start_x = xt;
    cout << "xt = "; xt.print();
}


    return Vector(2);
}

int Methods::maxArr(double *arr, int size)
{
    int i = 0;
    int max = i;
    for(int i = 1; i < size; i++)
    {
        if(arr[i]>arr[max]) max = i;
    }
    return max;
}
