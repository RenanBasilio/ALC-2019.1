#pragma once

// Defines a type named "function" which is a pointer to a function that takes 
// a double and returns a double.
typedef double(*Function)(double);

enum IntegrationMethod { Polinomial, Quadrature };

/**
 * Calcula o valor da integral.
 * 
 * @param f   A função a ser integrada.
 * @param x1  O limite de integração inferior
 * @param x2  O limite de integração superios
 * @param pts O número de pontos de integração.
 * @param m   O método de integração.
 * @return    O valor da integral numérica da função.
 */
double computeIntegral( Function f, double x1, double x2, size_t pts, IntegrationMethod m );

/**
 * Calcula o valor da integral utilizando o metodo polinomial.
 * 
 * @param f   A função a ser integrada.
 * @param x1  O limite de integração inferior
 * @param x2  O limite de integração superios
 * @param pts O número de pontos de integração.
 * @return    O valor da integral numérica da função.
 */
double computeIntegralPolinomial( Function f, double x1, double x2, size_t pts );