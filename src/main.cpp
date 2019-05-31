#include <main.hpp>

int main(int argc, char* argv[]) {

    std::cout << "=========================== Trabalho 1 ===========================" << std::endl << std::endl;

    Matrix A = Matrix({
        { 19,  5,  3,  1,  2,  1 },
        {  5, 20,  5,  3,  1,  2 },
        {  3,  5, 19,  5,  1,  2 },
        {  1,  3,  5, 16,  1,  2 },
        {  2,  1,  1,  1, 15,  3 },
        {  1,  2,  2,  2,  3, 14 }
    });
    Matrix B = Matrix({
        {30}, {10}, {10}, {-10}, {0}, {5}
    }, 6);
    //Matrix B = Matrix({ 30, 10, 10, -10, 0, 5 });

    real alpha = 0.15;

    std::cout <<  termcolor::cyan << "================ Exercicio 1 ( a = " << alpha << " ) ================" << termcolor::reset << std::endl;
    A = A * alpha;

    std::cout << "Entrada:" << std::endl;
    std::cout << "A: " << std::endl << A << std::endl << "B: " << std::endl << B.transpose() << std::endl;

    std::cout << termcolor::cyan << "a) Maior autovalor, metodo de potencia" << termcolor::reset << std::endl;
    try {
        std::cout << computeGreatestEigenValue( A, 10E-5 ) << std::endl << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }

    std::cout << termcolor::cyan << "b) Autovalores, metodo de jacobi" << termcolor::reset << std::endl;
    try {
        Matrix X = computeEigen( A ).first;
        for ( size_t i = 0; i < X.ncolumns(); i++) {
            std::cout << X.at(i,i);
            if ( i < X.ncolumns() - 1 ) std::cout << ", ";
            else std::cout << std::endl << std::endl;
        }
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }

    std::cout << termcolor::cyan << "c) Solucao do sistema Ax = b" << termcolor::reset << std::endl;
    try {
        std::cout << termcolor::green << "Decomposicao LU: " << termcolor::reset << solveLUDecomp( A, B ).transpose() << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }
    try {
        std::cout << termcolor::green << "Cholesky:        " << termcolor::reset << solveCholeskyDecomp( A, B ).transpose() << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }
    try {
        std::cout << termcolor::green << "Gauss-Seidel:    " << termcolor::reset << solveIterative( A, B, GaussSeidel, 10E-5 ).transpose() << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }

    std::cout << termcolor::cyan << "d) Determinante de A" << termcolor::reset << std::endl;
    try {
        std::cout << determinant(A) << std::endl << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }

    std::cout << termcolor::cyan << "======================= Exercicio 3 =======================" << termcolor::reset << std::endl;

    A = Matrix({
        {3, 4, 0},
        {4, 5, 3},
        {0, 3, 6}
    });
    B = Matrix({
        {1}, {0}, {1}
    }, 3);
    //B = Matrix({ 1, 0, 1 });

    std::cout << "Entrada:" << std::endl;
    std::cout << "A: " << std::endl << A << std::endl << "B: " << std::endl << B.transpose() << std::endl;
    try {
        std::cout << "Resultado: " << solveIterative(A, B, Jacobi, 10E-5) << std::endl;
    } catch (std::exception e) { std::cout << termcolor::red << e.what() << termcolor::reset << std::endl; }

    std::cout << std::endl << "=========================== Trabalho 2 ===========================" << std::endl << std::endl;

    std::cout << termcolor::cyan << "======================= Exercicio 5 =======================" << termcolor::reset << std::endl;
    {
        Function f = [](real x){ return (exp(-pow(x, 2)/2.0)); };

        size_t iter = 0;
        real gauss = 1, gaussprev = 0;
        while ( abs(gauss - gaussprev) > 1e-3 && iter < 10 ) {
            iter++;
            gaussprev = gauss;
            gauss = computeIntegral(f, 0, 3, iter, Quadrature);
        }

        std::cout << "Quadratura de Gauss  : " << gauss << " ( " << iter << " pontos de integracao )" << std::endl;

        iter = 0;
        real poli = 1, poliprev = 0;
        while ( abs(poli - poliprev) > 1e-3 && iter < 10 ) {
            iter++;
            poliprev = poli;
            poli = computeIntegral(f, 0, 3, iter, Polinomial);
        }

        std::cout << "Quadratura Polinomial: " << poli << " ( " << iter << " pontos de integracao )" << std::endl;
    }
    std::cout << termcolor::cyan << "======================= Exercicio 6 =======================" << termcolor::reset << std::endl;
    {
        FirstOrderDifferential f = [](real t, real y){ return (-10*t*pow(y, 2)); };

        real euler = computeDifferentialEuler(f, 0, 2, 1, 0.1, true);
        std::cout << "Metodo de Euler: ( x, y ) = ( 1, " << euler << " )" << std::endl;
        
        real rk = computeDifferentialRungeKutta_SecondOrder(f, 0, 2, 1, 0.1, true);
        std::cout << "Metodo de Runge-Kutta (Segunda Ordem): ( x, y ) = ( 1, " << rk <<  " )" << std::endl;
    }
    std::cout << termcolor::cyan << "======================= Exercicio 9 =======================" << termcolor::reset << std::endl;
    {
        SecondOrderDifferential f = [](real t, real y, real yy){ return (2+cos(1.5*t)-0.2*yy-y); };

        real rkn = computeDifferentialRungeKuttaNystrom(f, 0, 0, 0, 100, 10, true);
        std::cout << "Metodo Runge-Kutta-Nystron:( x, y ) = ( 1, " << rkn << " )" << std::endl;
    }
    return 0;
}