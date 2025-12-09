#include "../include/matrix.h"
#include <cmath>
#include <stdexcept>

// Dodawanie macierzy A+B
matrix& matrix::operator+(matrix& m) {
    if (rows != m.rows || cols != m.cols)
        throw std::runtime_error("Nieprawidłowe wymiary dla dodawania");
    matrix* result = new matrix(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }
    return *result;
}

// Mnożenie macierzy A*B
matrix& matrix::operator*(matrix& m) {
    if (cols != m.rows)
        throw std::runtime_error("Nieprawidłowe wymiary dla mnożenia");
    matrix* result = new matrix(rows, m.cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result->data[i][j] = 0;
            for(int k = 0; k < cols; k++) {
                result->data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }
    return *result;
}

// Dodaj 'a' do każdego elementu
matrix& matrix::operator+(int a) {
    matrix* result = new matrix(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] + a;
        }
    }
    return *result;
}

// Pomnóż każdy element przez 'a'
matrix& matrix::operator*(int a) {
    matrix* result = new matrix(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] * a;
        }
    }
    return *result;
}

// Odejmij 'a' od każdego elementu
matrix& matrix::operator-(int a) {
    matrix* result = new matrix(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] - a;
        }
    }
    return *result;
}

// int + A
matrix operator+(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a + m.data[i][j];
        }
    }
    return result;
}

// int * A
matrix operator*(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a * m.data[i][j];
        }
    }
    return result;
}

// int - A
matrix operator-(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a - m.data[i][j];
        }
    }
    return result;
}

// A++ (wszystkie elementy +1)
matrix& matrix::operator++(int) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j]++;
        }
    }
    return *this;
}

// A-- (wszystkie elementy -1)
matrix& matrix::operator--(int) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j]--;
        }
    }
    return *this;
}

// Powiększ każdy element o 'a'
matrix& matrix::operator+=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] += a;
        }
    }
    return *this;
}

// Pomniejsz każdy element o 'a'
matrix& matrix::operator-=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] -= a;
        }
    }
    return *this;
}

// Pomnóż każdy element o 'a'
matrix& matrix::operator*=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] *= a;
        }
    }
    return *this;
}

// Dodaj część całkowitą z double do wszystkich elementów
matrix& matrix::operator()(double value) {
    int intPart = static_cast<int>(value);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] += intPart;
        }
    }
    return *this;
}

// Wypisywanie
ostream& operator<<(ostream& o, matrix& m) {
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            o << m.data[i][j];
            if(j < m.cols - 1) o << " ";
        }
        o << endl;
    }
    return o;
}

// Czy każdy element jest równy?
bool matrix::operator==(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] != m.data[i][j]) return false;
        }
    }
    return true;
}

// Czy każdy element jest większy?
bool matrix::operator>(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] <= m.data[i][j]) return false;
        }
    }
    return true;
}

// Czy każdy element jest mniejszy?
bool matrix::operator<(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] >= m.data[i][j]) return false;
        }
    }
    return true;
}