#include "../include/matrix.h"
#include <cmath>
#include <stdexcept>

/**
 * @brief Operator dodawania macierzy - A + B
 * 
 * Dodaje dwie macierze tego samego rozmiaru, zwracając nową macierz
 * zawierającą sumę elementów. Operacja odbywa się element po elemencie.
 * 
 * @param m macierz do dodania (prawy operand)
 * 
 * @return referencja na nową macierz zawierającą sumę A + B
 * 
 * @throw std::runtime_error jeśli wymiary macierzy nie są zgodne
 *        (rows lub cols się różnią)
 * 
 * @pre this->rows == m.rows && this->cols == m.cols
 * @post wynikowa macierz[i][j] = this[i][j] + m[i][j]
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2);
 * A(0, 0) = 1; A(0, 1) = 2;
 * A(1, 0) = 3; A(1, 1) = 4;
 * 
 * matrix B(2, 2);
 * B(0, 0) = 5; B(0, 1) = 6;
 * B(1, 0) = 7; B(1, 1) = 8;
 * 
 * matrix C = A + B;  // C[0][0] = 6, C[0][1] = 8, ...
 * @endcode
 * 
 * @warning Używa `release()` na unique_ptr - być ostrożnym z zarządzaniem pamięcią!
 */
matrix& matrix::operator+(matrix& m) {
    if (rows != m.rows || cols != m.cols)
        throw std::runtime_error("Nieprawidłowe wymiary dla dodawania");
    auto result = std::make_unique<matrix>(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }
    return *result.release();
}

/**
 * @brief Operator mnożenia macierzy - A * B
 * 
 * Mnoży dwie macierze według reguł mnożenia macierzy.
 * Wynikowa macierz ma wymiary (rows × m.cols).
 * Liczba kolumn macierzy A musi równać się liczbie wierszy macierzy B.
 * 
 * @param m macierz mnożnika (prawy operand)
 * 
 * @return referencja na nową macierz zawierającą iloczyn A * B
 * 
 * @throw std::runtime_error jeśli this->cols != m.rows
 * 
 * @pre this->cols == m.rows
 * @post wynikowa macierz[i][j] = Σ(this[i][k] × m[k][j]) dla k=0..cols-1
 * @complexity O(n × m × p) gdzie n = this->rows, m = this->cols, p = m.cols
 * 
 * @example
 * @code
 * matrix A(2, 3);  // macierz 2×3
 * matrix B(3, 2);  // macierz 3×2
 * matrix C = A * B;  // wynik 2×2
 * @endcode
 * 
 * @note Mnożenie macierzy nie jest przemienne: A*B ≠ B*A
 * @warning Używa `release()` na unique_ptr - być ostrożnym z zarządzaniem pamięcią!
 */
matrix& matrix::operator*(matrix& m) {
    if (cols != m.rows)
        throw std::runtime_error("Nieprawidłowe wymiary dla mnożenia");
    auto result = std::make_unique<matrix>(rows, m.cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result->data[i][j] = 0;
            for(int k = 0; k < cols; k++) {
                result->data[i][j] += this->data[i][k] * m.data[k][j];
            }
        }
    }
    return *result.release();
}

/**
 * @brief Operator dodawania skalara - A + a
 * 
 * Dodaje skalar `a` do każdego elementu macierzy.
 * Zwraca nową macierz tego samego rozmiaru.
 * 
 * @param a skalar do dodania do każdego elementu
 * 
 * @return referencja na nową macierz zawierającą wynik
 * 
 * @post wynikowa macierz[i][j] = this[i][j] + a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);  // wszystkie elementy = 1.0
 * matrix B = A + 5;     // wszystkie elementy = 6.0
 * @endcode
 */
matrix& matrix::operator+(int a) {
    auto result = std::make_unique<matrix>(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] + a;
        }
    }
    return *result.release();
}

