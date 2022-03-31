/** 
 * 
 * */

#include "Matrix.hpp"
#include <vector>
#include <iostream>
using namespace zich;
Matrix::Matrix(std::vector<double> baseArr, int n, int m)
{
    this->n = n;
    this->m = m;
    std::vector<double> currRow;
    for (int i = 0; i < n*m; i++) {
        currRow.push_back(baseArr.at(i)); // add test for this problem (not using 'at' will not throw but make the test fail and crash) DELETE WHEN DONE
        if (currRow.size() == m) {
            this->mat.push_back(currRow);
            currRow.resize(0);
        } 
    }
}

Matrix Matrix::operator + (Matrix const &other) {
    if (this->n!=other.n||this->m!=other.m) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }

    std::vector<double> baseArr;
    for (int i = 0; i<other.n; i++) {
        for (int j = 0; j<other.m; j++) {
            baseArr.push_back(this->mat.at(i).at(j)+other.mat.at(i).at(j));
        }
    }
    Matrix ans{baseArr, n, m};
    return ans;
};

void Matrix::operator += (Matrix const &other) {
    if (this->n!=other.n||this->m!=other.m) {
        throw std::runtime_error("can't perform operation due to unequal dimensions");
    }
    Matrix temp = *this;
    temp = temp + other;
    this->mat = temp.mat;
}

void Matrix::print() {
    for (size_t i = 0; i < n; i++)
    {
        std::cout << "[\t";
        for (size_t j = 0; j < m; j++)
        {
            std::cout << this->mat.at(i).at(j) << "\t";
        }
        std::cout << "]\n";
    }
    std::cout << "\n";
}


int main() {
    //std::vector<double> identity = {3, 4, -1, 2, 5, 2.4, 3, 3, 7, 4, 4, 11.3};
    /*
    * [ 3, 4, -1, 2 ]
    * [ 5, 2.4, 3, 3 ]
    * [ 7, 4, 4, 11.3]
    * 3, 4, -1, 2, 5, 2.4, 3, 3, 7, 4, 4, 11.3
    */

    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    std::vector<double> id = {3, 4, -1, 2, 5, 2.4, 3, 3, 7};
    Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size
    Matrix b{id, 3, 3};
    a.print();
    b.print();
    a += b;
    a.print();
    b += b;
    a.print();
    b.print();


    return 0;
}


