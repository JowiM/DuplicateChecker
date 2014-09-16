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

void ShellInterface::processInput(std::string input, std::list<std::string> &selectedFiles)
{
	traceLine results;
	expandTrace(input, ';', results);

	for (traceLine::iterator result = results.begin(); result != results.end(); result++){
		traceLine ids;
		expandTrace(result->second, '.', ids);

		int parent = atoi(ids[0].c_str());
		int child = atoi(ids[1].c_str());
		std::cout << atoi(ids[0].c_str()) << std::endl;

		if (lDuplicated.size() >= parent){
			continue;
		}

		int pos = 0;
		for (tDuplicated::iterator hashRecord = lDuplicated.begin(); hashRecord != lDuplicated.end(); hashRecord++){
			if (pos != parent){
				pos++;
				continue;
			}

			int childPos = 0;
			for (FileContainer::iterator file = hashRecord->second.files.begin(); file != hashRecord->second.files.end(); file++){
				if (childPos != child){
					childPos++;
					continue;
				}

				selectedFiles.push_back(*file);
				break;
			}

			break;
		}
	}
}

float ShellInterface::calculateTotal(std::list<std::string> &selectedFiles)
{
	float total = 0;
	for (std::list<std::string>::iterator file = selectedFiles.begin(); file != selectedFiles.end(); file++){
		total += boost::filesystem::file_size(*file);
	}
	return total;
}

void ShellInterface::start()
{
	std::string input;
	
	//Output file menu
	outputDuplicate();
		
	std::cout << "!------------------------- File Stats and Deletion -------------------------!" << std::endl;
	std::cout << "!     To select multiple files use semicolin. (eg. 0.0;0.1;0.2;1.2;1.3)     !" << std::endl;
	std::cout << "!     To Exit write 'exit'                                                  !" << std::endl;
	std::cout << "!       Select files you want to know the size and option to delete!!       !" << std::endl;
	std::cout << "!---------------------------------------------------------------------------!" << std::endl;
	std::cout << "Select Files: " << std::endl;
	std::cin >> input;
		
	//Exit application
	if (input == "exit"){
		return;
	}

	//Convert IDs to selected Files
	std::list<std::string> selectedFiles;
	processInput(input, selectedFiles);

	//Calculate space saving!!
	float size = calculateTotal(selectedFiles);
	char confirmation;
	std::cout << "You will delete the following:" << std::endl;
	for (std::list<std::string>::iterator file = selectedFiles.begin(); file != selectedFiles.end(); file++){
		std::cout << *file << std::endl;
	}
	std::cout << "You will save " << size << "do you want to delete the files? Press Y to delete!" << std::endl;
	std::cin >> confirmation;

	if (confirmation == 'Y'){
		if (deleteFiles(selectedFiles)){
			std::cout << "Files Deleted Successfully!!" << std::endl;
		}
		else {
			std::cout << "Not all files where deleted!!" << std::endl;
		}
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

bool ShellInterface::deleteFiles(std::list<std::string> &selectedFiles)
{
	bool filesDeleted = true;
	for (std::list<std::string>::iterator file = selectedFiles.begin(); file != selectedFiles.end(); file++){
		try {
			if (boost::filesystem::exists(*file)){
				boost::filesystem::remove(*file);
			}
		}
		catch (const std::exception& ex){
			filesDeleted = false;
		}
	}
	return filesDeleted;
}