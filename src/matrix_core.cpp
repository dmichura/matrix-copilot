#include "matrix.h"
#include <memory>
#include <algorithm>
#include <stdexcept>

Matrix::Matrix() noexcept
    : rows_(0), cols_(0), size_(0), data_(nullptr) {}

Matrix::Matrix(size_type rows, size_type cols, double value)
    : rows_(rows), cols_(cols), size_(rows * cols), data_(nullptr)
{
    alokuj(size_);
    std::fill(data_.get(), data_.get() + size_, value);
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init)
    : rows_(init.size()), cols_(init.size() ? init.begin()->size() : 0), size_(rows_ * cols_), data_(nullptr)
{
    alokuj(size_);
    size_type i = 0;
    for (const auto& row : init) {
        if (row.size() != cols_)
            throw std::invalid_argument("Inconsistent row sizes in initializer_list");
        for (double v : row)
            data_[i++] = v;
    }
}

void Matrix::alokuj(size_type n) {
    if (!data_ || size_ < n) {
        data_.reset();
        data_ = std::make_unique<double[]>(n);
        size_ = n;
    }
    // Jeśli zaalokowany rozmiar >= n, nie robimy nic
}