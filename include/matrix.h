#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <ostream>

using namespace std;

class matrix {
public:
    matrix() noexcept;
    matrix(std::size_t rows, std::size_t cols, double value = 0.0);
    matrix(std::initializer_list<std::initializer_list<double>> init);

    // Konstruktor kopiujący
    matrix(const matrix& other);
    // Operator przypisania
    matrix& operator=(const matrix& other);
    
    // Konstruktor przenoszący
    matrix(matrix&&) noexcept = default;
    // Operator przypisania przenoszący
    matrix& operator=(matrix&&) noexcept = default;
    
    ~matrix() = default;

    std::size_t get_rows() const noexcept { return rows; }
    std::size_t get_cols() const noexcept { return cols; }
    std::size_t size() const noexcept { return rows * cols; }

    // Zarządzanie pamięcią
    void alokuj(std::size_t n);

    // Dostęp do danych
    double& operator()(std::size_t r, std::size_t c);
    double operator()(std::size_t r, std::size_t c) const;

    // Operatory arytmetyczne
    matrix& operator+(matrix& m);
    matrix& operator*(matrix& m);
    matrix& operator+(int a);
    matrix& operator*(int a);
    matrix& operator-(int a);

    // Friend operatory dla int op matrix
    friend matrix operator+(int a, matrix& m);
    friend matrix operator*(int a, matrix& m);
    friend matrix operator-(int a, matrix& m);

    // Inkrementacja/dekrementacja
    matrix& operator++(int);
    matrix& operator--(int);

    // Operatory przypisania
    matrix& operator+=(int a);
    matrix& operator-=(int a);
    matrix& operator*=(int a);

    // Operator funkcyjny
    matrix& operator()(double value);

    // Wypisywanie
    friend ostream& operator<<(ostream& o, matrix& m);

    // Operatory porównania
    bool operator==(const matrix& m);
    bool operator>(const matrix& m);
    bool operator<(const matrix& m);

    // Metody utility
    matrix& wstaw(int x, int y, int wartosc);
    int pokaz(int x, int y);
    matrix& dowroc();
    matrix& losuj();
    matrix& losuj(int x);
    matrix& diagonalna(int* t);
    matrix& diagonalna_k(int k, int* t);
    matrix& kolumna(int x, int* t);
    matrix& wiersz(int y, int* t);
    matrix& przekatna();
    matrix& pod_przekatna();
    matrix& nad_przekatna();
    matrix& szachownica();

    int rows, cols;
    std::unique_ptr<double*[]> data;

private:
};