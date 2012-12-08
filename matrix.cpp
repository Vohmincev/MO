#include "matrix.hpp"

Matrix::Matrix(int w, int h)
{
    this->width = w;
    this->height = h;
    this->data = new double*[h];
    for(int i = 0; i < h; i++)
    {
        this->data[i] = new double[w];
        memset(this->data[i], 0, sizeof(double)*w);
    }
};

Matrix::Matrix(int w, int h, double* arr)
{
    this->width  = w;
    this->height = h;
    this->data = new double*[h];
    for(int i = 0; i < h; i++)
        this->data[i] = new double[w];

    for(int i = 0; i < this->height; i++)
        for(int j = 0; j < this->width; j++)
            this->data[i][j] = arr[i*h+j];
}

Matrix::Matrix(int w, int h, double a ...)
{
    this->width = w;
    this->height = h;
    this->data = new double*[h];
    for(int i = 0; i < h; i++)
    {
        this->data[i] = new double[w];
        //memset(this->data[i], 0, sizeof(double)*w);
    }

    va_list p;
    va_start(p,a);
    for( int i=0; i<h; i++ )
    {
        for( int j=0; j<w; j++ )
        {
            this->data[i][j] = a;
            a = va_arg(p, double);
        }
    }
    va_end(p);
}

int Matrix::getHeight()
{
    return this->height;
}

int Matrix::getWidth()
{
    return this->width;
}

double& Matrix::operator()(int i, int j)
{
    return this->data[i][j];
}

Matrix Matrix::operator+(Matrix m)
{
    Matrix res(this->width, this->height);
    if( this->height == m.height && this->width == m.width) // сложение матриц возможно
    {
        for(int i = 0; i < this->height; i++)
            for(int j = 0; j < this->width; j++)
                res.data[i][j] = this->data[i][j] + m.data[i][j];
        return res;
    }
    else cout << "Operation \"+\" is not defined for this matrix" << endl;
}

Matrix Matrix::operator-(Matrix m)
{
    Matrix res(this->width, this->height);
    if( this->height == m.height && this->width == m.width) // сложение матриц возможно
    {
        for(int i = 0; i < this->height; i++)
            for(int j = 0; j < this->width; j++)
                res.data[i][j] = this->data[i][j] - m.data[i][j];
        return (Matrix&)res;
    }
    else
    {
        cout << "Operation \"-\" is not defined for this matrix" << endl;
        return *this;
    }
}

Matrix Matrix::operator*(double d)
{
    Matrix m(this->width, this->height);
    for(int i = 0; i < this->height; i++)
        for(int j = 0; j < this->width; j++)
            m.data[i][j] = this->data[i][j] * d;
    return (Matrix)m;
}

Matrix Matrix::operator*(Matrix m)
{
    if(m.width == m.height && m.height == 1) // если матрица справа от оператора состоит из одного элемента - умножение как на число
    {
        *this = * this * m.data[0][0];
        return (Matrix)*this;
    }

    if( this->height == this->width && this->width == 1 ) //то же самое, только справа
    {
        Matrix res = m;
        *this = ( res = res * this->data[0][0] );
        return (Matrix)res;
    }

    if( this->width == m.height ) // умножение матриц возможно
    {
        Matrix res(m.width, this->height);
        for( int i = 0; i < res.height; i++ )
            for( int j = 0; j < res.width; j++ )
                for( int k = 0; k < this->width; k++ )
                    res.data[i][j] += this->data[i][k] * m.data[k][j];
        return res;
    }
    else
    {
        cout << "Error \"*\" : height must equals width!\n";
        return Matrix();
    }
}

Matrix Matrix::operator/(Matrix m)
{
    if(m.getHeight() == m.getWidth() && m.getWidth() == 1)
        return (*this / m.data[0][0]);
}

Matrix Matrix::operator/(double d)
{
    return (*this * (1.0/double(d)));
}

Matrix Matrix::makeTranspose()
{
    Matrix m( this->height, this->width );
    for( int i=0; i < this->height; i++ )
        for( int j=0; j < this->width; j++ )
            m.data[j][i] = this->data[i][j];
    //*this = m;
    return (Matrix)m;
}

