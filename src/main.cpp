#include <main.hpp>

int main(int argc, char* argv[]) {
    Matrix mtx1 = Matrix( { {1.2,  3.4, 1.6}, 
                            {8.4, 0.48, 9.2}, 
                            {9.3,  3.4, 7.0}, 
                            {2.0,  3.5, 1.0} } );
    Matrix mtx2 = Matrix( { {9.8, 6.2}, 
                            {5.4, 5.2}, 
                            {2.5, 1.9} } );

    Matrix res = Matrix( { { 34.12,  28.16}, 
                           {107.912, 72.056}, 
                           {127,     88.64},
                           { 41,     32.5} } );

    Matrix res_ = mtx1 * mtx2;

    std::cout << (res_ == res) << std::endl;

    return 0;
}