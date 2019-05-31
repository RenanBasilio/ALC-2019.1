#pragma once
#include <vector>
#include <Definitions.hpp>

std::vector<real> generateLagrangeWeights( int pts );

std::vector<real> generateLagrangeWeights( int pts, real x1, real x2 );