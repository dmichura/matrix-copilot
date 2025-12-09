#pragma once
#include <memory>
#include <vector>
#include <cstddef>
#include <initializer_list>
#include <ostream>

class Matrix {
public:
    using size_type = std::size_t;

    Matrix() noexcept;
    Matrix(size_type rows, size_type cols, double value = 0.0);
    Matrix(std::initializer_list<std::initializer_list<double>> init);

    Matrix(const Matrix&) = default;
    Matrix(Matrix&&) noexcept = default;
    Matrix& operator=(const Matrix&) = default;
    Matrix& operator=(Matrix&&) noexcept = default;
    ~Matrix() = default;

    size_type rows() const noexcept { return rows_; }
    size_type cols() const noexcept { return cols_; }
    size_type size() const noexcept { return size_; }

    // Zarządzanie pamięcią
    void alokuj(size_type n);

    // Dostęp do danych
    double& operator()(size_type r, size_type c) { return data_[r * cols_ + c]; }
    double operator()(size_type r, size_type c) const { return data_[r * cols_ + c]; }
    double* data() noexcept { return data_.get(); }
    const double* data() const noexcept { return data_.get(); }

private:
    size_type rows_{0}, cols_{0}, size_{0};
    std::unique_ptr<double[]> data_;
};