#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <ostream>

using namespace std;

class matrix {
public:
    using size_type = std::size_t;

    matrix() noexcept;
    matrix(size_type rows, size_type cols, double value = 0.0);
    matrix(std::initializer_list<std::initializer_list<double>> init);

    matrix(const matrix&) = default;
    matrix(matrix&&) noexcept = default;
    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) noexcept = default;
    ~matrix() = default;

    size_type get_rows() const noexcept { return rows; }
    size_type get_cols() const noexcept { return cols; }
    size_type size() const noexcept { return rows * cols; }

    // Zarządzanie pamięcią
    void alokuj(size_type n);

    // Dostęp do danych
    double& operator()(size_type r, size_type c) { return data[r][c]; }
    double operator()(size_type r, size_type c) const { return data[r][c]; }

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

    // Publiczne dla friend funkcji
    int rows, cols;
    double** data;

private:
};