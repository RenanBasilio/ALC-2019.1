#include <main.hpp>

int main(int argc, char* argv[]) {
    Matrix mtx = Matrix({
        { 5, -4,  1,  0},
        {-4,  6, -4,  1},
        { 1, -4,  6, -4},
        { 0,  1, -4,  5}
    });
    Matrix v = Matrix({
        {-1}, {2}, {1}, {3}
    });

    Matrix mtx2 = Matrix({
        {2, 5},
        {3, 1}
    });
    Matrix v2 = Matrix({
        {16}, {11}
    }, 2, 1);

    Matrix t = Matrix({
        {4, 1, 1},
        {2, 7, 2},
        {1, 5, 8}
    });
    Matrix v3 = Matrix({
        {11}, {15}, {23}
    }, 3, 1);

    std::cout << solveIterative(t, v3, IterativeMethod::Jacobi, 10E-9) << std::endl;
    std::cout << solveGaussElim(t, v3) << std::endl;

    return 0;
}