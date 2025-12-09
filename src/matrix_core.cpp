#include "../include/matrix.h"
#include <memory>
#include <algorithm>
#include <stdexcept>

matrix::matrix() noexcept
    : rows(0), cols(0), data(nullptr) {}

matrix::matrix(size_type rows, size_type cols, double value)
    : rows(rows), cols(cols), data(nullptr)
{
    alokuj(rows * cols);
    std::fill(data[0], data[0] + rows * cols, value);
}

matrix::matrix(std::initializer_list<std::initializer_list<double>> init) {
    rows = static_cast<int>(init.size());
    cols = rows > 0 ? static_cast<int>(init.begin()->size()) : 0;
    alokuj(rows * cols);
    int r = 0;
    for (const auto& row : init) {
        if (row.size() != static_cast<size_type>(cols))
            throw std::runtime_error("Niezgodne długości wierszy w initializer_list");
        int c = 0;
        for (double val : row) {
            data[r][c] = val;
            ++c;
        }
        ++r;
    }
}

void matrix::alokuj(size_type n) {
    (void)n; // parametr nieużywany
    data = new double*[rows];
    for (size_type i = 0; i < static_cast<size_type>(rows); ++i) {
        data[i] = new double[cols];
    }
    for (size_type i = 0; i < static_cast<size_type>(rows); ++i) {
        for (size_type j = 0; j < static_cast<size_type>(cols); ++j) {
            data[i][j] = 0.0;
        }
    }
}