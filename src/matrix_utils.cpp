#include "../include/matrix.h"
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <stdexcept>

using namespace std;

/**
 * @brief Wstawia wartość do komórki macierzy
 * 
 * Ustawia wartość elementu na pozycji (x, y) na podaną wartość.
 * Brak sprawdzenia granic - nieprawidłowe indeksy mogą spowodować
 * niezdefiniowane zachowanie.
 * 
 * @param x indeks wiersza (0-based)
 * @param y indeks kolumny (0-based)
 * @param wartosc wartość do wstawienia (konwertowana z int na double)
 * 
 * @return referencja na bieżącą macierz (umożliwia łańcuchowanie operacji)
 * 
 * @pre 0 <= x < rows && 0 <= y < cols
 * @post data[x][y] == wartosc
 * @complexity O(1)
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.wstaw(0, 0, 5).wstaw(1, 1, 10);  // łańcuchowanie operacji
 * @endcode
 * 
 * @warning Brak sprawdzenia granic! Użycie nieprawidłowych indeksów
 *          spowoduje niezdefiniowane zachowanie
 * 
 * @see pokaz()
 */
matrix& matrix::wstaw(int x, int y, int wartosc) {
    data[x][y] = wartosc;
    return *this;
}

/**
 * @brief Zwraca wartość z komórki macierzy
 * 
 * Pobiera wartość elementu na pozycji (x, y) z macierzy.
 * Brak sprawdzenia granic.
 * 
 * @param x indeks wiersza (0-based)
 * @param y indeks kolumny (0-based)
 * 
 * @return wartość elementu data[x][y] (skonwertowana do int)
 * 
 * @pre 0 <= x < rows && 0 <= y < cols
 * @complexity O(1)
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.wstaw(0, 0, 42);
 * int val = m.pokaz(0, 0);  // val == 42
 * @endcode
 * 
 * @warning Brak sprawdzenia granic! Użycie nieprawidłowych indeksów
 *          spowoduje niezdefiniowane zachowanie
 * 
 * @see wstaw()
 */
int matrix::pokaz(int x, int y) {
    return data[x][y];
}

/**
 * @brief Dokonuje transpozycji macierzy w miejscu (in-place)
 * 
 * Transponuje macierz zamieniając wiersze z kolumnami.
 * Operacja jest przeprowadzana w miejscu (nie tworzy nowej macierzy).
 * Wymaga macierzy kwadratowej (rows == cols).
 * 
 * @return referencja na bieżącą macierz (transponowaną)
 * 
 * @throw std::runtime_error jeśli macierz nie jest kwadratowa
 * 
 * @pre rows == cols (macierz kwadratowa)
 * @post element na pozycji [i][j] zawiera wartość które była na [j][i]
 * @complexity O(n²) gdzie n = rows = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.wstaw(0, 1, 5).wstaw(1, 0, 3);
 * m.dowroc();  // m[0][1] = 3, m[1][0] = 5
 * @endcode
 * 
 * @warning Wymaga macierzy kwadratowej! Dla macierzy prostokątnych
 *          rzuca wyjątek std::runtime_error
 * 
 * @note Optymalizacja: pętla j rozpoczyna się od i+1, aby uniknąć
 *       podwójnego zamieniania
 */
matrix& matrix::dowroc() {
    if (rows != cols) {
        throw std::runtime_error("Transpozycja in-place wymaga macierzy kwadratowej");
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = i + 1; j < cols; ++j) {
            double temp = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = temp;
        }
    }
    return *this;
}

