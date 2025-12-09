#include "matrix.h"
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// 1. Wstawia wartość do komórki (wiersz x, kolumna y)
matrix& matrix::wstaw(int x, int y, int wartosc) {
    data[x][y] = wartosc;
    return *this;
}

// 2. Zwraca wartość z komórki (wiersz x, kolumna y)
int matrix::pokaz(int x, int y) {
    return data[x][y];
}

// 3. Dokonuje transpozycji macierzy w miejscu (zamienia wiersze z kolumnami)
matrix& matrix::dowroc() {
    // Dla macierzy kwadratowej n x n
    if (rows != cols) {
        throw std::runtime_error("Transpozycja in-place wymaga macierzy kwadratowej");
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = i + 1; j < cols; ++j) {
            int temp = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = temp;
        }
    }
    return *this;
}

// 4. Wypełnia wszystkie pola losowymi cyframi 0-9
matrix& matrix::losuj() {
    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = rand() % 10;
        }
    }
    return *this;
}

// 5. Losuje 'x' par współrzędnych i wstawia w nie losowe cyfry 0-9
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

// 6. Przepisuje tablicę 't' na główną przekątną, reszta zerami
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

// 7. Przepisuje tablicę 't' na przekątną przesuniętą o 'k'
// k=0 główna, k>0 w górę (w prawo), k<0 w dół
matrix& matrix::diagonalna_k(int k, int* t) {
    // Wyzeruj całą macierz
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = 0;
        }
    }
    
    if (k >= 0) {
        // k > 0: przesuwa w prawo (górę)
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

// 8. Wpisuje tablicę 't' w kolumnę o indeksie x
matrix& matrix::kolumna(int x, int* t) {
    for (int i = 0; i < rows; ++i) {
        data[i][x] = t[i];
    }
    return *this;
}

// 9. Wpisuje tablicę 't' w wiersz o indeksie y
matrix& matrix::wiersz(int y, int* t) {
    for (int j = 0; j < cols; ++j) {
        data[y][j] = t[j];
    }
    return *this;
}

// 10. Wstawia 1 na przekątnej, 0 poza nią
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

// 11. Wstawia 1 pod przekątną, 0 na przekątnej i nad nią
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

// 12. Wstawia 1 nad przekątną, 0 na przekątnej i pod nią
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

// 13. Wypełnia wzorem szachownicy (0 i 1) zależnie od parzystości sumy indeksów
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
