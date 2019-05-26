#include <Definitions.hpp>

/**
 * Numerically solves the value of a first order differential equation using
 * the Euler method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The x coordinate of the starting point
 * @param  y0   The y coordinate of the starting point
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialEuler( FirstOrderDifferential f, real x0, real y0, real x, real step );

/**
 * Numerically solves the value of a first order differential equation using
 * the Second Order Rene-Kutta method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The x coordinate of the starting point
 * @param  y0   The y coordinate of the starting point
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialRengeKutta_SecondOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step );

/**
 * Numerically solves the value of a first order differential equation using
 * the Fourth Order Renge-Kutta method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The x coordinate of the starting point
 * @param  y0   The y coordinate of the starting point
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialRengeKutta_FourthOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step );