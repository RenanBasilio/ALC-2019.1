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

    std::cout << solveJacobi(mtx2, v2) << std::endl;

    return 0;
}