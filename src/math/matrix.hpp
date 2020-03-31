//
// Created by anton on 29.03.2020.
//

#ifndef KNIGHT_MATRIX_HPP
#define KNIGHT_MATRIX_HPP

#include <iostream>

template <typename T>
class Matrix {
    class Row {
        friend class Matrix;

        Matrix* mParent;
        size_t mRowInd;

        Row(Matrix* parent, size_t rowInd)
            : mParent(parent), mRowInd(rowInd)
        {}

        Row(const Matrix* parent, size_t rowInd)
                : mParent(const_cast<Matrix*>(parent)), mRowInd(rowInd)
        {}

    public:
        constexpr T& operator[](size_t col) {
            if(col >= mParent->mColumns) {
                throw std::out_of_range("out of columns range");
            }

            return mParent->mData[mRowInd * mParent->mColumns + col];
        }

        constexpr const T& operator[](size_t col) const {
            if(col >= mParent->mColumns) {
                throw std::out_of_range("out of columns range");
            }

            return mParent->mData[mRowInd * mParent->mColumns + col];
        }
    };

public:
    Matrix() {}

    Matrix(const Matrix<T>& oth) {
        *this = oth;
    }

    Matrix(Matrix<T>&& oth) {
        *this = std::move(oth);
    }

    Matrix(size_t rows, size_t columns, const T& value = T())
        :mRows(rows), mColumns(columns)
    {
        initialize(value);
    }

    Matrix<T>& operator=(Matrix<T>&& oth) {
        free();

        mRows = oth.mRows;
        mColumns = oth.mColumns;
        mData = oth.mData;

        oth.mRows = 0;
        oth.mColumns = 0;
        oth.mData = nullptr;

        return *this;
    }

    Matrix<T>& operator=(const Matrix<T>& oth) {
        resize(oth.mRows, oth.mColumns);

        for(size_t i = 0; i < mRows * mColumns; ++i) {
            mData[i] = oth.mData[i];
        }

        return *this;
    }

    void free() {
        mColumns = mRows = 0;
        delete[] mData;
    }

    void resize(size_t rows, size_t columns, const T& value = T()) {
        free();

        mRows = rows;
        mColumns = columns;

        initialize(value);
    }

    Matrix transpose() const {
        Matrix<T> res(mColumns, mRows);

        for(size_t i = 0; i < mRows; ++i) {
            for(size_t j = 0; j < mColumns; ++j) {
                res.mData[j * res.mColumns + i] = mData[i * mColumns + j];
            }
        }

        return res;
    }

    bool isZero() const {
        for(size_t i = 0; i < mRows * mColumns; ++i) {
            if(mData[i] != T()) {
                return false;
            }
        }

        return true;
    }

    constexpr size_t getRows() const noexcept {
        return mRows;
    }

    constexpr size_t getColumns() const noexcept {
        return mColumns;
    }

    constexpr Row operator[](size_t row) {
        if(row >= mRows) {
            throw std::out_of_range("out of rows range");
        }

        return Row(this, row);
    }

    constexpr Row operator[](size_t row) const {
        if(row >= mRows) {
            throw std::out_of_range("out of rows range");
        }

        return Row(this, row);
    }

    Matrix& operator+=(const Matrix<T>& oth) {
        for(size_t i = 0; i < std::min(mRows * mColumns, oth.mRows * oth.mColumns); ++i) {
            mData[i] += oth.mData[i];
        }

        return *this;
    }

    Matrix& operator-=(const Matrix<T>& oth) {
        for(size_t i = 0; i < std::min(mRows * mColumns, oth.mRows * oth.mColumns); ++i) {
            mData[i] -= oth.mData[i];
        }

        return *this;
    }

    Matrix& operator*=(const Matrix<T>& oth) {
        if (mColumns == oth.mRows) {
            Matrix res(mRows, oth.mColumns);

            for(size_t i = 0; i < mRows; ++i) {
                for(size_t j = 0; j < oth.mColumns; ++j) {
                    for (size_t k = 0; k < mColumns; ++k) {
                        res[i][j] += (*this)[i][k] * oth[k][j];
                    }
                }
            }

            *this = res;
        }

        return *this;
    }

    template <typename NumType>
    Matrix& operator*=(NumType num) {
        for(size_t i = 0 ; i < mRows * mColumns; ++i) {
            mData[i] *= num;
        }

        return *this;
    }

    friend Matrix operator+(const Matrix<T>& left, const Matrix<T>& right) {
        auto res = left;
        res += right;
        return res;
    }

    friend Matrix operator-(const Matrix<T>& left, const Matrix<T>& right) {
        auto res = left;
        res -= right;
        return res;
    }

    friend Matrix operator*(const Matrix<T>& left, const Matrix<T>& right) {
        auto res = left;
        res *= right;
        return res;
    }

    template <typename NumType>
    friend Matrix operator*(const Matrix<T>& mat, NumType num) {
        auto res = mat;
        res *= num;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Matrix<T>& mat) {
        for(size_t i = 0; i < mat.mRows; ++i) {
            for(size_t j = 0; j < mat.mColumns; ++j) {
                stream << mat.mData[i * mat.mColumns + j] << ' ';
            }
            stream << '\n';
        }

        return stream;
    }

    ~Matrix() {
        free();
    }

private:
    void initialize(const T& value) {
        mData = new T[mRows * mColumns];

        for(size_t i = 0; i < mRows * mColumns; ++i) {
            mData[i] = value;
        }
    }

    size_t mRows = 0;
    size_t mColumns = 0;
    T* mData = nullptr;
};

#endif //KNIGHT_MATRIX_HPP
