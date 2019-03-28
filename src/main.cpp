#include <main.hpp>

int main(int argc, char* argv[]) {
    Matrix test = Matrix( { { 1, 2, 5 }, 
                            { 3, 4, 6 },
                            { 7, 6, 1 } });
    std::cout << "Matriz 1: " << std::endl << test.toString() << std::endl;
    std::cout << "Transposta: " << std::endl << test.transpose().toString() << std::endl;

    // Test ATA
    Matrix mult_test = test.transpose() * test;
    std::cout << "ATA: " << std::endl << mult_test.toString() << std::endl;

    Matrix vect = Matrix( {1, 5, 7} );
    std::cout << "b: " << std::endl << vect.toString() << std::endl;
    mult_test = test * vect;
    std::cout << "Ab: " << std::endl << mult_test.toString() << std::endl;


    return 0;
}