#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;
// +, += , + unari, -, -=, - unari, A*B | if you can't multiply matrices (different n OR m) throw error 
// >, >=, <, <=, ==, != | if you can't compare (different n OR m) throw error 
// A++, A--, ++A, --A
// x*A, A*x
// <<, >> 

TEST_CASE("Different operations with correct inputs and usage") {
    
    SUBCASE("Comparators") {
        /**
         * @brief This subcase checks for the correctness of ==, !=, >, >=, <, <=. It is required to pass this test inorder to test the rest of the functions.
         */
        Matrix A{{1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3};
        Matrix B{{1, 0, 0, 0, 1, 0, 0, 0, 1}, 3, 3};
        Matrix E{{2, 0, 0, 0, 2, 0, 0, 0, 2}, 3, 3};
        REQUIRE_EQ(A==A, true);
        REQUIRE_EQ(A==B, true);
        REQUIRE_EQ(A==E, false);
        REQUIRE_EQ(A!=A, false);
        REQUIRE_EQ(A!=B, false);
        REQUIRE_EQ(E>A, true);
        REQUIRE_EQ(A>E, false);
        REQUIRE_EQ(B>=A, true);
        REQUIRE_EQ(A<E, true);
        REQUIRE_EQ(E<A, false);
        REQUIRE_EQ(A<=B, true);

    }
    SUBCASE("adders and substractors") {
        /**
         * @brief This subcase checks the correctness of +, +=, + unari, -, -=, - unari
         * This WILL NOT include ++ and -- (postfix and prefix).
         */
        std::vector<double> identity3x3_1 = {1, 0, 0, 0, 1, 0, 0, 0, 1};
        Matrix A{identity3x3_1, 3, 3};
        Matrix B{{0, 0, 0, 0, 0, 0, 0, 0, 0}, 3, 3};
        CHECK_MESSAGE((A+B == A) == true, "\n\toutput:\n" << (A+B) << "\t expected:\n" << A);
        Matrix C{{2, 0, 0, 0, 2, 0, 0, 0, 2}, 3, 3};
        CHECK_MESSAGE((A+A == C) == true, "\n\toutput:\n" << (A+A) << "\t expected:\n" << C); 

        Matrix D{{5, 1, 6, 4, 1, 6, 0, 1}, 4, 2};
        Matrix E{{7, 4, 6, 6, 6, 6, 2, 7}, 4, 2};
        Matrix F{{12, 5, 12, 10, 7, 12, 2, 8}, 4, 2};
        CHECK_MESSAGE((D+E == F) == true, "\n\toutput:\n" << (D+E) << "\t expected:\n" << F); 
        Matrix G {{-2, -3, 0, -2, -5, 0, -2, -6}, 4, 2};
        CHECK_MESSAGE((D-E == G) == true, "\n\toutput:\n" << (D-E) << "\t expected:\n" << G); 
        D+=E;
        CHECK_MESSAGE((D == F) == true, "\n\toutput:\n" << (D) << "\t expected:\n" << F); 
        Matrix H{{5, 1, 6, 4, 1, 6, 0, 1}, 4, 2};
        D-=E;
        CHECK_MESSAGE((D == H) == true, "\n\toutput:\n" << (D) << "\t expected:\n" << H); 
        CHECK_MESSAGE((B-C == -C) == true, "\n\toutput:\n" << (B-C) << "\t expected:\n" << -C);
        Matrix I{{-5, -1, -6, -4, -1, -6, -0, -1}, 4, 2};
        CHECK_MESSAGE((-H == I) == true, "\n\toutput:\n" << (-H) << "\t expected:\n" << I);
        CHECK_MESSAGE((+H == H) == true, "\n\toutput:\n" << (+H) << "\t expected:\n" << H);

        Matrix J{{7, 1, 6, 9}, 2, 2};
        Matrix K{{9, 5, 5, 0}, 2, 2};
        Matrix L{{16, 6, 11, 9}, 2, 2};
        CHECK_MESSAGE((J+K == L) == true, "\n\toutput:\n" << (J+K) << "\t expected:\n" << L);
        Matrix M{{32, 12, 22, 18}, 2, 2};
        CHECK_MESSAGE((J+K+L == M) == true, "\n\toutput:\n" << (J+K+L) << "\t expected:\n" << M);
    }

    SUBCASE("++ and -- postfix and prefix") {
        /**
         * @brief This subcase checks the correctness of ++ and -- (postfix and prefix).
         */
        Matrix A{{5, 1, 6, 4, 1, 6, 0, 1}, 4, 2};
        Matrix A2{{5, 1, 6, 4, 1, 6, 0, 1}, 4, 2}; // for readable output
        Matrix plusplusA{{6, 2, 7, 5, 2, 7, 1, 2}, 4, 2};
        Matrix TWICEplusplusA{{7, 3, 8, 6, 3, 8, 2, 3}, 4, 2};
        CHECK_MESSAGE((++A==plusplusA) == true, "\n\toutput:\n" << (++A2) << "\t expected:\n" << plusplusA);
        CHECK_MESSAGE((A++==plusplusA) == true, "\n\toutput:\n" << (A2++) << "\t expected:\n" << plusplusA);
        CHECK_MESSAGE((A==TWICEplusplusA) == true, "\n\toutput:\n" << A << "\t expected:\n" << TWICEplusplusA);

        CHECK_MESSAGE((A--==TWICEplusplusA) == true, "\n\toutput:\n" << (A2--) << "\t expected:\n" << TWICEplusplusA);
        Matrix originalA{{5, 1, 6, 4, 1, 6, 0, 1}, 4, 2};
        CHECK_MESSAGE((--A==originalA) == true, "\n\toutput:\n" << (--A2) << "\t expected:\n" << originalA);
    }
    SUBCASE("Multipications") {
        /**
         * @brief This subcase checks the correctness of * (scalar and matrices)
         * Make sure scalar multipication works using either side. (i.e 3*A or A*3)
         */
        Matrix A{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 5, 3};
        Matrix B{{1, 2, 3, 2, 1.5, 7.2}, 3, 2};
        Matrix C{{5, 10, 15, 10, 7.5, 36}, 3, 2};
        CHECK_MESSAGE((4.3*A == A) == true, "\n\toutput:\n" << 4.3*A << "\t expected:\n" << A); // A IS ZERO MATRIX
        CHECK_MESSAGE((A*3.1 == A) == true, "\n\toutput:\n" << A*3.1 << "\t expected:\n" << A);
        CHECK_MESSAGE((5*B == C) == true,   "\n\toutput:\n" << 5*B << "\t expected:\n" << C);
        
        Matrix D{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 5, 2};
        CHECK_MESSAGE((A*B == D) == true,   "\n\toutput:\n" << A*B << "\t expected:\n" << D); // A IS ZERO MATRIX
        Matrix E{{0, 1, 9, 6, 0, 6, 0, 5, 1, 7}, 2, 5};
        Matrix BE{{12, 1, 19, 8, 14, 12, 3, 37, 20, 14, 43.2, 1.5, 49.5, 16.2, 50.4}, 3, 5};
        Matrix F{{2,3,2,1,5}, 5, 1};
        Matrix BEF{{143, 197, 458.1}, 3, 1};
        CHECK_MESSAGE((B*E*F == BEF) == true,   "\n\toutput:\n" << B*E*F << "\t expected:\n" << BEF); 
    }

}


TEST_CASE("Bad inputs and wrong usage") {
    SUBCASE("Constructor") {
        int failed = 0;
        try {Matrix C{{0,0,0,0}, 2, 1};} catch (const std::exception&) {failed++;}
        try {Matrix C{{}, 0, 1};} catch (const std::exception&) {failed++;}
        try {Matrix C{{0,0,0,0}, 2, -1};} catch (const std::exception&) {failed++;}
        try {Matrix C{{0,0,0,0}, 2, 2};} catch (const std::exception&) {CHECK(false);}
        try {Matrix C{{0,0}, 1, 2};} catch (const std::exception&) {CHECK(false);}
        if (failed!=3) CHECK_MESSAGE(false, "An exepction was not thrown when needed!");;
    }
    
    Matrix A{{0, 0, 0, 0, 0, 2, 0, 0, 0, 0}, 5, 2};
    Matrix B{{1, 2, 3, 2, 1.5, 7.2, 4, 3}, 2, 4};
    SUBCASE("Comparators") {
        /**
         * @brief Comparsion of any kind should only be possible between two matrices with equal dimensios
         * 
         */
        bool test;
        int failed = 0;
        try {  
            test = A==A;
            test = A >= A;
            test = A <= A;
            test = A != A;
            test = A > A;
            test = A < A;
        } catch (const std::exception&) { 
            CHECK_MESSAGE(false, "An exception occurred when it wasn't needed!");
        }
        try { test = A==B ;} catch(const std::exception&) {failed++;}
        try { test = A>=B ;} catch(const std::exception&) {failed++;}
        try { test = A<=B ;} catch(const std::exception&) {failed++;}
        try { test = A!=B;} catch(const std::exception&) {failed++;}
        try { test = A>B ;} catch(const std::exception&) {failed++;}
        try { test = A<B ;} catch(const std::exception&) {failed++;}
        if (failed!=6) CHECK_MESSAGE(false, "An exepction was not thrown when needed!");

        
    }
    SUBCASE("adders and substractors") {
        /**
         * @brief adding and substracting should only be possible between matrices with equal dimensions.
         * 
         */
        CHECK_THROWS(A+B);
        CHECK_NOTHROW(A+A);
        CHECK_THROWS(A+B+B);
        CHECK_THROWS(B+B+A);
        CHECK_NOTHROW(B+B+B);

        CHECK_THROWS(A-B);
        CHECK_NOTHROW(A-A);
        CHECK_THROWS(A-B+B);
        CHECK_THROWS(B-B-A);
        CHECK_NOTHROW(B-B-B);

        CHECK_THROWS(B+B-A);
        CHECK_NOTHROW(B-B+B);
    }

    SUBCASE("Multipications") {
        /**
         * @brief Matrix multipication of kind A * B, should only be possible
         * when A is iXn and B is nXj, for each i, n and j. Notice that A and B share n.
         */
        CHECK_NOTHROW(A*B);
        CHECK_THROWS(B*A);
        CHECK_THROWS(A*A);
        CHECK_THROWS(B*B);
        Matrix C{{1,1,1,1}, 2, 2};
        CHECK_NOTHROW(C*C);
        CHECK_THROWS(C*A);
        CHECK_NOTHROW(A*C);
        CHECK_THROWS(B*C);
        CHECK_NOTHROW(C*B);
    }
}
