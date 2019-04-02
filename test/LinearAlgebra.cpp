#include <gtest/gtest.h>
#include <LinearAlgebra.hpp>

TEST(LinearAlgebra, RetroSubstitution) {
    Matrix A = Matrix({
        {5, -4, 1, 0},
        {0, 14.0/5.0, -16.0/5.0, 1},
        {0, 0, 15.0/7.0, -20.0/7.0},
        {0, 0, 0, 35.0/42.0}
    });
    Matrix b = Matrix({{-1}, {6.0/5.0}, {18.0/7.0}, {6}});
    Matrix exp = Matrix({{5.8}, {10.2}, {10.8}, {7.2}});

    Matrix x = ret_subs(A, b);

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, RetroSubstitutionAugmented) {
    Matrix mtx = Matrix({
        {5, -4, 1, 0, -1},
        {0, 14.0/5.0, -16.0/5.0, 1, 6.0/5.0},
        {0, 0, 15.0/7.0, -20.0/7.0, 18.0/7.0},
        {0, 0, 0, 35.0/42.0, 6}
    });
    Matrix exp = Matrix({{5.8}, {10.2}, {10.8}, {7.2}});

    Matrix x = ret_subs(mtx);

    std::cout << mtx << std::endl;

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, GaussianElimination) {
    Matrix mtx = Matrix({
        { 5, -4,  1,  0},
        {-4,  6, -4,  1},
        { 1, -4,  6, -4},
        { 0,  1, -4,  5}
    });
    Matrix v = Matrix({
        {-1}, {2}, {1}, {3}
    });

    Matrix exp = Matrix({{5.8}, {10.2}, {10.8}, {7.2}});

    Matrix x = gauss(mtx, v);

    EXPECT_EQ(x, exp);
}