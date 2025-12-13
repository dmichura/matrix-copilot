#include "../include/matrix.h"
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <algorithm>

/**
 * @brief Konstruktor domyślny - tworzy macierz o wymiarach 0x0
 * 
 * Inicjalizuje macierz z zerowym rozmiarem i pustym wskaźnikiem.
 * Użyty dla tworzenia macierzy bez parametrów.
 * 
 * @note Macierz utworzona tym konstruktorem jest pusta i wymaga
 *       użycia operatora przypisania, aby otrzymać dane.
 * 
 * @post rows == 0, cols == 0, data == nullptr
 */
matrix::matrix() noexcept : rows(0), cols(0), data(nullptr) {}

/**
 * @brief Konstruktor z parametrami - tworzy macierz o podanych wymiarach
 * 
 * Alokuje pamięć dla macierzy o wymiarach r×c i inicjalizuje
 * wszystkie elementy wartością `value`.
 * 
 * @param r liczba wierszy (konwertowana do int)
 * @param c liczba kolumn (konwertowana do int)
 * @param value wartość początkowa wszystkich elementów (domyślnie 0.0)
 * 
 * @throw std::bad_alloc jeśli alokacja pamięci się nie powiedzie
 * 
 * @post rows == r, cols == c, wszystkie elementy == value
 * @complexity O(r × c) - dla alokacji i inicjalizacji
 * 
 * @example
 * @code
 * matrix m(3, 3, 1.5);  // macierz 3×3 wypełniona wartościami 1.5
 * @endcode
 */
matrix::matrix(std::size_t r, std::size_t c, double value)
    : rows(static_cast<int>(r)), cols(static_cast<int>(c)) {
    alokuj(r * c);
    for (std::size_t i = 0; i < static_cast<std::size_t>(rows); ++i) {
        for (std::size_t j = 0; j < static_cast<std::size_t>(cols); ++j) {
            data[i][j] = value;
        }
    }
}

/**
 * @brief Konstruktor z initializer_list - tworzy macierz ze zainicjalizowanej listy
 * 
 * Konstruuje macierz z zagnieżdżonej listy inicjalizacyjnej.
 * Wszystkie wiersze muszą mieć tę samą długość.
 * 
 * @param init zagnieżdżona lista inicjalizacyjna std::initializer_list
 * 
 * @throw std::runtime_error jeśli wiersze mają różne długości
 * 
 * @post rows == init.size(), cols == liczba kolumn w pierwszym wierszu
 * @complexity O(r × c) gdzie r = liczba wierszy, c = liczba kolumn
 * 
 * @example
 * @code
 * matrix m = {{1, 2, 3},
 *             {4, 5, 6}};  // macierz 2×3
 * @endcode
 */
matrix::matrix(std::initializer_list<std::initializer_list<double>> init)
    : rows(static_cast<int>(init.size())),
      cols(init.size() ? static_cast<int>(init.begin()->size()) : 0) {
    alokuj(rows * cols);
    std::size_t r = 0;
    for (const auto& row : init) {
        if (row.size() != static_cast<std::size_t>(cols))
            throw std::runtime_error("Niezgodne długości wierszy w initializer_list");
        std::size_t c = 0;
        for (double val : row) {
            data[r][c] = val;
            ++c;
        }
        ++r;
    }
}

/**
 * @brief Konstruktor kopiujący - tworzy głęboką kopię macierzy
 * 
 * Tworzy nową macierz będącą kopią innej macierzy.
 * Alokuje nową pamięć i kopiuje wszystkie elementy.
 * Wymagany ze względu na użycie unique_ptr w klasie.
 * 
 * @param other macierz do skopiowania
 * 
 * @post Ta macierz ma te same wymiary co `other` oraz identyczne elementy
 * @throw std::bad_alloc jeśli alokacja pamięci się nie powiedzie
 * @complexity O(r × c) - O(inne.rows × inne.cols)
 * 
 * @note Bez tego konstruktora, kompilator nie mógłby skopiować
 *       macierzy ze względu na unique_ptr
 * 
 * @example
 * @code
 * matrix A(3, 3, 1.0);
 * matrix B = A;  // używa konstruktora kopiującego
 * @endcode
 */
