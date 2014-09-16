#include "stdafx.h"
#include "ShellInterface.h"

using namespace ublue;

ShellInterface::ShellInterface(tDuplicated &duplicated) {
	lDuplicated = duplicated;
}

ShellInterface::~ShellInterface() {}

void ShellInterface::outputDuplicate()
{
	int count = 0;
	for (tDuplicated::iterator hashRecord = lDuplicated.begin(); hashRecord != lDuplicated.end(); hashRecord++){
		std::cout << "-- -ID:" << count++ << "-Hash:" << hashRecord->first << " -totalSize:" << hashRecord->second.totalSize << "-- " << std::endl;
		int count2 = 0;
		for (FileContainer::iterator files = hashRecord->second.files.begin(); files != hashRecord->second.files.end(); files++){
			std::cout << "  |_ ID:" << count2++ << "-File:" << *files << std::endl;
		}

		std::cout << std::endl;
	}
}

void ShellInterface::processInput(std::string input)
{
	traceLine results;
	expandTrace(input, ';', results);


}

void ShellInterface::start()
{
	std::string input;
	while (1){
		//Output file menu
		outputDuplicate();
		
		std::cout << "!------------------------- File Stats and Deletion -------------------------!" << std::endl;
		std::cout << "!     To select multiple files use semicolin. (eg. 0.0;0.1;0.2;1.2;1.3)     !" << std::endl;
		std::cout << "!       Select files you want to know the size and option to delete!!       !" << std::endl;
		std::cout << "!---------------------------------------------------------------------------!" << std::endl;
		std::cout << "Select Files: " << std::endl;
		std::cin >> input;
		
		if (input == "exit"){
			break;
		}

		processInput(input);
	}
}


void ShellInterface::expandTrace(std::string &s, char delimiter, traceLine &result)
{
	size_t pos = 0;
	std::string token;
	int index = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		result[index] = token;
		s.erase(0, pos + 1);
		index += 1;
	}
	result[index] = s;
}