/**
 * @brief Wypełnia macierz losowymi cyframi 0-9
 * 
 * Generuje losowe wartości z zakresu [0, 9] dla wszystkich elementów macierzy.
 * Używa generatora liczb losowych std::rand() z ziarnem czasowym.
 * 
 * @return referencja na bieżącą macierz (wypełnioną)
 * 
 * @post każdy element macierzy zawiera losową wartość z zakresu [0, 9]
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.losuj();  // macierz zawiera losowe cyfry 0-9
 * @endcode
 * 
 * @warning Używa std::rand() - nie jest to generator o dobrych właściwościach
 *          statystycznych. Dla poważnych zastosowań użyj std::mt19937
 * 
 * @note Ziarna losowe są ustawiane przy każdym wywołaniu (time(0)),
 *       co może spowolnić program jeśli jest wywoływane wielokrotnie
 * 
 * @deprecated Rozważ użycie <random> zamiast rand()
 */
matrix& matrix::losuj() {
    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = rand() % 10;
        }
    }
    return *this;
}

/**
 * @brief Losuje `x` par współrzędnych i wstawia losowe cyfry
 * 
 * Wybiera `x` losowych pozycji w macierzy i wstawia w nich losowe cyfry 0-9.
 * Pozycje mogą się powtarzać (losowanie ze zwracaniem).
 * 
 * @param x liczba pozycji do wylosowania i wypełnienia
 * 
 * @return referencja na bieżącą macierz (zmodyfikowaną)
 * 
 * @post co najwyżej `x` losowych elementów zawiera losowe wartości z [0, 9]
 * @complexity O(x)
 * 
 * @example
 * @code
 * matrix m(5, 5, 0.0);
 * m.losuj(10);  // wypełni co najwyżej 10 losowych pozycji
 * @endcode
 * 
 * @note Liczba faktycznie zmienionych elementów może być mniejsza niż `x`
 *       ze względu na losowe powtórzenia pozycji
 * 
 * @warning Używa std::rand() - zobacz losuj() dla szczegółów
 * 
 * @deprecated Rozważ użycie <random> zamiast rand()
 * 
 * @see losuj()
 */
matrix& matrix::losuj(int x) {
    srand(time(0));
    for (int i = 0; i < x; ++i) {
        int row = rand() % rows;
        int col = rand() % cols;
        int value = rand() % 10;
        data[row][col] = value;
    }
    return *this;
}

/**
 * @brief Przepisuje tablicę na główną przekątną
 * 
 * Ustawia wszystkie elementy macierzy na zero, następnie
 * przepisuje wartości z tablicy `t` na główną przekątną [i][i].
 * Ilość elementów przepisanych = min(rows, cols).
 * 
 * @param t wskaźnik na tablicę wartości do wpisania
 *          (musi zawierać co najmniej min(rows, cols) elementów)
 * 
 * @return referencja na bieżącą macierz (zmodyfikowaną)
 * 
 * @pre t != nullptr && t ma co najmniej min(rows, cols) elementów
 * @post wszystkie elementy = 0 poza przekątną, data[i][i] = t[i]
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * int values[] = {1, 2, 3};
 * m.diagonalna(values);
 * // Wynik:
 * // 1 0 0
 * // 0 2 0
 * // 0 0 3
 * @endcode
 * 
 * @warning Parametr `t` musi zawierać wystarczającą ilość elementów!
 *          Brak sprawdzenia granic tablicy wejściowej
 * 
 * @see diagonalna_k()
 */
matrix& matrix::diagonalna(int* t) {
    // Wyzeruj całą macierz
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = 0;
        }
    }
    
    // Wstaw wartości na głównej przekątnej
    int minDim = (rows < cols) ? rows : cols;
    for (int i = 0; i < minDim; ++i) {
        data[i][i] = t[i];
    }
    return *this;
}