matrix::matrix(const matrix& other) 
    : rows(other.rows), cols(other.cols) {
    alokuj(rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

/**
 * @brief Operator przypisania - przypisuje wartości z innej macierzy
 * 
 * Tworzy głęboką kopię macierzy źródłowej i przypisuje jej zawartość
 * do bieżącej macierzy. Obsługuje także samoprzypasanie (a = a).
 * 
 * @param other macierz do przypisania
 * 
 * @return referencja na bieżącą macierz (*this)
 * 
 * @post Ta macierz ma te same wymiary co `other` oraz identyczne elementy
 * @throw std::bad_alloc jeśli alokacja pamięci się nie powiedzie
 * @complexity O(r × c) - O(inne.rows × inne.cols)
 * 
 * @note Zawiera sprawdzenie samoprzypasania (this == &other)
 * 
 * @example
 * @code
 * matrix A(3, 3, 1.0);
 * matrix B(2, 2, 0.0);
 * B = A;  // B zmienia rozmiar i przejmuje dane z A
 * @endcode
 */
matrix& matrix::operator=(const matrix& other) {
    if (this == &other) {
        return *this;
    }
    
    // Zwolnij starą pamięć
    data.reset();
    
    rows = other.rows;
    cols = other.cols;
    
    alokuj(rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    
    return *this;
}

/**
 * @brief Alokuje pamięć dla macierzy
 * 
 * Przydziela dynamiczną pamięć dla dwuwymiarowej tablicy double
 * oraz inicjalizuje wszystkie elementy na zero.
 * Korzysta z unique_ptr do automatycznego zarządzania pamięcią.
 * 
 * @param n liczba elementów do alokacji (parametr nieużywany,
 *          rzeczywisty rozmiar określony przez rows i cols)
 * 
 * @pre rows > 0 && cols > 0
 * @post data wskazuje na alokowaną tablicę, wszystkie elementy = 0.0
 * @throw std::bad_alloc jeśli alokacja się nie powiedzie
 * @complexity O(rows × cols)
 * 
 * @note Parametr `n` jest ignorowany; rzeczywisty rozmiar to rows × cols
 * @warning Jeśli rows lub cols wynoszą 0, zachowanie jest niezdefiniowane
 * 
 * @internal Ta metoda jest wewnętrzna dla klasy i powinna być
 *           wywoływana przez konstruktory
 */
void matrix::alokuj(std::size_t /*n*/) {
    data = std::make_unique<double*[]>(rows);
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols];
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = 0.0;
        }
    }
}

/**
 * @brief Operator dostępu (niestały) - zwraca referencję na element
 * 
 * Umożliwia dostęp do elementu macierzy o indeksach (r, c)
 * i modyfikację jego wartości. Brak sprawdzenia granic.
 * 
 * @param r indeks wiersza (0-based)
 * @param c indeks kolumny (0-based)
 * 
 * @return referencja na element data[r][c]
 * 
 * @pre 0 <= r < rows && 0 <= c < cols
 * @complexity O(1) - bezpośredni dostęp do pamięci
 * 
 * @warning Brak sprawdzenia granic! Przekazanie nieprawidłowych
 *          indeksów spowoduje niezdefiniowane zachowanie
 * 
 * @example
 * @code
 * matrix m(3, 3);
 * m(0, 0) = 5.0;  // ustawienie wartości
 * double x = m(0, 0);  // odczytanie wartości
 * @endcode
 */
double& matrix::operator()(std::size_t r, std::size_t c) {
    return data[r][c];
}

/**
 * @brief Operator dostępu (stały) - zwraca kopię elementu
 * 
 * Umożliwia bezpieczny (tylko do odczytu) dostęp do elementu
 * macierzy bez możliwości modyfikacji. Brak sprawdzenia granic.
 * 
 * @param r indeks wiersza (0-based)
 * @param c indeks kolumny (0-based)
 * 
 * @return kopia wartości elementu data[r][c]
 * 
 * @pre 0 <= r < rows && 0 <= c < cols
 * @complexity O(1) - bezpośredni dostęp do pamięci
 * 
 * @warning Brak sprawdzenia granic! Przekazanie nieprawidłowych
 *          indeksów spowoduje niezdefiniowane zachowanie
 * 
 * @example
 * @code
 * const matrix m(3, 3, 1.5);
 * double x = m(0, 0);  // zwraca 1.5 (kopię wartości)
 * // m(0, 0) = 5.0;  // BŁĄD KOMPILACJI - brak możliwości modyfikacji
 * @endcode
 */
double matrix::operator()(std::size_t r, std::size_t c) const {
    return data[r][c];
}