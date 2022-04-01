/** 
 * 
 * */

#include "Matrix.hpp"
#include <vector>
#include <iostream>
using namespace zich;
Matrix::Matrix(std::vector<double> baseArr, int signedrows, int signedcols)
{
    if (signedrows<1||signedcols<1) {
        throw std::runtime_error("size must be a positive integer");
    }
    unsigned int rows = (unsigned int)signedrows;
    unsigned int cols = (unsigned int)signedcols;
    if (baseArr.size()>rows*cols) {
        throw std::runtime_error("The given vector won't fit into the size of the Matrix");
    }
    this->rows = rows;
    this->cols = cols;
    std::vector<double> currRow;
    for (size_t i = 0; i < rows*cols; i++) {
        if (i<baseArr.size()) {
            currRow.push_back(baseArr.at(i));
        } else {
            currRow.push_back(0);
        }
        if (currRow.size() == cols) {
            this->mat.push_back(currRow);
            currRow.resize(0);
        } 
    }
}

Matrix::Matrix(std::vector<std::vector<double>> mat, unsigned int rows, unsigned int cols) {
    this->rows = rows;
    this->cols = cols;
    this->mat = std::move(mat);
}
Matrix::~Matrix() {}

double Matrix::operator () (unsigned int r,unsigned int c)const{ return mat.at(r).at(c);} // this function is a test

double Matrix::at(unsigned int r,unsigned int c) const{ 
    if (r>=rows||c>=cols) {
        throw std::runtime_error("out of bounds!");
    }
    return mat.at(r).at(c); 
    }

bool Matrix::operator==(Matrix const &other) {
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (at(i,j)!=other.at(i,j)) {
                return false;
            }
        }
    }
    
    return true;
}

bool Matrix::operator!=(Matrix const &other) {
    return !(*(this)==other);
}

bool Matrix::operator > (Matrix const &other){
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis>sumOther;        
}
bool Matrix::operator >= (Matrix const &other){
    if (cols!=other.cols||rows!=other.rows) {
        throw std::runtime_error("can't perform comparsion due to unequal dimensions");
    }
    double sumThis = 0;
    double sumOther = 0;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            sumThis += at(i,j);
            sumOther += other.at(i,j);
        }
    }
    return sumThis>=sumOther;        
}

bool Matrix::operator < (Matrix other){
    return other>*this;
}
bool Matrix::operator <= (Matrix other){
    return other>=*this;
}

Matrix Matrix::operator + (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }

    std::vector<double> baseArr;
    for (size_t i = 0; i<other.rows; i++) {
        for (size_t j = 0; j<other.cols; j++) {
            baseArr.push_back(at(i,j)+other.at(i,j));
        }
    }
    Matrix ans{baseArr, static_cast<int>(rows), static_cast<int>(cols)};
    return ans;
};

void Matrix::operator += (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix temp = *this;
    temp = temp + other;
    this->mat = temp.mat;
}

Matrix Matrix::operator + () {
    
    std::vector<double> baseArr;
    for (size_t i = 0; i<this->rows; i++ ) {
        for (size_t j = 0; j < this->cols; j++)
        {
            baseArr.push_back(at(i,j));
        }
    }
    
    Matrix ans{baseArr, (int)this->rows, (int)this->cols};
    return ans;
}

Matrix Matrix::operator - () {
    std::vector<double> baseArr;
    for (size_t i = 0; i<this->rows; i++ ) {
        for (size_t j = 0; j < this->cols; j++)
        {
            baseArr.push_back(-1*at(i,j));
        }
    }
    
    Matrix ans{baseArr, (int)this->rows, (int)this->cols};
    return ans;
}

Matrix Matrix::operator - (Matrix other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix ans = *this + (-other);
    return ans;
}

void Matrix::operator -= (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix temp = *this;
    temp = temp - other;
    this->mat = temp.mat;
}

Matrix& Matrix::operator ++ () {// ++Prefix
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] += 1;
        }
    }
    return *this;
}

Matrix Matrix::operator ++ (int) {// Postfix++
    Matrix temp = *this;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] += 1;
        }
    }
    return temp;
}

Matrix& Matrix::operator -- () {// --Prefix
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] -= 1;
        }
    }
    return *this;
}

Matrix Matrix::operator -- (int) {// Postfix--
    Matrix temp = *this;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            mat[i][j] -= 1;
        }
    }
    return temp;
}

Matrix Matrix::operator * (Matrix const &other) {
    if (this->cols!=other.rows) {
        throw std::runtime_error("Matrix multipication requires specific dimensions properties!");
    }
    std::vector<std::vector<double>> multMat;
    std::vector<double> currRow;
    for (size_t i = 0; i < this->rows; i++)
    {
        currRow.resize(0);
        for (size_t j = 0; j < other.cols; j++)
        {
            currRow.push_back(0);
        }
        multMat.push_back(currRow);
    }
    
    for (size_t i = 0; i < this->rows; i++)
    {
        for (size_t j = 0; j < other.cols; j++)
        {
            for (size_t k = 0; k < this->cols /*=other.rows*/; k++)
            {
                multMat[i][j] += at(i, k) * other.at(k, j);
            }
        }
    }
    
    Matrix ans{multMat, this->rows, other.cols}; 
    return ans;
}

Matrix Matrix::operator * (double const &scalar) {
    Matrix ans = *this;
    for (size_t i = 0; i < ans.rows; i++)
    {
        for (size_t j = 0; j < ans.cols; j++)
        {
            ans.mat[i][j] *= scalar;
        }
    }
    return ans;
}

void Matrix::operator *= (double const &scalar) {
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                this->mat[i][j] *= scalar;
            }
        }
    }

namespace zich {

    Matrix operator * (double const &scalar, Matrix other) {
        Matrix ans = other;
        for (size_t i = 0; i < ans.rows; i++)
        {
            for (size_t j = 0; j < ans.cols; j++)
            {
                ans.mat[i][j] *= scalar;
            }
        }
        return ans;
    }


    std::ostream& operator << (std::ostream& os, Matrix other) {
        for (size_t i = 0; i < other.rows; i++)
        {
            os << "[";
            for (size_t j = 0; j < other.cols; j++)
            {
                if (j==other.cols-1) {
                os << other.at(i,j); 
                } else {                                  
                os << other.at(i,j) << " "; 
                }
            }
            os << "]\n";
        }
        os << "\n";

        return os;
    }
}

// int main() {
//     //std::vector<double> identity = {3, 4, -1, 2, 5, 2.4, 3, 3, 7, 4, 4, 11.3};
//     /*
//     * [ 3, 4, -1, 2 ]
//     * [ 5, 2.4, 3, 3 ]
//     * [ 7, 4, 4, 11.3]
//     * 3, 4, -1, 2, 5, 2.4, 3, 3, 7, 4, 4, 11.3
//     */

//     std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
//     std::vector<double> id = {3, 4, -1, 2, 5, 2.4, 3, 3, 7};
//     Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size
//     Matrix b{id, 3, 3};
//     a.print();
//     b.print();
//     a += b;
//     a.print();
//     b += b;
//     a.print();
//     b.print();


//     return 0;
// }


