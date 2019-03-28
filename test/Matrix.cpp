#include <gtest/gtest.h>
#include <Matrix.hpp>
#include <random>
#include <cstring>


TEST(MatrixTests, InitializeZeroMatrix) {
    Matrix mtx = Matrix(5,3);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(mtx.at(i, j), 0) << mtx.toString();
        }
    }
}

TEST(MatrixTests, InitializeColumnVector) {
    double val[4] = {1.0, 8.5, 4.7, 7.2};
    Matrix mtx = Matrix({val[0], val[1], val[2], val[3]});
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(mtx.at(i, 0), val[i]) << mtx.toString();
        EXPECT_EQ(mtx.at(i), val[i]) << mtx.toString();
        EXPECT_EQ(std::memcmp(mtx.getColumn(0).data(), val, sizeof(val)), 0) << mtx.toString();
    }
}

TEST(MatrixTests, InitializeRowVector) {
    double val[7] = {1.0, 8.5, 4.7, 7.2, 9.6, 15.4, -5.4};
    Matrix mtx = Matrix({{val[0], val[1], val[2], val[3], val[4], val[5], val[6]}});
    for (size_t i = 0; i < 7; i++) {
        EXPECT_EQ(mtx.at(0, i), val[i]) << mtx.toString();
        EXPECT_EQ(std::memcmp(mtx.getRow(0).data(), val, sizeof(val)), 0) << mtx.toString();
    }
}

TEST(MatrixTests, InitializeSquareMatrix) {

    double val[5][5];
    std::uniform_real_distribution<double> unif(0, 100);
    std::default_random_engine re;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            val[i][j] = unif(re);
        }
    }

    Matrix mtx = Matrix( {  { val[0][0], val[0][1], val[0][2], val[0][3], val[0][4] },
                            { val[1][0], val[1][1], val[1][2], val[1][3], val[1][4] },
                            { val[2][0], val[2][1], val[2][2], val[2][3], val[2][4] },
                            { val[3][0], val[3][1], val[3][2], val[3][3], val[3][4] },
                            { val[4][0], val[4][1], val[4][4], val[4][3], val[4][4] } } );

    EXPECT_EQ(mtx.ncolumns(), 5);
    EXPECT_EQ(mtx.nrows(), 5);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            EXPECT_EQ(mtx.at(i, j), val[i][j]) << "i = " << i << ", j = " << j << ", matrix:" << std::endl << mtx.toString();
        }
    }
}

Matrix generateTestMatrix(double rows, double columns) {

    Matrix mtx = Matrix(rows, columns);

    std::uniform_real_distribution<double> unif(0, 100);
    std::default_random_engine re;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            mtx.at(i, j) = unif(re);
        }
    }

    return mtx;

}

TEST(MatrixTests, TransposeColumnVector) {

    Matrix mtx = generateTestMatrix(1, 4);

    Matrix tr = mtx.transpose();

    for (size_t i = 0; i < mtx.nrows(); i++) {
        for (size_t j = 0; j < mtx.ncolumns(); j++) {
            EXPECT_EQ(tr.at(i, j), mtx.at(j, i)) << mtx.toString();
        }
        EXPECT_EQ(tr.getRow(i), mtx.getColumn(i)) << mtx.toString();
    }
}

TEST(MatrixTests, TransposeSquareMatrix) {

    Matrix mtx = generateTestMatrix(5, 5);

    Matrix tr = mtx.transpose();

    for (size_t i = 0; i < mtx.nrows(); i++) {
        for (size_t j = 0; j < mtx.ncolumns(); j++) {
            EXPECT_EQ(tr.at(i, j), mtx.at(j, i)) << mtx.toString();
        }
        EXPECT_EQ(tr.getRow(i), mtx.getColumn(i)) << mtx.toString();
    }
}

TEST(MatrixTests, TransposeMatrix) {

    Matrix mtx = generateTestMatrix(3, 7);

    Matrix tr = mtx.transpose();

    for (size_t i = 0; i < mtx.nrows(); i++) {
        for (size_t j = 0; j < mtx.ncolumns(); j++) {
            EXPECT_EQ(tr.at(i, j), mtx.at(j, i)) << mtx.toString();
        }
        EXPECT_EQ(tr.getRow(i), mtx.getColumn(i)) << mtx.toString();
    }
}