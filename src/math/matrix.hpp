//
// Created by anton on 29.03.2020.
//

#ifndef KNIGHT_MATRIX_HPP
#define KNIGHT_MATRIX_HPP

template <typename T>
class Matrix {
    class Row {
        friend class Matrix;

        Matrix* mParent;
        size_t mRowInd;

        Row(Matrix* parent, size_t rowInd)
            : mParent(parent), mRowInd(rowInd)
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
        std::cout << "Matrix copy constructor\n";
        *this = oth;
    }

    Matrix(Matrix<T>&& oth) {
        std::cout << "Matrix move constructor\n";
        *this = oth;
    }

    Matrix(size_t rows, size_t columns, const T& value = T())
        :mRows(rows), mColumns(columns)
    {
        initialize(value);
    }

    Matrix<T>& operator=(Matrix<T>&& oth) {
        std::cout << "Matrix move operator\n";
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
        std::cout << "Matrix copy operator\n";
        resize(oth.mRows, oth.mColumns);

        for(size_t i = 0; i < mRows * mColumns; ++i) {
            mData[i] = oth.mData[i];
        }

        return *this;
    }

    void free() {
        std::cout << "Matrix free:\n";
        std::cout << mRows << ' ' << mColumns << '\n';

        for(size_t i = 0; i < mRows; ++i) {
            for(size_t j = 0; j < mColumns; ++j) {
                std::cout << mData[i * mColumns + j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';

        delete[] mData;
    }

    void resize(size_t rows, size_t columns, const T& value = T()) {
        free();

        mRows = rows;
        mColumns = columns;

        initialize(value);
    }

    constexpr Row operator[](size_t row) {
        if(row >= mRows) {
            throw std::out_of_range("out of rows range");
        }

        return Row(this, row);
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
