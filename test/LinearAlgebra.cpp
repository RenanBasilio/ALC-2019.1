#include <gtest/gtest.h>
#include <LinearAlgebra.hpp>

TEST(LinearEquations, BackSubstitution) {
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

TEST(LinearEquations, ForwardSubstitution) {
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

TEST(LinearEquations, GaussElimination) {
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

TEST(LinearEquations, GaussJordanElimination) {
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

TEST(MatrixOperations, Inverse) {
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

TEST(LinearEquations, LUDecomposition) {
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

TEST(LinearEquations, CholeskyDecomposition) {
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

TEST(LinearEquations, JacobiIterative) {
    Matrix mtx = Matrix({
        {4, 1, 1},
        {2, 7, 2},
        {1, 5, 8}
    });
    Matrix v = Matrix({{11}, {15}, {23}}, 3, 1);

    Matrix exp = Matrix({{2}, {1}, {2}}, 3, 1);

    Matrix x = solveIterative(mtx, v, Jacobi, 10E-6);

    EXPECT_EQ(x, exp);
}

TEST(LinearEquations, GaussSeidelIterative) {
    Matrix mtx = Matrix({
        {4, 1, 1},
        {2, 7, 2},
        {1, 5, 8}
    });
    Matrix v = Matrix({{11}, {15}, {23}}, 3, 1);

    Matrix exp = Matrix({{2}, {1}, {2}}, 3, 1);

    Matrix x = solveIterative(mtx, v, GaussSeidel, 10E-6);

    EXPECT_EQ(x, exp);
}

TEST(EigenValues, PowerMethod) {
    Matrix mtx = Matrix({
        {1.0, 0.2, 0.0},
        {0.2, 1.0, 0.5},
        {0.0, 0.5, 1.0}
    });

    EXPECT_TRUE(computeGreatestEigenValue(mtx) - 1.539 < 10E-5);
}

TEST(EigenValues, Jacobi) {
    Matrix mtx = Matrix({
        {1.0, 0.2, 0.0},
        {0.2, 1.0, 0.5},
        {0.0, 0.5, 1.0}
    });

    Matrix eigenval = Matrix({
        {1.0,   0.0,   0.0},
        {0.0, 1.539,   0.0},
        {0.0,   0.0, 0.461}
    });

    Matrix eigenvec = Matrix({
        { 0.928, 0.263,  0.263},
        {   0.0, 0.707, -0.707},
        {-0.371, 0.657,  0.657}
    });

    std::pair<Matrix, Matrix> res = computeEigen(mtx);

    EXPECT_EQ(res.first, eigenval);
    EXPECT_EQ(res.second, eigenvec);
}

TEST(MatrixOperations, Determinant) {
    Matrix mtx = Matrix({
        {-2.0, 2.0, -3.0},
        {-1.0, 1.0,  3.0},
        { 2.0, 0.0, -1.0}
    });

    EXPECT_DOUBLE_EQ(determinant(mtx), 18);
}