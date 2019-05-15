// mdsplusAccessVS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Ignore MIX MAX keyword
#define NOMINMAX

// Ignore atribute keyword
#define __attribute__(x)

#include <iostream>
#include <gsl/gsl_vector.h>
#include <mdsobjects.h>
#include "mdsplusAccess.h"

int main()
{

	if (testMDSplusAccess()) {
		std::cout << "MDSplus Access Test Passed!\n";
	}

	getchar();

	return 0;

}