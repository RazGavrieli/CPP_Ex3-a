/** 
 * 
 * */

#ifndef Matrix_H
#define Matrix_H

#include <vector>


namespace zich {
class Matrix
{
    std::vector<std::vector<double>> mat;
    unsigned int rows, cols; // as in matrix is n X m (n rows by m collums)


// +, += , + unari, -, -=, - unari
// >, >=, <, <=, ==, != | if you can't compare (different n OR m) throw error 
// A++, A--, ++A, --A
// x*A
// A*B | if you can't multiply matrices (different n OR m) throw error 
// <<, >> 

public:
    Matrix(std::vector<double> baseArr, int rows, int cols);
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
    bool operator < (Matrix const &other);
    bool operator <= (Matrix const &other);
    bool operator == (Matrix const &other);
    bool operator != (Matrix const &other);

    Matrix& operator ++ (); // ++Prefix
    Matrix operator ++ (int); // Postfix++
    Matrix& operator -- (); // --Prefix
    Matrix operator -- (int); // Postfix--

    Matrix operator *(int const &scalar);
    friend Matrix operator * (Matrix const &m1, Matrix const &m2);

    //void operator << (Matrix const &other); // why get "other"?
    //void operator >> (Matrix const &other); // why get "other"?

    void print();
};
}
#endif
