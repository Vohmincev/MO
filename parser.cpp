#include "parser.hpp"

std::vector<std::string> funct = {"sin", "cos", "ln", "exp"};

Parser::Parser()
{
    this->dimension = 0;
    return;
}

Parser::Parser(string ex_in)
{
    stack<string> st;
    stack<int> stfunc;
    string::iterator exIterator = ex_in.begin();
    int f_id, f_len; // id и длинна функции в массиве функций
    this->dimension=0; // количество переменных
    while(exIterator != ex_in.end())
    {
        if(isDigit(*exIterator)) // встретилась ЦИФРА => ревращаем ее в число
        {
            string str;
            int it=0;
            str.resize((it+1)*sizeof(char));
            str[it] = *exIterator;
            //cout << str[it];
            it++;
            exIterator++;
            while(isNumeric(*exIterator))
            {
                str.resize((it+1)*sizeof(char));
                str[it] = *exIterator;
                //cout << str[it];
                it++;
                exIterator++;
            }
            this->out.push_back(ELEM(str)); // положить в выходной массив число
            continue;
        }

        if(*exIterator == '(')
        {
            st.push("(");
            stfunc.push(-1);
            //cout << "DEBUG: '(':" << *exIterator << endl;
            exIterator++;
        }

        if(*exIterator == ')')
        {
            //cout << "DEBUG: ')': " << *exIterator << endl;
            while(st.top() != "(")
            {
                this->out.push_back(ELEM(st.top(),1));
                st.pop();
                if(st.empty())
                {
                    cout << "error";
                }
            }
            st.pop();
            if(!stfunc.empty())
            {
                if( stfunc.top() != -1 )
                {
                    std::stringstream sstr;
                    sstr << stfunc.top();
                    this->out.push_back(ELEM(sstr.str(), 3));
                    stfunc.pop();
                    //cout << "In out vector: " << out.back().data << endl;
                }
            }
            exIterator++;
        }

        if(inArray(*exIterator, "+-/^*")) //знак операции
        {
            string op;
            op = (const char)*exIterator;
            //cout << "DEBUG: op:" << *exIterator << endl;
            while( !st.empty() && (prioritet( *exIterator ) <= prioritet( st.top()[0] )) )
            {
                this->out.push_back(ELEM(st.top(), 1));
                st.pop();
            }
            st.push(op);
            exIterator++;
        }

        if(inFunctions(exIterator, f_id, f_len))
        {
            exIterator += f_len;
            stfunc.push(f_id);
            //cout << "added to stack :" << stfunc.top() << endl;
            if(*exIterator == '(')
            {
                st.push("(");
                exIterator++;
                //cout << "( is here" << endl;
                continue;
            }
            else
            {
                cout << "Fucking syntax error" << endl;
                break;
            }
        }
        if(*exIterator == 'x')
        {
            exIterator++;
            char cache[32] = { 0 };
            while( isDigit(*exIterator) ) // встретили x1 || x2 || etc.
            {
                // магия
                cache[strlen(cache)] = *exIterator;
                this->dimension = (int)max(this->dimension, (*exIterator-48));
                exIterator++;
            }
            this->out.push_back(ELEM(cache, 2));
            continue;
        }
    }

    while(!st.empty())
    {
        this->out.push_back( ELEM(st.top(), 1) );
        st.pop();
    }
}



double Parser::execute(double x)
{
    if(this->dimension > 1)
    {
        cout << "need more arguments";
        return 0;
    }
    vector<double> xt;
    xt.push_back(x);
    return this->execute(xt);
}