/**
 * @brief Przepisuje tablicę na przekątną przesuniętą o k pozycji
 * 
 * Ustawia wszystkie elementy na zero, następnie przepisuje wartości
 * z tablicy `t` na przekątną przesuniętą o `k` pozycji.
 * 
 * - k=0: główna przekątna [i][i]
 * - k>0: przekątna ponad główną (w prawo) [i][i+k]
 * - k<0: przekątna poniżej głównej (w dół) [i][i-k]
 * 
 * @param k przesunięcie przekątnej (k=0 główna, k>0 w górę, k<0 w dół)
 * @param t wskaźnik na tablicę wartości do wpisania
 * 
 * @return referencja na bieżącą macierz (zmodyfikowaną)
 * 
 * @pre t != nullptr && t zawiera wystarczającą ilość elementów
 * @post wszystkie elementy = 0 poza przekątną k, elementy na przekątnej = t[i]
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * int values[] = {1, 2, 3};
 * 
 * // k=0 (główna przekątna)
 * m.diagonalna_k(0, values);
 * 
 * // k=1 (nad główną)
 * m.diagonalna_k(1, values);
 * // Wynik:
 * // 0 1 0
 * // 0 0 2
 * // 0 0 0
 * 
 * // k=-1 (pod główną)
 * m.diagonalna_k(-1, values);
 * // Wynik:
 * // 0 0 0
 * // 1 0 0
 * // 0 2 0
 * @endcode
 * 
 * @warning Brak sprawdzenia granic dla parametru `t`!
 * 
 * @see diagonalna()
 */
matrix& matrix::diagonalna_k(int k, int* t) {
    // Wyzeruj całą macierz
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = 0;
        }
    }
    
    if (k >= 0) {
        // k >= 0: przesuwa w prawo (górę)
        for (int i = 0; i < rows; ++i) {
            int j = i + k;
            if (j < cols) {
                data[i][j] = t[i];
            }
        }
    } else {
        // k < 0: przesuwa w dół
        int absk = -k;
        for (int i = absk; i < rows; ++i) {
            int j = i - absk;
            data[i][j] = t[i - absk];
        }
    }
    return *this;
}

/**
 * @brief Wpisuje tablicę w kolumnę macierzy
 * 
 * Wstawia wszystkie elementy tablicy `t` w kolumnę o indeksie `x`.
 * Pozostałe elementy macierzy nie są modyfikowane.
 * 
 * @param x indeks kolumny (0-based)
 * @param t wskaźnik na tablicę wartości
 *          (musi zawierać co najmniej `rows` elementów)
 * 
 * @return referencja na bieżącą macierz (zmodyfikowaną)
 * 
 * @pre 0 <= x < cols && t != nullptr && t zawiera co najmniej rows elementów
 * @post data[i][x] = t[i] dla wszystkich i < rows
 * @complexity O(rows)
 * 
 * @example
 * @code
 * matrix m(3, 3, 0.0);
 * int col_values[] = {10, 20, 30};
 * m.kolumna(1, col_values);  // wstaw w kolumnę indeks 1
 * // Wynik: kolumna [1] zawiera [10, 20, 30]
 * @endcode
 * 
 * @warning Brak sprawdzenia granic! Nieprawidłowy indeks x lub za mała
 *          tablica t spowodują niezdefiniowane zachowanie
 * 
 * @see wiersz()
 */
matrix& matrix::kolumna(int x, int* t) {
    for (int i = 0; i < rows; ++i) {
        data[i][x] = t[i];
    }
    return *this;
}

/**
 * @brief Wpisuje tablicę w wiersz macierzy
 * 
 * Wstawia wszystkie elementy tablicy `t` w wiersz o indeksie `y`.
 * Pozostałe elementy macierzy nie są modyfikowane.
 * 
 * @param y indeks wiersza (0-based)
 * @param t wskaźnik na tablicę wartości
 *          (musi zawierać co najmniej `cols` elementów)
 * 
 * @return referencja na bieżącą macierz (zmodyfikowaną)
 * 
 * @pre 0 <= y < rows && t != nullptr && t zawiera co najmniej cols elementów
 * @post data[y][j] = t[j] dla wszystkich j < cols
 * @complexity O(cols)
 * 
 * @example
 * @code
 * matrix m(3, 3, 0.0);
 * int row_values[] = {5, 6, 7};
 * m.wiersz(2, row_values);  // wstaw w wiersz indeks 2
 * // Wynik: wiersz [2] zawiera [5, 6, 7]
 * @endcode
 * 
 * @warning Brak sprawdzenia granic! Nieprawidłowy indeks y lub za mała
 *          tablica t spowodują niezdefiniowane zachowanie
 * 
 * @see kolumna()
 */
