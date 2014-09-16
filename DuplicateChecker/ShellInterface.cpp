#include "stdafx.h"
#include "ShellInterface.h"

using namespace ublue;

ShellInterface::ShellInterface(tDuplicated &duplicated) {
	lDuplicated = duplicated;
}

ShellInterface::~ShellInterface() {}

void ShellInterface::outputDuplicate()
{
	for (tDuplicated::iterator hashRecord = lDuplicated.begin(); hashRecord != lDuplicated.end(); hashRecord++){
		std::cout << "-- " << hashRecord->first << "-- " << std::endl;

		for (FileContainer::iterator files = hashRecord->second.begin(); files != hashRecord->second.end(); files++){
			std::cout << "  |_ " << *files << std::endl;
		}

		std::cout << std::endl;
	}
}

void ShellInterface::processInput(std::string input)
{

}

void ShellInterface::start()
{
	std::string input;
	while (1){
		//Output file menu
		outputDuplicate();
		
		std::cout << "Select Files:" << std::endl;
		std::cin >> input;
		
		if (input == "exit"){
			break;
		}

		processInput(input);
	}
}