/**
 * @brief Operator mnożenia przez skalar - A * a
 * 
 * Mnoży każdy element macierzy przez skalar `a`.
 * Zwraca nową macierz tego samego rozmiaru.
 * 
 * @param a skalar mnożnika
 * 
 * @return referencja na nową macierz zawierającą wynik
 * 
 * @post wynikowa macierz[i][j] = this[i][j] * a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 2.0);
 * matrix B = A * 3;  // wszystkie elementy mnożone przez 3
 * @endcode
 */
matrix& matrix::operator*(int a) {
    auto result = std::make_unique<matrix>(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] * a;
        }
    }
    return *result.release();
}

/**
 * @brief Operator odejmowania skalara - A - a
 * 
 * Odejmuje skalar `a` od każdego elementu macierzy.
 * Zwraca nową macierz tego samego rozmiaru.
 * 
 * @param a skalar do odjęcia od każdego elementu
 * 
 * @return referencja na nową macierz zawierającą wynik
 * 
 * @post wynikowa macierz[i][j] = this[i][j] - a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 10.0);
 * matrix B = A - 3;  // wszystkie elementy zmniejszone o 3
 * @endcode
 */
matrix& matrix::operator-(int a) {
    auto result = std::make_unique<matrix>(rows, cols);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            result->data[i][j] = this->data[i][j] - a;
        }
    }
    return *result.release();
}

/**
 * @brief Friend operator dodawania skalara - a + A
 * 
 * Dodaje skalar `a` do każdego elementu macierzy `m`.
 * Operacja jest przemienna: a + A = A + a
 * 
 * @param a skalar (lewy operand)
 * @param m macierz (prawy operand)
 * 
 * @return nowa macierz zawierająca wynik a + m
 * 
 * @post wynikowa macierz[i][j] = a + m[i][j]
 * @complexity O(n × m) gdzie n = m.rows, m = m.cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * matrix B = 5 + A;  // równoważne A + 5
 * @endcode
 */
matrix operator+(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a + m.data[i][j];
        }
    }
    return result;
}

/**
 * @brief Friend operator mnożenia skalara - a * A
 * 
 * Mnoży każdy element macierzy `m` przez skalar `a`.
 * Operacja jest przemienna: a * A = A * a
 * 
 * @param a skalar (lewy operand)
 * @param m macierz (prawy operand)
 * 
 * @return nowa macierz zawierająca wynik a * m
 * 
 * @post wynikowa macierz[i][j] = a * m[i][j]
 * @complexity O(n × m) gdzie n = m.rows, m = m.cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 2.0);
 * matrix B = 3 * A;  // równoważne A * 3
 * @endcode
 */
matrix operator*(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a * m.data[i][j];
        }
    }
    return result;
}

/**
 * @brief Friend operator odejmowania skalara - a - A
 * 
 * Odejmuje każdy element macierzy `m` od skalara `a`.
 * Operacja nie jest przemienna: a - A ≠ A - a
 * 
 * @param a skalar (lewy operand)
 * @param m macierz (prawy operand)
 * 
 * @return nowa macierz zawierająca wynik a - m
 * 
 * @post wynikowa macierz[i][j] = a - m[i][j]
 * @complexity O(n × m) gdzie n = m.rows, m = m.cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * matrix B = 10 - A;  // każdy element = 10 - A[i][j]
 * @endcode
 */
matrix operator-(int a, matrix& m) {
    matrix result(m.rows, m.cols);
    for(int i = 0; i < m.rows; i++) {
        for(int j = 0; j < m.cols; j++) {
            result.data[i][j] = a - m.data[i][j];
        }
    }
    return result;
}

