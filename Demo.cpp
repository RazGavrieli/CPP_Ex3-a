/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 * 
 * Edited by Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Matrix.hpp"
using namespace zich;

// int main() {
  
//   std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
//   std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
//   Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size
//   cout << a << endl;
//   /* prints [1 0 0]
//             [0 1 0]
//             [0 0 1]*/

//   cout << (-a) << endl;
//   /* prints [-1 0 0]
//             [0 -1 0]
//             [0 0 -1]*/
//   cout << (3*a) << endl;
//   /* prints [-3 0 0]
//             [0 -3 0]
//             [0 0 -3]*/

//   Matrix b{arr, 3, 3};
//   a *= -3;
//   cout << (a+b) << endl;  // prints the 0 matrix
//   cout << (b-a) << endl;
//   /* prints [6 0 0]
//             [0 6 0]
//             [0 0 6]*/

//   cout << "End of demo!" << endl;
//   return 0;
// }

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
    (a-b).print();
    b.print();

    return 0;
}