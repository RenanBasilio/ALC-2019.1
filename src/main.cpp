#include <main.hpp>

int main(int argc, char* argv[]) {
    SqMatrix test = SqMatrix(2, { { 1, 2 }, 
                                  { 3, 4 } });
    std::cout << "Matriz 1: " << std::endl << test.toString() << std::endl;
    std::cout << "Transposta: " << std::endl << test.transpose().toString() << std::endl;

    Matrix test2(5, 5);
    std::cout << "Nao-Alocada: " << std::endl << test2.toString() << std::endl;
    return 0;
}