matrix& matrix::wiersz(int y, int* t) {
    for (int j = 0; j < cols; ++j) {
        data[y][j] = t[j];
    }
    return *this;
}

/**
 * @brief Ustawia macierz jako macierz jednostkową (identyczności)
 * 
 * Wstawia 1.0 na głównej przekątnej i 0.0 wszędzie indziej.
 * Wynikiem jest macierz I taka, że A * I = A i I * A = A.
 * 
 * @return referencja na bieżącą macierz (przekształconą)
 * 
 * @post data[i][i] = 1.0, data[i][j] = 0.0 dla i ≠ j
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.przekatna();
 * // Wynik:
 * // 1 0 0
 * // 0 1 0
 * // 0 0 1
 * @endcode
 * 
 * @note Ta funkcja zawsze tworzy macierz tożsamościową,
 *       niezależnie od poprzedniej zawartości
 * 
 * @see pod_przekatna(), nad_przekatna()
 */
matrix& matrix::przekatna() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == j) {
                data[i][j] = 1;
            } else {
                data[i][j] = 0;
            }
        }
    }
    return *this;
}

/**
 * @brief Tworzy macierz dolnotrójkątną z jedynkami
 * 
 * Wstawia 1.0 dla wszystkich elementów poniżej głównej przekątnej,
 * 0.0 na i nad główną przekątną.
 * 
 * @return referencja na bieżącą macierz (przekształconą)
 * 
 * @post data[i][j] = 1.0 jeśli i > j, 0.0 jeśli i ≤ j
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.pod_przekatna();
 * // Wynik:
 * // 0 0 0
 * // 1 0 0
 * // 1 1 0
 * @endcode
 * 
 * @see nad_przekatna(), przekatna()
 */
matrix& matrix::pod_przekatna() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i > j) {
                data[i][j] = 1;
            } else {
                data[i][j] = 0;
            }
        }
    }
    return *this;
}

/**
 * @brief Tworzy macierz górniotrójkątną z jedynkami
 * 
 * Wstawia 1.0 dla wszystkich elementów powyżej głównej przekątnej,
 * 0.0 na i poniżej głównej przekątnej.
 * 
 * @return referencja na bieżącą macierz (przekształconą)
 * 
 * @post data[i][j] = 1.0 jeśli i < j, 0.0 jeśli i ≥ j
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.nad_przekatna();
 * // Wynik:
 * // 0 1 1
 * // 0 0 1
 * // 0 0 0
 * @endcode
 * 
 * @see pod_przekatna(), przekatna()
 */
matrix& matrix::nad_przekatna() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i < j) {
                data[i][j] = 1;
            } else {
                data[i][j] = 0;
            }
        }
    }
    return *this;
}

/**
 * @brief Wypełnia macierz wzorem szachownicy
 * 
 * Tworzy wzór szachownicy gdzie elementy przyjmują wartość 0 lub 1
 * w zależności od parzystości sumy indeksów (i + j).
 * Jeśli (i + j) jest parzyste → 0, jeśli nieparzyste → 1.
 * 
 * @return referencja na bieżącą macierz (wypełnioną)
 * 
 * @post data[i][j] = 0 jeśli (i + j) % 2 == 0, 
 *                   = 1 jeśli (i + j) % 2 == 1
 * @complexity O(n × m) gdzie n = rows, m = cols
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m.szachownica();
 * // Wynik:
 * // 0 1 0
 * // 1 0 1
 * // 0 1 0
 * @endcode
 * 
 * @note Wzór szachownicy jest często używany w testach i wizualizacji
 * 
 * @see przekatna(), pod_przekatna(), nad_przekatna()
 */
matrix& matrix::szachownica() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i + j) % 2 == 0) {
                data[i][j] = 0;
            } else {
                data[i][j] = 1;
            }
        }
    }
    return *this;
}
