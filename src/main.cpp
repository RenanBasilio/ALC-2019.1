#include <main.hpp>

int main(int argc, char* argv[]) {

    Matrix mtx = Matrix({
        { 16,  9,  8,  7,  6,  5,  4,  3,  2,  1},
        {  9, 17,  9,  8,  7,  6,  5,  4,  3,  2},
        {  8,  9, 18,  9,  8,  7,  6,  5,  4,  3},
        {  7,  8,  9, 19,  9,  8,  7,  6,  5,  4},
        {  6,  7,  8,  9, 18,  9,  8,  7,  6,  5},
        {  5,  6,  7,  8,  9, 17,  9,  8,  7,  6},
        {  4,  5,  6,  7,  8,  9, 16,  9,  8,  7},
        {  3,  4,  5,  6,  7,  8,  9, 15,  9,  8},
        {  2,  3,  4,  5,  6,  7,  8,  9, 14,  9},
        {  1,  2,  3,  4,  5,  6,  7,  8,  9, 13}
    });

    Matrix vec = Matrix({
        {4}, {0}, {8}, {0}, {12}, {0}, {8}, {0}, {4}, {0}
    }, 10);

    Matrix x1 = solveLUDecomp(mtx, vec);
    Matrix x2 = solveCholeskyDecomp(mtx, vec);

    std::cout << x1.transpose() << std::endl;

    return 0;
}