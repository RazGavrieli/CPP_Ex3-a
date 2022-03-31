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
        throw std::runtime_error("size can't be negative");
    }
    unsigned int rows = (unsigned int)signedrows;
    unsigned int cols = (unsigned int)signedcols;
    this->rows = rows;
    this->cols = cols;
    std::vector<double> currRow;
    for (size_t i = 0; i < rows*cols; i++) {
        currRow.push_back(baseArr.at(i)); // add test for this problem (not using 'at' will not throw but make the test fail and crash) DELETE WHEN DONE
        if (currRow.size() == cols) {
            this->mat.push_back(currRow);
            currRow.resize(0);
        } 
    }
}

Matrix::~Matrix() {}

double Matrix::operator () (unsigned int r,unsigned int c)const{ return mat.at(r).at(c);} // this function is a test

Matrix Matrix::operator + (Matrix const &other) {
    if (this->rows!=other.rows||this->cols!=other.cols) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }

    std::vector<double> baseArr;
    for (size_t i = 0; i<other.rows; i++) {
        for (size_t j = 0; j<other.cols; j++) {
            baseArr.push_back(this->mat.at(i).at(j)+other.mat.at(i).at(j));
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
            baseArr.push_back(this->mat.at(i).at(j));
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
            baseArr.push_back(-1*this->mat.at(i).at(j));
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


void Matrix::print() {
    Matrix temp = *this;
    for (size_t i = 0; i < rows; i++)
    {
        std::cout << "[\t";
        for (size_t j = 0; j < cols; j++)
        {
            std::cout << temp(i,j) << "\t"; // this is a test for (i,j) instead of .at().at()
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
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