/**
 * @brief Operator post-inkrementacji - A++ (wszystkie elementy +1)
 * 
 * Zwiększa wartość każdego elementu macierzy o 1.
 * Jest to operator postfiksowy (zwraca kopię przed zmianą).
 * 
 * @return referencja na bieżącą macierz (po inkrementacji)
 * 
 * @post każdy element macierzy zwiększony o 1
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @note W praktyce zwraca `*this`, nie starą wartość,
 *       ze względu na typ zwracany `matrix&`
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * A++;  // wszystkie elementy = 2.0
 * @endcode
 */
matrix& matrix::operator++(int) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j]++;
        }
    }
    return *this;
}

/**
 * @brief Operator post-dekrementacji - A-- (wszystkie elementy -1)
 * 
 * Zmniejsza wartość każdego elementu macierzy o 1.
 * Jest to operator postfiksowy (zwraca kopię przed zmianą).
 * 
 * @return referencja na bieżącą macierz (po dekrementacji)
 * 
 * @post każdy element macierzy zmniejszony o 1
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @note W praktyce zwraca `*this`, nie starą wartość,
 *       ze względu na typ zwracany `matrix&`
 * 
 * @example
 * @code
 * matrix A(2, 2, 5.0);
 * A--;  // wszystkie elementy = 4.0
 * @endcode
 */
matrix& matrix::operator--(int) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j]--;
        }
    }
    return *this;
}

/**
 * @brief Operator przypisania z dodawaniem - A += a
 * 
 * Powiększa każdy element macierzy o skalar `a`.
 * Modyfikuje macierz w miejscu (in-place).
 * 
 * @param a skalar do dodania
 * 
 * @return referencja na bieżącą macierz (po modyfikacji)
 * 
 * @post każdy element macierzy zwiększony o a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * A += 5;  // wszystkie elementy = 6.0
 * @endcode
 */
matrix& matrix::operator+=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] += a;
        }
    }
    return *this;
}

/**
 * @brief Operator przypisania z odejmowaniem - A -= a
 * 
 * Pomniejsza każdy element macierzy o skalar `a`.
 * Modyfikuje macierz w miejscu (in-place).
 * 
 * @param a skalar do odjęcia
 * 
 * @return referencja na bieżącą macierz (po modyfikacji)
 * 
 * @post każdy element macierzy zmniejszony o a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 10.0);
 * A -= 3;  // wszystkie elementy = 7.0
 * @endcode
 */
matrix& matrix::operator-=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] -= a;
        }
    }
    return *this;
}

/**
 * @brief Operator przypisania z mnożeniem - A *= a
 * 
 * Mnoży każdy element macierzy przez skalar `a`.
 * Modyfikuje macierz w miejscu (in-place).
 * 
 * @param a skalar mnożnika
 * 
 * @return referencja na bieżącą macierz (po modyfikacji)
 * 
 * @post każdy element macierzy pomnożony przez a
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 2.0);
 * A *= 3;  // wszystkie elementy = 6.0
 * @endcode
 */
matrix& matrix::operator*=(int a) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] *= a;
        }
    }
    return *this;
}

/**
 * @brief Operator funkcyjny - A(value)
 * 
 * Dodaje część całkowitą liczby `value` do każdego elementu macierzy.
 * Modyfikuje macierz w miejscu (in-place).
 * 
 * @param value liczba zmiennoprzecinkowa, z której wyodrębniany jest 
 *              operator funkcyjny  całkowita część
 * 
 * @return referencja na bieżącą macierz (po modyfikacji)
 * 
 * @post każdy element macierzy zwiększony o int(value)
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * A(3.7);  // część całkowita = 3, wszystkie elementy += 3
 * @endcode
 * 
 * @note Część ułamkowa (0.7) jest ignorowana
 */
matrix& matrix::operator()(double value) {
    int intPart = static_cast<int>(value);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            this->data[i][j] += intPart;
        }
    }
    return *this;
}

