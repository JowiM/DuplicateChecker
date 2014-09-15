// DuplicateChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Checker.h"
#include "ShellInterface.h"

using namespace ublue;

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "!!Missing Args!! - Please enter directory!" << std::endl;
		return -1;
	}

	tDuplicated duplicatedFiles;
	std::string dir = argv[1];
	
	Checker dirChecker(dir);
	dirChecker.process(duplicatedFiles);
	
	ShellInterface shellUI(duplicatedFiles);
	shellUI.start();

	return 0;
}

