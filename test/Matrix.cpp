#include <gtest/gtest.h>
#include <Matrix.hpp>
#include <random>
#include <cstring>


Matrix generateTestMatrix(size_t rows, size_t columns) {

    Matrix mtx = Matrix(rows, columns);

    std::uniform_real_distribution<double> unif(0, 100);
    std::default_random_engine re;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            mtx.at(i, j) = unif(re);
        }
    }
    std::cout << "Generated test matrix: " << std::endl << mtx <<std::endl;
    return mtx;

}

TEST(MatrixBasics, InitializeZeroMatrix) {
    Matrix mtx = Matrix(5,3);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 3; j++) {
            EXPECT_EQ(mtx.at(i, j), 0) << mtx;
        }
    }
}

TEST(MatrixBasics, InitializeColumnVector) {
    double val[4] = {1.0, 8.5, 4.7, 7.2};
    Matrix mtx = Matrix({{val[0]}, {val[1]}, {val[2]}, {val[3]}});
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(mtx.at(i, 0), val[i]) << mtx;
        EXPECT_EQ(mtx.at(i), val[i]) << mtx;
        EXPECT_EQ(std::memcmp(mtx.getColumn(0).data(), val, sizeof(val)), 0) << mtx;
    }
}

TEST(MatrixBasics, InitializeRowVector) {
    double val[7] = {1.0, 8.5, 4.7, 7.2, 9.6, 15.4, -5.4};
    Matrix mtx = Matrix({{val[0], val[1], val[2], val[3], val[4], val[5], val[6]}});
    for (size_t i = 0; i < 7; i++) {
        EXPECT_EQ(mtx.at(0, i), val[i]) << mtx;
        EXPECT_EQ(std::memcmp(mtx.getRow(0).data(), val, sizeof(val)), 0) << mtx;
    }
}

TEST(MatrixBasics, InitializeSquareMatrixAndAccessorOperator) {

    std::vector<std::vector<double>> val(5, std::vector<double>(5,0));
    std::uniform_real_distribution<double> unif(0, 100);
    std::default_random_engine re;
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            val.at(i).at(j) = unif(re);
        }
    }

    Matrix mtx = Matrix( {  { val[0][0], val[0][1], val[0][2], val[0][3], val[0][4] },
                            { val[1][0], val[1][1], val[1][2], val[1][3], val[1][4] },
                            { val[2][0], val[2][1], val[2][2], val[2][3], val[2][4] },
                            { val[3][0], val[3][1], val[3][2], val[3][3], val[3][4] },
                            { val[4][0], val[4][1], val[4][2], val[4][3], val[4][4] } } );

    EXPECT_EQ(mtx.ncolumns(), 5);
    EXPECT_EQ(mtx.nrows(), 5);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            EXPECT_EQ(mtx.at(i, j), val.at(i).at(j)) << "i = " << i << ", j = " << j << ", matrix:" << std::endl << mtx;
        }
    }
}

TEST(MatrixBasics, Equality) {
    Matrix mtx1 = Matrix( { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    Matrix mtx2 = Matrix( { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );

    ASSERT_TRUE(mtx1 == mtx2);

}

TEST(MatrixBasics, InsertRow) {
    Matrix mtx = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    Matrix exp = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9},
                            {10, 11, 12} } );
    mtx.insertRow(3, {10, 11, 12});

    EXPECT_EQ(mtx, exp);
}

TEST(MatrixBasics, InsertColumn) {
    Matrix mtx = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    Matrix exp = Matrix(  { {1, 2, 3, 10},
                            {4, 5, 6, 11},
                            {7, 8, 9, 12}} );

    mtx.insertColumn(3, {10, 11, 12});

    EXPECT_EQ(mtx, exp);
}

TEST(MatrixBasics, RemoveRow) {
    Matrix mtx = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9},
                            {10, 11, 12} } );
    Matrix exp = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    
    mtx.removeRow(3);

    EXPECT_EQ(mtx, exp);
}