/**
 * @brief Operator wypisywania - std::cout << matrix
 * 
 * Wypisuje macierz w formacie wierszy i kolumn na strumień wyjściowy.
 * Każdy wiersz jest wypisywany w oddzielnej linii, 
 * elementy w wierszu są oddzielone spacjami.
 * 
 * @param o strumień wyjściowy (np. std::cout)
 * @param m macierz do wypisania
 * 
 * @return referencja na strumień wyjściowy `o`
 * 
 * @complexity O(n × m) gdzie n = m.rows, m = m.cols
 * 
 * @example
 * @code
 * matrix A(2, 3);
 * A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
 * A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;
 * std::cout << A;
 * // Wyjście:
 * // 1 2 3
 * // 4 5 6
 * @endcode
 */
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

/**
 * @brief Operator porównania równości - A == B
 * 
 * Sprawdza, czy wszystkie elementy macierzy A są równe odpowiadającym im
 * elementom macierzy B. Zwraca `true` tylko jeśli KAŻDY element spełnia warunek.
 * 
 * @param m macierz do porównania
 * 
 * @return `true` jeśli A[i][j] == B[i][j] dla wszystkich i, j; `false` w przeciwnym razie
 * 
 * @pre wymiary obu macierzy muszą być identyczne
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * matrix B(2, 2, 1.0);
 * matrix C(2, 2, 2.0);
 * 
 * bool result1 = (A == B);  // true - wszystkie elementy równe
 * bool result2 = (A == C);  // false - elementy różne
 * @endcode
 * 
 * @note Użyteczne do porównywania macierzy o pełnych danych
 */
bool matrix::operator==(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] != m.data[i][j]) return false;
        }
    }
    return true;
}

/**
 * @brief Operator porównania "większy" - A > B
 * 
 * Sprawdza, czy wszystkie elementy macierzy A są ŚCIŚLE większe
 * od odpowiadających im elementów macierzy B.
 * Zwraca `true` tylko jeśli KAŻDY element spełnia warunek.
 * 
 * @param m macierz do porównania
 * 
 * @return `true` jeśli A[i][j] > B[i][j] dla wszystkich i, j; 
 *         `false` jeśli choć jeden element nie spełnia warunku
 * 
 * @pre wymiary obu macierzy muszą być identyczne
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 5.0);
 * matrix B(2, 2, 2.0);
 * matrix C(2, 2, 3.0);
 * 
 * bool result1 = (A > B);  // true - wszystkie elementy A > B
 * bool result2 = (A > C);  // true - wszystkie elementy A > C
 * bool result3 = (B > C);  // false - elementy B <= C
 * @endcode
 * 
 * @note Wymaga, aby KAŻDY element spełniał warunek (semantyka ALL)
 */
bool matrix::operator>(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] <= m.data[i][j]) return false;
        }
    }
    return true;
}

/**
 * @brief Operator porównania "mniejszy" - A < B
 * 
 * Sprawdza, czy wszystkie elementy macierzy A są ŚCIŚLE mniejsze
 * od odpowiadających im elementów macierzy B.
 * Zwraca `true` tylko jeśli KAŻDY element spełnia warunek.
 * 
 * @param m macierz do porównania
 * 
 * @return `true` jeśli A[i][j] < B[i][j] dla wszystkich i, j;
 *         `false` jeśli choć jeden element nie spełnia warunku
 * 
 * @pre wymiary obu macierzy muszą być identyczne
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix A(2, 2, 1.0);
 * matrix B(2, 2, 5.0);
 * matrix C(2, 2, 2.0);
 * 
 * bool result1 = (A < B);  // true - wszystkie elementy A < B
 * bool result2 = (B < A);  // false - elementy B > A
 * bool result3 = (A < C);  // true - wszystkie elementy A < C
 * @endcode
 * 
 * @note Wymaga, aby KAŻDY element spełniał warunek (semantyka ALL)
 */
bool matrix::operator<(const matrix& m) {
    if(rows != m.rows || cols != m.cols) return false;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(this->data[i][j] >= m.data[i][j]) return false;
        }
    }
    return true;
}