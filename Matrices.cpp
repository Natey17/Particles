#include "Matrices.h"
#include <stdexcept>
#include <cmath>

using namespace std;

namespace Matrices {

    Matrix::Matrix(int _rows, int _cols) : a(_rows, std::vector<double>(_cols, 0.0))
    {
        rows = _rows;
        cols = _cols;
    }

    Matrix operator+(const Matrix& A, const Matrix& B)
    {
        if (A.getRows() != B.getRows() || A.getCols() != B.getCols()) {
            throw std::runtime_error("Matrix dimension mismatch in operator+");
        }
        Matrix C(A.getRows(), A.getCols());
        for (int i = 0; i < A.getRows(); i++) {
            for (int j = 0; j < A.getCols(); j++) {
                C(i, j) = A(i, j) + B(i, j);
            }
        }
        return C;
    }

    Matrix operator*(const Matrix& A, const Matrix& B)
    {
        if (A.getCols() != B.getRows()) {
            throw std::runtime_error("Matrix dimension mismatch in operator*");
        }
        Matrix C(A.getRows(), B.getCols());
        for (int i = 0; i < A.getRows(); i++) {
            for (int j = 0; j < B.getCols(); j++) {
                double sum = 0.0;
                for (int k = 0; k < A.getCols(); k++) {
                    sum += A(i, k) * B(k, j);
                }
                C(i, j) = sum;
            }
        }
        return C;
    }

bool operator==(const Matrix& A, const Matrix& B)
    {
        if (A.getRows() != B.getRows() || A.getCols() != B.getCols()) {
            return false;
        }
        for (int i = 0; i < A.getRows(); i++) {
            for (int j = 0; j < A.getCols(); j++) {
                if (A(i,j) != B(i,j)) return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& A, const Matrix& B)
    {
        return !(A == B);
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& M)
    {
        for (int i = 0; i < M.getRows(); i++) {
            for (int j = 0; j < M.getCols(); j++) {
                os << M(i, j);
                if (j < M.getCols() - 1) os << " ";
            }
            if (i < M.getRows() - 1) os << "\n";
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2)
    {
        (*this)(0,0) = cos(theta);
        (*this)(0,1) = -sin(theta);
        (*this)(1,0) = sin(theta);
        (*this)(1,1) = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2,2)
    {
        (*this)(0,0) = scale;
        (*this)(0,1) = 0.0;
        (*this)(1,0) = 0.0;
        (*this)(1,1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2,nCols)
    {
        for (int j = 0; j < nCols; j++) {
            (*this)(0,j) = xShift;
            (*this)(1,j) = yShift;
        }
    }

} // end namespace Matrices
