#include <Definitions.hpp>

/**
 * Numerically solves for the value of a first order differential equation using
 * the Euler method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The initial value of x
 * @param  y0   The initial value of y
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialEuler( FirstOrderDifferential f, real x0, real y0, real x, real step );

/**
 * Numerically solves for the value of a first order differential equation using
 * the Second Order Rene-Kutta method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The initial value of x
 * @param  y0   The initial value of y
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialRungeKutta_SecondOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step );

/**
 * Numerically solves for the value of a first order differential equation using
 * the Fourth Order Renge-Kutta method.
 * 
 * @param  f    A first order differential equation f(t, y(t))
 * @param  x0   The initial value of x
 * @param  y0   The initial value of y
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialRungeKutta_FourthOrder ( FirstOrderDifferential f, real x0, real y0, real x, real step );

/**
 * Numerically solves for the value of a second order differential equation using
 * the Taylor Series Expansion method.
 * 
 * @param  f    A second order differential equation f(t, y(t), y'(t))
 * @param  x0   The initial value of x
 * @param  y0   The initial value of y
 * @param  yy0  The initial value of y'
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialTaylor( SecondOrderDifferential f, real x0, real y0, real yy0, real x, real step );

/**
 * Numerically solves for the value of a second order differential equation using
 * the Renge-Kutta-Nystron method.
 * 
 * @param  f    A first order differential equation f(t, y(t), y'(t))
 * @param  x0   The initial value of x
 * @param  y0   The initial value of y
 * @param  yy0  The initial value of y'
 * @param  x    The target x
 * @param  step The integration step
 * @return The value of y(x)
 */
real computeDifferentialRungeKuttaNystron( SecondOrderDifferential f, real x0, real y0, real yy0, real x, real step );