#include <gtest/gtest.h>
#include <LinearAlgebra.hpp>

TEST(LinearAlgebra, BackSubstitution) {
    Matrix A = Matrix({
        {5, -4, 1, 0},
        {0, 14.0/5.0, -16.0/5.0, 1},
        {0, 0, 15.0/7.0, -20.0/7.0},
        {0, 0, 0, 35.0/42.0}
    });
    Matrix b = Matrix({{-1}, {6.0/5.0}, {18.0/7.0}, {6}});
    Matrix exp = Matrix({{5.8}, {10.2}, {10.8}, {7.2}});

    Matrix x = solveBackSubstitution(A, b);

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, ForwardSubstitution) {
    Matrix A = Matrix({
        {  3,  0,  0,  0 },
        { -1,  1,  0,  0 },
        {  3, -2, -1,  0 },
        {  1, -2,  6,  2 }
    });
    Matrix b = Matrix({{5}, {6}, {4}, {2}});
    Matrix exp = Matrix({{5.0/3.0}, {23.0/3.0}, {-43.0/3.0}, {305.0/6.0}});

    Matrix x = solveForwardSubstitution(A, b);

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

TEST(LinearAlgebra, LUDecomposition) {
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

    Matrix x = solveLUDecomp(mtx, v);

    EXPECT_EQ(x, exp);
}

TEST(LinearAlgebra, CholeskyDecomposition) {
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

    Matrix x = solveCholeskyDecomp(mtx, v);

    EXPECT_EQ(x, exp);
}