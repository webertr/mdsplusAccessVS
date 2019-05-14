// mdsplusAccessVS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Ignore MIX MAX keyword
#define NOMINMAX

// Ignore atribute keyword
#define __attribute__(x)

#include <iostream>
#include <gsl/gsl_vector.h>
#include <mdsobjects.h>

int main()
{
    std::cout << "Starting program...\n";

	MDSplus::Tree* tree;
	MDSplus::Data* data;

	std::string treeName = "fuze";
	std::string nodeName = "\\I_P";
	int shotNumber = 0;

	int numElements;
	double* doubleArray;
	std::string readOnly = "READONLY";
	gsl_vector* nullVec = 0;

	/*
	 * Trying to open an experiment and shot number
	 */
	try {

		/*
		 * The tree name has to match the path environment variable xxx_path
		 * fuze_path = fuze.fuze::/usr/local/trees/fuze/newdata/~t
		 */
		tree = new MDSplus::Tree(treeName.c_str(), shotNumber, readOnly.c_str());

	}
	catch (MDSplus::MdsException & exc) {

		std::cout << "Cannot open tree " << treeName
			<< " shot " << shotNumber << ": " << exc.what() << std::endl;
		return -1;

	}
	catch (...) {

		std::cout << "Default error";
		return -1;

	}

	try {
		data = MDSplus::execute(nodeName.c_str(), tree);
	}
	catch (MDSplus::MdsException & exc) {

		std::cout << "Cannot execute command in " << treeName
			<< " shot " << shotNumber << ": " << exc.what() << std::endl;
		return -1;

	}
	catch (...) {

		std::cout << "Default error for execute";
		return -1;

	}

	doubleArray = data->getDoubleArray(&numElements);

	gsl_vector* retVec = gsl_vector_alloc(numElements);

	int ii;
	for (ii = 0; ii < numElements; ii++) {
		gsl_vector_set(retVec, ii, doubleArray[ii]);
		std::cout << "Value(" << ii << "): " << doubleArray[ii] << "\n";
	}

	// Data objects must be freed via routine deleteData()
	MDSplus::deleteData(data);

	// Tree objects use C++ delete. Can't find a MDSplus::deleteTree()
	delete tree;

	// Delete pointer to memory that mdsplus created. Shouldn't already be deleted?
	delete doubleArray;

	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
