#include "../include/matrix.h"
#include <stdexcept>
#include <cstddef>
#include <memory>
#include <algorithm>

matrix::matrix() noexcept : rows(0), cols(0), data(nullptr) {}

matrix::matrix(std::size_t r, std::size_t c, double value)
    : rows(static_cast<int>(r)), cols(static_cast<int>(c)) {
    alokuj(r * c);
    for (std::size_t i = 0; i < static_cast<std::size_t>(rows); ++i) {
        for (std::size_t j = 0; j < static_cast<std::size_t>(cols); ++j) {
            data[i][j] = value;
        }
    }
}

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

void matrix::alokuj(std::size_t /*n*/) {
    data = new double*[rows];
    for (std::size_t i = 0; i < static_cast<std::size_t>(rows); ++i) {
        data[i] = new double[cols];
    }
    for (std::size_t i = 0; i < static_cast<std::size_t>(rows); ++i) {
        for (std::size_t j = 0; j < static_cast<std::size_t>(cols); ++j) {
            data[i][j] = 0.0;
        }
    }
}