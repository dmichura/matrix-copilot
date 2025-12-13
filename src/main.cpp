#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm> // min
#include "../include/matrix.h"

// Wczytywanie macierzy z pliku tekstowego
matrix wczytaj_macierz_z_pliku(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) throw std::runtime_error("Nie można otworzyć pliku: " + filename);

    size_t rows, cols;
    fin >> rows >> cols;

    matrix result(rows, cols, 0.0);
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            fin >> result.data[r][c];
        }
    }
    return result;
}

// Wypisanie fragmentu macierzy (np. 5x5)
void wypisz_fragment(const matrix& m, size_t max_rows = 5, size_t max_cols = 5) {
    size_t rmax = std::min(static_cast<size_t>(m.rows), max_rows);
    size_t cmax = std::min(static_cast<size_t>(m.cols), max_cols);
    for (size_t r = 0; r < rmax; ++r) {
        std::cout << "[ ";
        for (size_t c = 0; c < cmax; ++c) {
            std::cout << m(r, c) << " ";
        }
        if (cmax < static_cast<size_t>(m.cols)) std::cout << "...";
        std::cout << "]\n";
    }
    if (rmax < static_cast<size_t>(m.rows)) std::cout << "...\n";
}

int main() {
    try {
        std::cout << "Wczytywanie macierzy A z pliku...\n";
        matrix A = wczytaj_macierz_z_pliku("data/input_matrix_A.txt");
        std::cout << "Wczytywanie macierzy B z pliku...\n";
        matrix B = wczytaj_macierz_z_pliku("data/input_matrix_B.txt");

        std::cout << "\n--- Testowanie A+B ---\n";
        matrix AB = A + B;
        wypisz_fragment(AB);

        std::cout << "\n--- Testowanie A*B ---\n";
        matrix AMB = A * B;
        wypisz_fragment(AMB);

        std::cout << "\n--- Testowanie A+10 ---\n";
        matrix Aplus10 = A + 10;
        wypisz_fragment(Aplus10);

        std::cout << "\n--- Testowanie A*5 ---\n";
        matrix Amul5 = A * 5;
        wypisz_fragment(Amul5);

        std::cout << "\n--- Testowanie 10+A ---\n";
        matrix tenPlusA = 10 + A;
        wypisz_fragment(tenPlusA);

        std::cout << "\n--- Testowanie operator() ---\n";
        std::cout << "A(0,0) przed: " << A(0,0) << "\n";
        A(0,0) = 123.456;
        std::cout << "A(0,0) po: " << A(0,0) << "\n";

        std::cout << "\n--- Testowanie operator+= (skalarem) ---\n";
        matrix Ap = A;
        Ap += 3; // dodaj 3 do wszystkich elementów
        wypisz_fragment(Ap);

        std::cout << "\n--- Testowanie operator-= (skalarem) ---\n";
        matrix Am = A;
        Am -= 2; // odejmij 2 od wszystkich elementów
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

        std::cout << "\n--- Testowanie operatora porównania == ---\n";
        std::cout << ((A == B) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Testowanie operatora porównania != ---\n";
        std::cout << ((!(A == B)) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Testowanie operatora > ---\n";
        std::cout << ((A > B) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Testowanie operatora < ---\n";
        std::cout << ((A < B) ? "PRAWDA" : "FAŁSZ") << "\n";

        std::cout << "\n--- Test zabezpieczeń (try-catch) ---\n";
        try {
            matrix C(2, 2, 1.0);
            matrix wynik = A * C; // jeśli wymiary nie pasują, powinien być wyjątek
            wypisz_fragment(wynik);
        } catch (const std::exception& e) {
            std::cout << "Złapano wyjątek: " << e.what() << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Błąd krytyczny: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\n--- KONIEC TESTÓW ---\n";
    return 0;
}