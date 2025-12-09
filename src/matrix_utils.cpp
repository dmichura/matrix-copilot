#include "matrix.h"
#include <ostream>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        for (Matrix::size_type j = 0; j < m.cols(); ++j) {
            os << std::setw(10) << std::setprecision(6) << m(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

Matrix transpose(const Matrix& m) {
    Matrix result(m.cols(), m.rows());
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        for (Matrix::size_type j = 0; j < m.cols(); ++j) {
            result(j, i) = m(i, j);
        }
    }
    return result;
}

double trace(const Matrix& m) {
    if (m.rows() != m.cols()) {
        throw std::invalid_argument("Trace can only be calculated for square matrices");
    }
    
    double sum = 0.0;
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        sum += m(i, i);
    }
    return sum;
}

bool is_square(const Matrix& m) noexcept {
    return m.rows() == m.cols();
}

bool is_symmetric(const Matrix& m) noexcept {
    if (!is_square(m)) {
        return false;
    }
    
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        for (Matrix::size_type j = i + 1; j < m.cols(); ++j) {
            if (std::abs(m(i, j) - m(j, i)) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

bool is_diagonal(const Matrix& m) noexcept {
    if (!is_square(m)) {
        return false;
    }
    
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        for (Matrix::size_type j = 0; j < m.cols(); ++j) {
            if (i != j && std::abs(m(i, j)) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

bool is_identity(const Matrix& m) noexcept {
    if (!is_diagonal(m)) {
        return false;
    }
    
    for (Matrix::size_type i = 0; i < m.rows(); ++i) {
        if (std::abs(m(i, i) - 1.0) > 1e-9) {
            return false;
        }
    }
    return true;
}

Matrix identity(Matrix::size_type n) {
    Matrix result(n, n, 0.0);
    for (Matrix::size_type i = 0; i < n; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}

double frobenius_norm(const Matrix& m) noexcept {
    double sum = 0.0;
    for (Matrix::size_type i = 0; i < m.size(); ++i) {
        double val = m.data()[i];
        sum += val * val;
    }
    return std::sqrt(sum);
}

Matrix fill(Matrix::size_type rows, Matrix::size_type cols, double value) {
    return Matrix(rows, cols, value);
}

Matrix zeros(Matrix::size_type rows, Matrix::size_type cols) {
    return Matrix(rows, cols, 0.0);
}

Matrix ones(Matrix::size_type rows, Matrix::size_type cols) {
    return Matrix(rows, cols, 1.0);
}
