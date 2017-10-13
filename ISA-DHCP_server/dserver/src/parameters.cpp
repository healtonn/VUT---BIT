/*
 *  Jakub Jochlík
 *  ISA - DHCP server
 */

#include "parameters.h"


int processParameters(int numberOfParameters, char* passedParameters[], parameter_t *parametersStructure){
  if(checkArgumentCount(numberOfParameters))
  	return -1;

  initializeParameterStructure(parametersStructure);
  if(parseArguments(numberOfParameters, passedParameters, parametersStructure))
  	return -1;

  if(!parametersStructure->p){
  	fprintf(stderr, "Missing -p !\n");
  	return -1;
  }
  return 0;
}

int checkArgumentCount(int argumentCount){
  if(argumentCount < 2 || argumentCount > 6){
    fprintf(stderr, "Wrong usage of program arguments\n");
    return -1;
  }
  return 0;
}

void initializeParameterStructure(parameter_t *parameters){
	parameters->h = false;
  parameters->e = false;
  parameters->p = false;
  parameters->ipPool = "";
}

int parseArguments(int numberOfParameters, char* passedParameters[], parameter_t *parametersStructure){
  int option;

  while((option = getopt(numberOfParameters, passedParameters, "hp:e:")) != -1){
    switch(option){
    case 'h':
    	parametersStructure->h = true;
    	break;
    case 'p':
      parametersStructure->p = true;
      if(isIPPoolArgumentValid(optarg, parametersStructure)){parametersStructure->ipPool = optarg;}
      else{
      	fprintf(stderr, "%s is invalid option\n", optarg);
      	return -1;
      }
      break;
    case 'e':
      parametersStructure->e = true;

      char* partOfOptarg;
      partOfOptarg = strtok(optarg, ",");
      while(partOfOptarg){
      	string substring(partOfOptarg);
      	unsigned char ipBuffer[sizeof(struct in6_addr)];
      	const char * forbiddenIpAsConstChar = substring.c_str();
      	unsigned int resultOfConversion;

      	resultOfConversion = inet_pton(AF_INET, forbiddenIpAsConstChar, ipBuffer);
      	if(resultOfConversion != 1)
      		return -1;
      	parametersStructure->forbiddenIP.push_back(substring);
      	partOfOptarg = strtok(NULL, ",");
      }
      break;
    default:
      fprintf(stderr, "You are entering wrong parameter OR mising parameter's argument!\n");
      return -1;
    }
  }

  return 0;
}

bool isIPPoolArgumentValid(string IPPool, parameter_t *parametersStructure){
	string maskDelimeter = "/";
	string ip;
	string mask;
	size_t slashPosition;

	if((slashPosition = IPPool.find(maskDelimeter)) == std::string::npos)
		return false;

	ip = IPPool.substr(0, slashPosition);
	mask = IPPool.substr(slashPosition + 1);

	if(!isIPCorrect(ip, parametersStructure))
		return false;

	if(!isMaskCorrect(mask, parametersStructure))
		return false;


	return true;
}

bool isIPCorrect(string ip, parameter_t *parametersStructure){
	unsigned char ipBuffer[sizeof(struct in6_addr)];
	const char * forbiddenIpAsConstChar = ip.c_str();
	unsigned int resultOfConversion;

	resultOfConversion = inet_pton(AF_INET, forbiddenIpAsConstChar, ipBuffer);
	if(resultOfConversion != 1)
		return false;

	string dotDelimeter = ".";
	string tmp;
	size_t dotPosition;
	vector<string> parsedNumbers;
	int dotCounter = 0;

	while((dotPosition = ip.find(dotDelimeter)) != std::string::npos){
		dotCounter++;
		tmp = ip.substr(0, dotPosition);
		parsedNumbers.insert(parsedNumbers.end(), tmp);
		ip.erase(0, dotPosition + 1);
	}
	parsedNumbers.insert(parsedNumbers.end(), ip);

	if(dotCounter != 3)
		return false;

	int numberFromString;
	int counter = -1;
	for (vector<string>::const_iterator i = parsedNumbers.begin(); i != parsedNumbers.end(); i++){
		counter++;
		numberFromString = getIntegerValueFromString(*i);
		if(numberFromString > 255 || numberFromString < 0)
			return false;
		fillIPData(counter, numberFromString, parametersStructure);
	}
	return true;
}

int getIntegerValueFromString(string numberToConvert){
	char *newChar = new char[numberToConvert.length() + 1];
	strcpy(newChar, numberToConvert.c_str());
	char *ptr;
	long result;
	result = strtol(newChar, &ptr, 10);
	return (int) result;
}

bool isMaskCorrect(string mask, parameter_t *parametersStructure){
	long longTypeMask = getIntegerValueFromString(mask);
	int intTypeMask = (int) longTypeMask;
	if(intTypeMask > 0 || intTypeMask < 31){
		fillIPData(5, intTypeMask, parametersStructure);
		return true;
	}
	else
		return false;
}

void fillIPData(int i,int data, parameter_t *parametersStructure){
	switch (i){
	case 0:
		parametersStructure->first = data;
		break;
	case 1:
		parametersStructure->second = data;
		break;
	case 2:
		parametersStructure->third = data;
		break;
	case 3:
		parametersStructure->fourth = data;
		break;
	case 5:	//mask
		parametersStructure->mask = data;
			break;
	}
}

void printParametersStructure(parameter_t parametersStructure){
	cout << "this is debugging output: " << endl;
	cout << "bool e: " << parametersStructure.e << endl;
	cout << "bool p: " << parametersStructure.p << endl;
	cout << "ip pool:" << parametersStructure.ipPool << endl;
	cout << "given ip: " << parametersStructure.first << "." << parametersStructure.second << "." << parametersStructure.third << "." << parametersStructure.fourth << endl;
	cout << "first: " << parametersStructure.first << endl;
	cout << "second: " << parametersStructure.second << endl;
	cout << "third: " << parametersStructure.third << endl;
	cout << "fourth: " << parametersStructure.fourth << endl;
	cout << "mask: " << parametersStructure.mask << endl << endl;
}
