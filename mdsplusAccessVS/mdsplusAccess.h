#pragma once

// Ignore MIX MAX keyword
#define NOMINMAX

// Ignore atribute keyword
#define __attribute__(x)

#include <iostream>
#include <gsl/gsl_vector.h>
#include <mdsobjects.h>

gsl_vector* readMDSplusVector(int shotNumber, std::string nodeName, std::string treeName);
gsl_vector* readMDSplusVectorDim(int shotNumber, std::string nodeName, std::string treeName);
int getCurrentPulseNumber();
double readMDSplusDouble(int shotNumber, std::string nodeName, std::string treeName);
bool testMDSplusAccess();
