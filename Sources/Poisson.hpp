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

/*
	To compile:
 gcc Poisson.cpp -std=c++11 -lstdc++
 */

#ifndef Poisson_hpp
#define Poisson_hpp
#include <stdio.h>
#include "PoissonGenerator.hpp"
std::vector<PoissonGenerator::sPoint> generatePosisson(int numPoints);
#endif /* Poisson_hpp */
