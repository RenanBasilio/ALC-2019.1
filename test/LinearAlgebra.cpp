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

    Matrix x = solveRetroSubstitution(A, b);

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

    Matrix x = solveRetroSubstitution(mtx);

    std::cout << mtx << std::endl;

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, GaussElimination) {
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

    Matrix x = solveGaussElim(mtx, v);

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, GaussJordanElimination) {
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

    Matrix x = solveGaussJordanElim(mtx, v);

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, Inverse) {
    Matrix mtx = Matrix({
        { 5, -4,  1,  0},
        {-4,  6, -4,  1},
        { 1, -4,  6, -4},
        { 0,  1, -4,  5}
    });
    Matrix inv = Matrix({
        { 1.2, 1.6, 1.4, 0.8},
        { 1.6, 2.6, 2.4, 1.4},
        { 1.4, 2.4, 2.6, 1.6},
        { 0.8, 1.4, 1.6, 1.2}
    });

    Matrix x = computeInverse(mtx);

    EXPECT_EQ(x, inv);
    EXPECT_EQ(mtx*x, Matrix::Identity(4));
}