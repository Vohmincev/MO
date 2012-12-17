#include <iostream>
#include <windows.h>
#include "methods.hpp"

#include <sstream>


// -std=c++0x is required

using namespace std;

int main()
{
    cout.precision(10);
    //cout << stdv[0] << " " << stdv[1] << endl;
    //cout << "Norm = " << m.getNorm();*/
    int k;
    int d, act;
    Vector start_x, x;
    string f1("100*(x2-x1^2)^2+(1-x1)^2"); //!
    string f2("(x1-1)^2+(x2-3)^2+4*(x3+5)^2"); //!
    string f3("8*x1^2+4*x1*x2+5*x2^2"); //!
    string f4("4*(x1-5)^2+(x2-6)^2"); //!
    string f6("(x2-x1*x1)^2+100*(1-x1*x1)^2"); //!
    string f7("3*(x1-4)^2+5*(x2+3)^2+7*(2*x3+1)^2"); //!
    string f8("(x1-2)^4+(x1-2*x2)^2");
    string f9("(x1+10*x2)^2+5*(x3-x4)^2+(x2-2*x3)^4+10*(x1-x4)^4");

    string f1_("(1.5-x1*(1-x2))^2+(2.25-x1*(1-x2^2))^2+(2.625-x1*(1-x2^3))^2"); //
    string f2_("(x1+10*x2)^2+5*(x3-x4)^2+(x2-2*x3)^4+10*(x1-x4)^4"); //
    string f3_("(x1^2+x2-11)^2+(x1+x2^2-7)^2"); //!
    string f4_("(x1-10*x2)^2+5*(x3-x4)^2+(x2-2*x3)^4+10*(x1-x4)^4"); //!
    string f5_("0.1*(12+x1^2+(1+x2^2)/x1^2+(x1^2*x2^2+100)/(x1^4*x2^4))"); //!
    string f6_("(x1-2)^2+(x2-1)^2+0.04/((0-0.25)*x1^2-x2^2+1)+5*(x1-2*x2+1)^2"); //!
    string f7_("100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2+(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)"); //!
    string f8_("100*(x2-x1^2)^2+(1-x1)^2"); //!
    string f9_("(0-12)*x2+4*x1^2+4*x2^2-4*x1*x2");
    string ff("(0-1)*12*x2+4*x1^2+4*x2^2-4*x1*x2");
    string kr("2*x1^2+2*x2^2-x1*x2+x1+10");

    /*start_x.setValue(2, 8.0, 9.0);
    //x = Methods(f1, start_x).CCD(start_x, k);
    //cout << "DFP method: "; x.print(); cout << "k = " << k << endl << endl;

    start_x.setValue(2, 1.5, 1.5);
    Vector xx = Methods(f1, start_x).DFP(start_x, k);
    cout << "Partan2 method: \n"; xx.print(); cout << "k = " << k << endl;

    start_x.setValue(4, -3.0, -1.0, -3.0, -1.0);
    //Vector xx = Methods(f9, start_x).DFP(start_x, k);
    //cout << "DFP method: "; xx.print(); cout << "k = " << k << endl;
    */

    string method("CCD");
    while(1)
    {
        cout << "Choose action:" << endl <<
             "1. Demo functions" << endl <<
             "2. Enter function" << endl <<
             "0. Quit" << endl << endl;

        cout << "Enter action: ";
        cin >> act;
        switch(act)
        {
        case 1:

            system("cls");
            cout << "Choose the function:" << endl << endl <<
                 "1. (1.5 - x1*(1-x2))^2 + (2.25 - x1*(1-x2^2))^2 + (2.625 - x1*(1-x2^3))^2" << endl << endl <<
                 "2. (x1+10*x2)^2+5*(x3-x4)^2+(x2-2*x3)^4+10*(x1-x4)^4" << endl << endl <<
                 "3. (x1^2 + x2 - 11)^2 + (x1 + x2^2 - 7)^2" << endl << endl <<
                 "4. (x1 - 10*x2)^2 + 5*(x3-x4)^2 + (x2 - 2*x3)^4 + 10*(x1-x4)^4" << endl << endl <<
                 "5. 0.1*(12 + x1^2 + (1+x2^2)/x1^2 + (x1^2*x2^2 + 100)/(x1^4 * x2^4))" << endl << endl <<
                 "6. (x1 - 2)^2 + (x2 - 1)^2 + 0.04/(0.25*x1^2 - x2^2 + 1) + 5*(x1 - 2*x2 + 1)^2" << endl << endl <<
                 "7. 100*(x2-x1^2)^2+(1-x1)^2+90*(x4-x3^2)^2+(1-x3)^3+10.1*((x2-1)^2+(x4-1)^2)+19.8*(x2-1)*(x4-1)" << endl << endl <<
                 "8. 100*(x2 - x1^2)^2 + (1 - x1)^2" << endl << endl;

            cout << "Enter number: ";
            cin >> d;
            cout << "\nEnter method(CCD, Partan2, FR, DFP): ";
            cin >> method;

            switch(d)
            {
            case 1:
                start_x.setValue(2, 1.5, 2.0);
                x = Methods(f1_, start_x).findMinimum(method, f1_, start_x, k);
                break;
            case 2:
                start_x.setValue(4, -3.0, -1.0, 0.0, -1.0);
                x = Methods(f2_, start_x).findMinimum(method, f2_, start_x, k);
                break;
            case 3:
                start_x.setValue(2, 1.5, 2.0);
                x = Methods(f3_, start_x).findMinimum(method, f3_, start_x, k);
                break;
            case 4:
                //start_x.setValue(4, 1.5, 2.0, 3.4, 2.1);
                start_x.setValue(2, 8.0, 9.0);
                x = Methods(f4, start_x).findMinimum(method, f4, start_x, k);
                break;
            case 5:
                start_x.setValue(2, 0.5, 0.5);
                x = Methods(f5_, start_x).findMinimum(method, f5_, start_x, k);
                break;
            case 6:
                start_x.setValue(2, 1.5, 2.0);
                x = Methods(f6_, start_x).findMinimum(method, f6_, start_x, k);
                break;
            case 7:
                start_x.setValue(4, 1.5, 2.0, 2.1, 3.5);
                x = Methods(f7_, start_x).findMinimum(method, f7_, start_x, k);
                break;
            case 8:
                start_x.setValue(2, 1.5, 2.0);
                x = Methods(f8_, start_x).findMinimum(method, f8_, start_x, k);
                break;
            case 9:
               //start_x.setValue(2, 0.0, 0.0);
                start_x.setValue(2, 1.0, 0.0);
                x = Methods(f9_, start_x).findMinimum(method, f9_, start_x, k);
                break;
            case 0:
                return 0;
            }
            cout << endl << method <<" result: ";
            x.print();
            cout << "k = " << k << endl << endl;
            system("pause");
            system("cls");
            break;

        case 2:
            x = Methods().getFunction();
            cout << endl << "Result: min = ";
            x.print();
            system("pause");
            system("cls");
            break;

        case 0:
            return 0;
        }
    }
    return 0;
}
