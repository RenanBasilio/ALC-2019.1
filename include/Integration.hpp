#pragma once

#include <Definitions.hpp>

enum IntegrationMethod { Polinomial, Quadrature };

/**
 * Calcula numericamente o valor da integral.
 * 
 * @param f   A função a ser integrada.
 * @param a   O limite de integração inferior
 * @param b   O limite de integração superios
 * @param pts O número de pontos de integração.
 * @param m   O método de integração.
 * @return    O valor da integral numérica da função.
 */
real computeIntegral( Function f, real a, real b, size_t pts, IntegrationMethod m );

/**
 * Calcula numericamente o valor da integral utilizando o metodo polinomial.
 * 
 * @param f   A função a ser integrada.
 * @param a   O limite de integração inferior
 * @param b   O limite de integração superios
 * @param pts O número de pontos de integração.
 * @return    O valor da integral numérica da função.
 */
real computeIntegralPolinomial( Function f, real a, real b, size_t pts );

/**
 * Calcula numericamente o valor da integral utilizando o metodo da quadratura de gauss.
 * 
 * @param f   A função a ser integrada.
 * @param a   O limite de integração inferior
 * @param b   O limite de integração superios
 * @param pts O número de pontos de integração.
 * @return    O valor da integral numérica da função.
 */
real computeIntegralQuadrature( Function f, real a, real b, size_t pts );