#include "stdafx.h"
#include "ShellInterface.h"

using namespace ublue;

ShellInterface::ShellInterface(tDuplicated &duplicated) {
	lDuplicated = duplicated;
}

ShellInterface::~ShellInterface() {}

void ShellInterface::start()
{
	std::string input;
	while (1){
		std::cout << "Select Files:" << std::endl;
		std::cin >> input;
	}
}