TEST(MatrixBasics, RemoveColumn) {
    Matrix mtx = Matrix(  { {1, 2, 3, 10},
                            {4, 5, 6, 11},
                            {7, 8, 9, 12}} );
    Matrix exp = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    
    mtx.removeColumn(3);

    EXPECT_EQ(mtx, exp);
}

TEST(MatrixBasics, SwapRow) {
    Matrix mtx = Matrix(  { {1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9} } );
    Matrix exp = Matrix(  { {1, 2, 3},
                            {7, 8, 9},
                            {4, 5, 6}, } );
    
    mtx.swapRow(1, 2);

    EXPECT_EQ(mtx, exp);
    
}

TEST(MatrixOperations, Transpose) {

    Matrix mtx = generateTestMatrix(3, 7);

    Matrix tr = mtx.transpose();

    for (size_t i = 0; i < mtx.nrows(); i++) {
        for (size_t j = 0; j < mtx.ncolumns(); j++) {
            EXPECT_EQ(mtx.at(i, j), tr.at(j, i));
        }
        EXPECT_EQ(mtx.getRow(i), tr.getColumn(i));
    }
}

TEST(MatrixOperations, AddScalar) {
    Matrix mtx1 = generateTestMatrix(3, 7);

    Matrix mtx2 = mtx1;

    for ( size_t i = 0; i < mtx1.nrows(); i++ ) {
        for ( size_t j = 0; j < mtx1.ncolumns(); j++) {
            mtx2.at(i, j) += 2;
        }
    }

    EXPECT_EQ(mtx2, (mtx1 + 2));
    EXPECT_EQ(mtx2, (2 + mtx1));
    EXPECT_EQ((2 + mtx1), (mtx1 + 2));
}

TEST(MatrixOperations, SubtractScalar) {
    Matrix mtx1 = generateTestMatrix(3, 7);

    Matrix mtx2 = mtx1;

    for ( size_t i = 0; i < mtx1.nrows(); i++ ) {
        for ( size_t j = 0; j < mtx1.ncolumns(); j++) {
            mtx2.at(i, j) -= 2;
        }
    }

    EXPECT_EQ(mtx2, (mtx1 - 2));
    EXPECT_EQ(mtx2, (2 - mtx1));
    EXPECT_EQ((2 - mtx1), (mtx1 - 2));
}

TEST(MatrixOperations, MultiplyScalar) {
    Matrix mtx1 = generateTestMatrix(3, 7);

    Matrix mtx2 = mtx1;

    for ( size_t i = 0; i < mtx1.nrows(); i++ ) {
        for ( size_t j = 0; j < mtx1.ncolumns(); j++) {
            mtx2.at(i, j) *= 2;
        }
    }

    EXPECT_EQ(mtx2, (mtx1 * 2));
    EXPECT_EQ(mtx2, (2 * mtx1));
    EXPECT_EQ((2 * mtx1), (mtx1 * 2));
}

TEST(MatrixOperations, DivideScalar) {
    Matrix mtx1 = generateTestMatrix(3, 7);

    Matrix mtx2 = mtx1;
    Matrix mtx3 = mtx1;

    for ( size_t i = 0; i < mtx1.nrows(); i++ ) {
        for ( size_t j = 0; j < mtx1.ncolumns(); j++) {
            mtx2.at(i, j) = mtx2.at(i, j) / 2;
            mtx3.at(i, j) = 2 / mtx3.at(i, j);
        }
    }

    EXPECT_EQ(mtx2, (mtx1 / 2));
    EXPECT_EQ(mtx3, (2 / mtx1));
}

TEST(MatrixOperations, MultiplyMatrix) {
    Matrix mtx1 = Matrix( { {1,  2, 7}, 
                            {9, 15, 4}, 
                            {2, 28, 6}, 
                            {66,10, 0} } );
    Matrix mtx2 = Matrix( { {1, 1}, 
                            {2, 8}, 
                            {4, 2} } );

    Matrix res_expected = Matrix( { { 33, 31}, 
                                    { 55, 137}, 
                                    { 82, 238},
                                    { 86, 146} } );

    EXPECT_EQ(res_expected, (mtx1 * mtx2));
}

