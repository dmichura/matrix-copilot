#include "matrix.h"
#include <ostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

// operator<< jest już zdefiniowany w matrix_operators.cpp jako friend

matrix transpose(const matrix& m) {
    matrix result(m.cols, m.rows);
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            result.data[j][i] = m.data[i][j];
        }
    }
    return result;
}

double trace(const matrix& m) {
    if (m.rows != m.cols) {
        throw std::invalid_argument("Trace can only be calculated for square matrices");
    }
    
    double sum = 0.0;
    for (int i = 0; i < m.rows; ++i) {
        sum += m.data[i][i];
    }
    return sum;
}

bool is_square(const matrix& m) noexcept {
    return m.rows == m.cols;
}

bool is_symmetric(const matrix& m) noexcept {
    if (!is_square(m)) {
        return false;
    }
    
    for (int i = 0; i < m.rows; ++i) {
        for (int j = i + 1; j < m.cols; ++j) {
            if (std::abs(m.data[i][j] - m.data[j][i]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

bool is_diagonal(const matrix& m) noexcept {
    if (!is_square(m)) {
        return false;
    }
    
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            if (i != j && std::abs(m.data[i][j]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

bool is_identity(const matrix& m) noexcept {
    if (!is_diagonal(m)) {
        return false;
    }
    
    for (int i = 0; i < m.rows; ++i) {
        if (std::abs(m.data[i][i] - 1.0) > 1e-9) {
            return false;
        }
    }
    return true;
}

matrix identity(matrix::size_type n) {
    matrix result(n, n, 0.0);
    for (matrix::size_type i = 0; i < n; ++i) {
        result.data[i][i] = 1.0;
    }
    return result;
}

double frobenius_norm(const matrix& m) noexcept {
    double sum = 0.0;
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            double val = m.data[i][j];
            sum += val * val;
        }
    }
    return std::sqrt(sum);
}

matrix fill(matrix::size_type rows, matrix::size_type cols, double value) {
    return matrix(rows, cols, value);
}

matrix zeros(matrix::size_type rows, matrix::size_type cols) {
    return matrix(rows, cols, 0.0);
}

matrix ones(matrix::size_type rows, matrix::size_type cols) {
    return matrix(rows, cols, 1.0);
}
