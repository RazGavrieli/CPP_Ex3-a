#ifndef Matrix_H
#define Matrix_H

#include <vector>
#include <iostream>

namespace zich {
class Matrix
{
    std::vector<std::vector<double>> mat;
    unsigned int rows, cols;
 
    double at(unsigned int row, unsigned int col) const;
    
public:
    Matrix(std::vector<double> baseArr, int rows, int cols);
    Matrix(std::vector<std::vector<double>> mat, unsigned int rows, unsigned int cols);
    ~Matrix();
    
    double operator()(unsigned int row, unsigned int col) const; // this function is a test
    
    Matrix operator + (Matrix const &other); 
    void operator += (Matrix const &other);
    Matrix operator + ();

    Matrix operator - (Matrix other);
    void operator -= (Matrix const &other);
    Matrix operator - ();

    bool operator > (Matrix const &other);
    bool operator >= (Matrix const &other);
    bool operator < (Matrix other);
    bool operator <= (Matrix other);
    bool operator == (Matrix const &other);
    bool operator != (Matrix const &other);

    Matrix& operator ++ (); // ++Prefix
    Matrix operator ++ (int); // Postfix++
    Matrix& operator -- (); // --Prefix
    Matrix operator -- (int); // Postfix--

    Matrix operator * (double const &scalar);
    friend Matrix operator * (double const &scalar, Matrix other);
    Matrix operator * (Matrix const &other);
    void operator *= (double const &scalar);
    void operator *= (Matrix const &other);


    friend std::ostream& operator << (std::ostream&, Matrix const &other);
    friend std::istream& operator >> (std::ostream&, Matrix &other);


};
}
#endif
