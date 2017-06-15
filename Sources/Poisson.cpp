/**
 * \file Poisson.cpp
 * \brief
 *
 * Poisson Disk Points Generator example
 *
 * \version 1.1.3
 * \date 10/03/2016
 * \author Sergey Kosarevsky, 2014-2016
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 */
#include "Poisson.hpp"

#include <vector>
#import "PoissonGenerator.hpp"

std::vector<PoissonGenerator::sPoint> generatePosisson(int numPoints) {
    PoissonGenerator::DefaultPRNG PRNG;
    std::vector<PoissonGenerator::sPoint> Points = PoissonGenerator::GeneratePoissonPoints(numPoints,PRNG);
    return Points;
}
