#include "matrix.h"
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

matrix::matrix(std::initializer_list<std::initializer_list<double>> init)
    : rows(init.size()), cols(init.size() ? init.begin()->size() : 0), data(nullptr)
{
    if (rows == 0 || cols == 0) {
        return;
    }
    
    alokuj(rows * cols);
    size_type i = 0;
    for (const auto& row : init) {
        if (row.size() != cols)
            throw std::invalid_argument("Inconsistent row sizes in initializer_list");
        for (double v : row) {
            data[i / cols][i % cols] = v;
            i++;
        }
    }
}

void matrix::alokuj(size_type n) {
    if (data != nullptr) {
        for (size_type i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
    
    data = new double*[rows];
    for (size_type i = 0; i < rows; ++i) {
        data[i] = new double[cols];
    }
}