double Parser::execute(vector<double> x)
{
    stack<string> st;
    double d=0.0;
    double res=0.0;
    vector<ELEM>::iterator it = this->out.begin();
    while(it != this->out.end() )
    {
        if( (*it).getType() == 0 ) // число
        {
            st.push((*it).data);
            it++;
            //ps(st); cout << endl;
            continue;
        }

        if( (*it).type == 1)
        {
            double first=0, second=0;
            if (st.size() >=2)
            {
                first = atof(st.top().c_str());
                st.pop();
                second = atof(st.top().c_str());
                st.pop();
            }
            else
            {
                cout << "Fucking error" << endl;
            }
            if((*it).data == "+")
            {
                res = second + first;
                std::ostringstream strs;
                strs << res;
                st.push(strs.str());
                it++;
                continue;
            }

            if((*it).data == "-")
            {
                res = second - first;
                std::ostringstream strs;
                strs << res;
                st.push(strs.str());
                //ps(st);
                it++;
                continue;
            }

            if((*it).data == "*")
            {
                res = second * first;
                std::ostringstream strs;
                strs << res;
                st.push(strs.str());
                //ps(st);
                it++;
                continue;
            }

            if((*it).data == "/")
            {
                res = second / first;
                std::ostringstream strs;
                strs << res;
                st.push(strs.str());
                //ps(st);
                it++;
                continue;
            }

            if((*it).data == "^")
            {
                res = pow(second, first);
                std::ostringstream strs;
                strs << res;
                st.push(strs.str());
                //ps(st);
                it++;
                continue;
            }
            it++;
        }


        if((*it).type == 2) // vars
        {
            int t = atoi((*it).data.c_str()) - 1;
            std::ostringstream strs;
            strs << x[t];
            st.push(strs.str());
            it++;
            continue;
        }


        if((*it).type == 3) // function
        {
            if( st.size() >= 1 )
            {
                d = atof(st.top().c_str());
                st.pop();
            }
            if((*it).data == "0") //sin
            {
                std::ostringstream strs;
                strs << sin(d);
                st.push(strs.str());
                it++;
                continue;
            }

            if((*it).data == "1") //cos
            {
                std::ostringstream strs;
                strs << cos(d);
                st.push(strs.str());
                it++;
                continue;
            }

            if((*it).data == "2") //ln
            {
                std::ostringstream strs; // приведение
                strs << log(d);     // к
                st.push(strs.str());// string
                //cout << "st ln: ";ps(st);
                it++;
                continue;
            }

            if((*it).data == "3") //exp
            {
                std::ostringstream strs;
                strs << exp(d);
                st.push(strs.str());
                //cout << "st exp: "; ps(st);
                it++;
                continue;
            }
        }
    }
    //cout << "st.top: " << st.top() << endl;
    if(res == 0) return atof(st.top().c_str());
    else return res;
}

bool Parser::inArray(const char c, string arr)
{
    for(unsigned int i = 0; i < arr.size(); i++)
        if(c == arr[i]) return true;
    return false;
}

bool Parser::isDigit(const char c)
{
    return inArray(c, "0123456789");
}

bool Parser::isNumeric(const char c)
{
    return (isDigit(c) || c =='.');
}

/*bool Parser::isSpace(const char c)
{
    return c == ' ';
}*/

bool Parser::inFunctions(string::iterator it, int& id, int& len)
{
    string str("");
    int j=0;
    while(*it != '(')
    {
        //cout << "iterator: " << *it << endl;
        //system("pause");
        str.resize((j+1)*sizeof(char));
        str[j] = *it;
        it++;
        j++;
        if(j>4) break;
    }
    for( unsigned int i=0; i<funct.size(); i++ )
    {
        if( !strncmp(str.c_str(), funct[i].c_str(), funct.size()) )
        {
            //cout << "I found it! id = " << i << endl;
            id = i;
            len = funct[i].size();
            return true;
        }
    }
    return false;
}

int Parser::prioritet(const char c) //приоритеты операций
{
    switch(c)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return -1;
    }
}

double Parser::max(double a, double b)
{
    return a < b ? b : a;
}

int Parser::getDimension()
{
    //cout << "dimension " << dimension << endl;
    return this->dimension;
}
