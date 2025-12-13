#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include "../include/matrix.h"

using namespace std;

/// @brief Wczytaj macierz z pliku tekstowego
/// Funkcja otwiera plik tekstowy i wczytuje wymiary macierzy oraz jej elementy.
/// Spodziewany format pliku:
/// - Linia 1: liczba wierszy liczba kolumn
/// - Nastepne linie: elementy macierzy oddzielone spacjami
/// 
/// @param filename Sciezka do pliku zawierajacego dane macierzy
/// @return Macierz wczytana z pliku
/// @throw std::runtime_error Jesli plik nie mogl byc otwarty
matrix wczytaj_macierz_z_pliku(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) throw std::runtime_error("Nie można otworzyć pliku: " + filename);

    size_t rows, cols;
    fin >> rows >> cols;

    matrix result(rows, cols, 0.0);
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            fin >> result(r, c);
        }
    }
    return result;
}

/// @brief Wypisz fragment macierzy na standardowe wyjscie
/// Funkcja wyswietla pierwsze max_rows wierszy i max_cols kolumn macierzy.
/// Jesli macierz jest wieksza, dodaje "..." wskazujace na ukryte elementy.
/// 
/// @param m Macierz do wypisania
/// @param max_rows Maksymalna liczba wierszy do wyswietlenia (domyslnie 5)
/// @param max_cols Maksymalna liczba kolumn do wyswietlenia (domyslnie 5)
void wypisz_fragment(const matrix& m, size_t max_rows = 5, size_t max_cols = 5) {
    size_t rmax = std::min(static_cast<size_t>(m.get_rows()), max_rows);
    size_t cmax = std::min(static_cast<size_t>(m.get_cols()), max_cols);
    
    for (size_t r = 0; r < rmax; ++r) {
        std::cout << "[ ";
        for (size_t c = 0; c < cmax; ++c) {
            std::cout << m(r, c) << " ";
        }
        if (cmax < static_cast<size_t>(m.get_cols())) 
            std::cout << "...";
        std::cout << "]\n";
    }
    if (rmax < static_cast<size_t>(m.get_rows())) 
        std::cout << "...\n";
}

/// @brief Glowna funkcja programu
/// Program testuje wszystkie operacje i funkcjonalnosci biblioteki matrix.
/// Wczytuje macierze z plikow, testuje operatory arytmetyczne, porownania
/// i inne operacje dostepne w klasie matrix. Wyswietla wyniki testow
/// w formacie czytelnym dla uzytkownika.
/// 
/// @return Kod zakonczenia programu (0 = sukces, 1 = blad)
int main() {
    try {
        std::cout << "=== TESTOWANIE BIBLIOTEKI MATRIX ===\n\n";

        std::cout << "Wczytywanie macierzy A z pliku...\n";
        matrix A = wczytaj_macierz_z_pliku("data/input_matrix_A.txt");
        std::cout << "Wymiary A: " << A.get_rows() << "x" << A.get_cols() << "\n\n";

        std::cout << "Wczytywanie macierzy B z pliku...\n";
        matrix B = wczytaj_macierz_z_pliku("data/input_matrix_B.txt");
        std::cout << "Wymiary B: " << B.get_rows() << "x" << B.get_cols() << "\n\n";

        std::cout << "--- Testowanie A+B ---\n";
        try {
            matrix AB = A + B;
            wypisz_fragment(AB);
        } catch (const std::exception& e) {
            std::cout << "Błąd: " << e.what() << "\n";
        }

        std::cout << "\n--- Testowanie A*B ---\n";
        try {
            matrix AMB = A * B;
            wypisz_fragment(AMB);
        } catch (const std::exception& e) {
            std::cout << "Błąd: " << e.what() << "\n";
        }

        std::cout << "\n--- Testowanie A+10 ---\n";
        matrix Aplus10 = A + 10;
        wypisz_fragment(Aplus10);

        std::cout << "\n--- Testowanie A*5 ---\n";
        matrix Amul5 = A * 5;
        wypisz_fragment(Amul5);

        std::cout << "\n--- Testowanie 10+A ---\n";
        matrix tenPlusA = 10 + A;
        wypisz_fragment(tenPlusA);

        std::cout << "\n--- Testowanie 5*A ---\n";
        matrix fiveTimesA = 5 * A;
        wypisz_fragment(fiveTimesA);

        std::cout << "\n--- Testowanie A-3 ---\n";
        matrix Aminus3 = A - 3;
        wypisz_fragment(Aminus3);

        std::cout << "\n--- Testowanie 10-A ---\n";
        matrix tenMinusA = 10 - A;
        wypisz_fragment(tenMinusA);

        std::cout << "\n--- Testowanie operator() (dostęp) ---\n";
        std::cout << "A(0,0) przed: " << A(0, 0) << "\n";
        A(0, 0) = 123.456;
        std::cout << "A(0,0) po: " << A(0, 0) << "\n";

        std::cout << "\n--- Testowanie operator+= (skalarem) ---\n";
        matrix Ap = A;
        Ap += 3;
        wypisz_fragment(Ap);

        std::cout << "\n--- Testowanie operator-= (skalarem) ---\n";
        matrix Am = A;
        Am -= 2;
        wypisz_fragment(Am);

        std::cout << "\n--- Testowanie operator*= (skalarem) ---\n";
        matrix As = A;
        As *= 2;
        wypisz_fragment(As);

        std::cout << "\n--- Testowanie inkrementacji ++ (postfix) ---\n";
        matrix Aincr = A;
        Aincr++;
        wypisz_fragment(Aincr);

        std::cout << "\n--- Testowanie dekrementacji -- (postfix) ---\n";
        matrix Adecr = A;
        Adecr--;
        wypisz_fragment(Adecr);

        std::cout << "\n--- Testowanie operator() z double ---\n";
        matrix Adouble = A;
        Adouble(3.7); // dodaj 3 do wszystkich elementów
        wypisz_fragment(Adouble);

        std::cout << "\n--- Testowanie operatora porównania == ---\n";
        matrix C = A;
        std::cout << "A == C: " << ((A == C) ? "PRAWDA" : "FAŁSZ") << "\n";
        std::cout << "A == B: " << ((A == B) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Testowanie operatora > ---\n";
        matrix D(3, 3, 0.5);
        matrix E(3, 3, 0.3);
        std::cout << "D(0.5) > E(0.3): " << ((D > E) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Testowanie operatora < ---\n";
        std::cout << "E(0.3) < D(0.5): " << ((E < D) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Wypisywanie     macierzy A (operator<<) ---\n";
        std::cout << A;

        std::cout << "\n=== KONIEC TESTÓW ===\n";
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Błąd krytyczny: " << e.what() << std::endl;
        return 1;
    }
}