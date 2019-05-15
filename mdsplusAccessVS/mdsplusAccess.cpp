#include "mdsplusAccess.h"


/******************************************************************************
 *
 * This is the source file to get mdsplus access to the fuze experiment
 *
 ******************************************************************************/


 /******************************************************************************
  * Function: readDHIMDSplusVector
  * Inputs: int, char *, char *, char *
  * Returns: gsl_vector *
  * Description:
  ******************************************************************************/

gsl_vector* readMDSplusVector(int shotNumber, std::string nodeName, std::string treeName) {

	MDSplus::Tree* tree;
	MDSplus::Data* data;
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
		return nullVec;

	}
	catch (...) {

		std::cout << "Default error";
		return nullVec;

	}

	try {
		
		data = MDSplus::execute(nodeName.c_str(), tree);

	}
	catch (MDSplus::MdsException & exc) {

		std::cout << "Cannot execute command in " << treeName
			<< " shot " << shotNumber << ": " << exc.what() << std::endl;
		delete tree;
		return nullVec;

	}
	catch (...) {

		std::cout << "Default error for execute";
		delete tree;
		return nullVec;

	}

	doubleArray = data->getDoubleArray(&numElements);

	gsl_vector* retVec = gsl_vector_alloc(numElements);

	int ii;
	for (ii = 0; ii < numElements; ii++) {
		gsl_vector_set(retVec, ii, doubleArray[ii]);
	}

	// Data objects must be freed via routine deleteData()
	MDSplus::deleteData(data);

	// Tree objects use C++ delete. Can't find a MDSplus::deleteTree()
	delete tree;

	// Delete pointer to memory that mdsplus created. Shouldn't already be deleted? This will get deleted by something else.
	//delete doubleArray;

	return retVec;

}


/******************************************************************************
 * Function: readDHIMDSplusVectorDim
 * Inputs: int, char *, char *, char *
 * Returns: gsl_vector *
 * Description:
 ******************************************************************************/

gsl_vector* readMDSplusVectorDim(int shotNumber, std::string nodeName, std::string treeName) {

	MDSplus::Tree* tree;
	MDSplus::Data* data;
	int numElements;
	double* doubleArray;
	std::string readOnly = "READONLY";
	char buf[1024];
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
		return nullVec;

	}
	catch (...) {

		std::cout << "Default error";
		return nullVec;
	}

	snprintf(buf, sizeof(buf) - 1, "DIM_OF(%s)", nodeName.c_str());
	
	try {

		data = MDSplus::execute(buf, tree);

	}
	catch (MDSplus::MdsException & exc) {

		std::cout << "Cannot execute command in " << treeName
			<< " shot " << shotNumber << ": " << exc.what() << std::endl;
		delete tree;
		return nullVec;

	}
	catch (...) {

		std::cout << "Default error for execute";
		delete tree;
		return nullVec;

	}

	doubleArray = data->getDoubleArray(&numElements);

	gsl_vector* retVec = gsl_vector_alloc(numElements);

	int ii;
	for (ii = 0; ii < numElements; ii++) {
		gsl_vector_set(retVec, ii, doubleArray[ii]);
	}

	// Data objects must be freed via routine deleteData()
	MDSplus::deleteData(data);

	// Tree objects use C++ delete. Can't find a MDSplus::deleteTree()
	delete tree;

	// Delete pointer to memory that mdsplus created. Shouldn't already be deleted? I think this gets deleted elsewhere
	//delete doubleArray;

	return retVec;

}


/******************************************************************************
 * Function: getCurrentPulseNumber
 * Inputs: const char *
 * Returns: int
 * Description: Returns the length of the specified signal if successful, -1
 ******************************************************************************/

int getCurrentPulseNumber() {

	MDSplus::Data* data;
	std::string getShot = "current_shot('fuze')";
	int pulseNumber;

	try {
		data = MDSplus::execute(getShot.c_str());
	}
	catch (MDSplus::MdsException & exc) {

		std::cout << "Cannot get current shot number: " 
			<< exc.what() << std::endl;
		return -1;

	}
	catch (...) {

		std::cout << "Default error for getting current shot number";
		return -1;

	}

	pulseNumber = data->getLong();

	// Data objects must be freed via routine deleteData()
	MDSplus::deleteData(data);

	/* return pulse number */
	return pulseNumber;

}


/******************************************************************************
 * Function: readDHIMDSplusDouble
 * Inputs: int, char *, char *, char *
 * Returns: gsl_vector *
 * Description:
 ******************************************************************************/

double readMDSplusDouble(int shotNumber, std::string nodeName, std::string treeName) {

	MDSplus::Tree* tree;
	MDSplus::Data* data;
	double doubleValue;
	std::string readOnly = "READONLY";

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

		std::cout << "Cannot get double: "
			<< exc.what() << std::endl;
		return -1;

	}
	catch (...) {

		std::cout << "Default error for getting double";
		return -1;

	}

	doubleValue = data->getDouble();

	// Data objects must be freed via routine deleteData()
	MDSplus::deleteData(data);

	// Tree objects use C++ delete. Can't find a MDSplus::deleteTree()
	delete tree;

	return doubleValue;

}


/******************************************************************************
 *
 * TESTING SECTION
 *
 ******************************************************************************/

static bool testDHIRead();
static bool testVectorRead();

bool testMDSplusAccess() {

	bool retBool = true;

	if (!testDHIRead()) {
		return false;
	}
	else {
		std::cout << "DHI Read Test Passed!\n";
	}

	if (!testVectorRead()) {
		return false;
	}
	else {
		std::cout << "Vector Read Test Passed!\n";
	}

	return true;

}

static bool testDHIRead() {

	//int shotNumber1 = 180517018; // DHI Time = 59E-5
	int shotNumber2 = 190501030; // DHI Time = 4.4E-5

	double time2 = readMDSplusDouble(shotNumber2, "\\T_DHI_GATE", "fuze");

	if ((time2 >= 4.5E-5) || (time2 <= 4.3E-5)) {
		std::cout << "testDHIRead() Failed!\n";
		std::cout << "Expected 4.4E-5 but got " << time2 << "\n";
		return false;
	}

	return true;

}

static bool testVectorRead() {

	std::string treeName = "fuze";
	std::string nodeName = "\\I_P";
	int shotNumber = 190403046;
	gsl_vector* testIP = readMDSplusVector(shotNumber, "\\I_P", "fuze");
	int numElements = testIP->size;

	if (numElements != 524288) {
		std::cout << "TEST FAILED. Incorrect number of elements";
		std::cout << "Expected 524288 and got" << numElements << "\n";
		gsl_vector_free(testIP);
		return false;
	}

	double testVal = gsl_vector_get(testIP, 100);
	if ((testVal < -27) || (testVal > -26)) {
		std::cout << "TEST FAILED. Incorrect value at 100";
		std::cout << "Expected around -26.5, Got " << testVal << "\n";
		gsl_vector_free(testIP);
		return false;
	}

}