void Matrix::makeIdentity()
{
    if(this->width == this->height)
    {
        for(int i = 0; i < this->height; i++)
            for( int j = 0; j < this->width; j++)
                if(i == j) this->data[i][j] = 1;
                else this->data[i][j] = 0;
    }
}

void Matrix::makeInv()
{
    Matrix result(this->getHeight(), this->getHeight());
    // Изначально результирующая матрица является единичной
    // Заполняем единичную матрицу
    for (int i = 0; i < result.getHeight(); ++i)
    {
        for (int j = 0; j < result.getHeight(); ++j)
            result.data[i][j] = 0.0;

        result.data[i][i] = 1.0;
    }

    // Копия исходной матрицы

    // Проходим по строкам матрицы (назовём их исходными)
    // сверху вниз. На данном этапе происходит прямой ход
    // и исходная матрица превращается в верхнюю треугольную
    for (int k = 0; k < this->getHeight(); ++k)
    {
        // Если элемент на главной диагонали в исходной
        // строке - нуль, то ищем строку, где элемент
        // того же столбца не нулевой, и меняем строки
        // местами
        if (fabs(this->data[k][k]) < 1e-8)
        {
            // Ключ, говорязий о том, что был произведён обмен строк
            bool changed = false;

            // Идём по строкам, расположенным ниже исходной
            for (int i = k + 1; i < result.getHeight(); ++i)
            {
                // Если нашли строку, где в том же столбце
                // имеется ненулевой элемент
                if (fabs(this->data[i][k]) > 1e-8)
                {
                    // Меняем найденную и исходную строки местами
                    // как в исходной матрице, так и в единичной
                    std::swap(this->data[k],   this->data[i]);
                    std::swap(result.data[k], result.data[i]);

                    // Взводим ключ - сообщаем о произведённом обмене строк
                    changed = true;

                    break;
                }
            }

            // Если обмен строк произведён не был - матрица не может быть
            // обращена
            if (!changed)
            {
                cout << "Error! Matrix can not be inverted!\n";
                return;
            }
        }

        // Запоминаем делитель - диагональный элемент
        double div = this->data[k][k];

        // Все элементы исходной строки делим на диагональный
        // элемент как в исходной матрице, так и в единичной
        for (int j = 0; j < result.getHeight(); ++j)
        {
            this->data[k][j]   /= div;
            result.data[k][j] /= div;
        }

        // Идём по строкам, которые расположены ниже исходной
        for (int i = k + 1; i < result.getHeight(); ++i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный под диагональным элементом исходной
            // строки
            double multi = this->data[i][k];

            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < result.getHeight(); ++j)
            {
                this->data[i][j]   -= multi * this->data[k][j];
                result.data[i][j] -= multi * result.data[k][j];
            }
        }
    }

    // Проходим по вернхней треугольной матрице, полученной
    // на прямом ходе, снизу вверх
    // На данном этапе происходит обратный ход, и из исходной
    // матрицы окончательно формируется единичная, а из единичной -
    // обратная
    for (int k = result.getHeight() - 1; k > 0; --k)
    {
        // Идём по строкам, которые расположены выше исходной
        for (int i = k - 1; i + 1 > 0; --i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный над диагональным элементом исходной
            // строки
            double multi = this->data[i][k];

            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < result.getHeight(); ++j)
            {
                this->data[i][j]   -= multi * this->data[k][j];
                result.data[i][j] -= multi * result.data[k][j];
            }
        }
    }
    *this = result;
}

void Matrix::print()
{
    for(int i = 0; i < this->height; i++)
    {
        for(int j = 0; j < this->width; j++)
            cout << this->data[i][j] << " ";
        cout << endl;
    }
}

Matrix::operator Vector&(void) {}

double Matrix::toDouble()
{
    if(this->height == this->width == 1)
        return this->data[0][0];
    else cout << "\n Error matrix is not 1x1 \n";
    return -1;
}
