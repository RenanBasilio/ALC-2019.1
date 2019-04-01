#include <gtest/gtest.h>
#include <LinearAlgebra.hpp>

TEST(LinearAlgebra, RetroSubstitution) {
    Matrix mtx = Matrix({
        {5, -4, 1, 0, -1},
        {0, 14.0/5.0, -16.0/5.0, 1, 6.0/5.0},
        {0, 0, 15.0/7.0, -20.0/7.0, 18.0/7.0},
        {0, 0, 0, 35.0/42.0, 6}
    });
    Matrix exp = Matrix({5.8, 10.2, 10.8, 7.2});

    Matrix x = ret_subs(mtx);

    EXPECT_TRUE(x == exp);
}