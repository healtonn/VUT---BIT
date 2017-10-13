/*
 *  Jakub Jochlík
 *  ISA - DHCP server
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <getopt.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

using namespace std;


typedef struct{
	bool h;
  bool e;
  bool p;
  vector<string> forbiddenIP;
  string ipPool;
  int first;
	int second;
	int third;
	int fourth;
	int mask;
}parameter_t;


/**
 *  Fills up parameters structure with parsed parameters for later use
 */
int processParameters(int numberOfParameters, char* parameters[], parameter_t *parametersStructure);

/**
 *  Performs simple argumet check. At least two parameters must be given (program itself and -p) and maximum 3 arguments can be given (-e)
 */
int checkArgumentCount(int numberOfParameters);

/**
 *  Fills up parameter structure with default values
 */
void initializeParameterStructure(parameter_t *structure);

/**
 *  Actual parsing is done here
 */
int parseArguments(int numberOfParameters, char* passedParameters[], parameter_t *parametersStructure);

/**
 * Checks, if given IP pool is valid option
 */
bool isIPPoolArgumentValid(string IPPool, parameter_t *parametersStructure);

bool isIPCorrect(string ip, parameter_t *parametersStructure);

bool isMaskCorrect(string mask, parameter_t *parametersStructure);

int getIntegerValueFromString(string numberToConvert);

/*
 * fills up data structure with input data
 */
void fillIPData(int i,int data, parameter_t *parametersStructure);

/**
 * shows content of ip parameters structure
 */
void printParametersStructure(parameter_t parametersStructure);
