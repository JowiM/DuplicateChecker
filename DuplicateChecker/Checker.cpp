#include "stdafx.h"
#include "Checker.h"


Checker::Checker(std::string& dir)
{
	gDir = dir;
}


Checker::~Checker() {}

bool Checker::process(tDuplicated& duplicate)
{
	FileContainer allFiles;

	//Recursively get all files in directory
	//Done so progress can be calculated!
	parseDir(gDir, allFiles);
	std::cout << "Total Files found :" << allFiles.size() << std::endl;

	findDuplicates(allFiles, duplicate);

	return false;
}

bool Checker::parseDir(std::string &dir, FileContainer &lsFile)
{
	boost::filesystem::directory_iterator begin(dir);
	boost::filesystem::directory_iterator end;

	for (; begin != end; ++begin){
		//Get file path
		std::string filePath = begin->path().string();
		//Get File Status
		boost::filesystem::file_status fStatus = boost::filesystem::status(*begin);
		//Check what type the file is. Directory or File??
		//@todo check whether microsoft has symbolic link and FIFO files features
		switch (fStatus.type())
		{
		case boost::filesystem::directory_file:
			//This is a directory hence recall this method
			parseDir(filePath, lsFile);
			break;
		case boost::filesystem::regular_file:
			lsFile.push_back(filePath);
			break;
		default:
			if (DEBUG == 1){
				std::cout << "Unhandled type of file!! - " << filePath << std::endl;
			}
		}
	}

	return true;
}

bool Checker::findDuplicates(FileContainer fList, tDuplicated duplicated)
{
	std::map<std::size_t, std::string> fileMap;

	for (FileContainer::iterator file = fList.begin(); file != fList.end(); file++){
		std::size_t tmpHash = hashFile(*file);
		
		if (tmpHash == 0){
			std::cout << "CANNOT BE ACCESSED or EMPTY!" << std::endl;
			continue;
		}

		if (fileMap.find(tmpHash) == fileMap.end()){
			//Add hash to file Map
			fileMap[tmpHash] = *file;
		}
		else {
			duplicated[tmpHash].push_back(*file);
			std::cout << "DUPLICATED!! " << *file << " - " << fileMap[tmpHash] << std::endl;
		}
	}

	std::cout << "Duplicate Files " << duplicated.size() << std::endl;
	
	return true;
}

/**
* @todo this methods requires updated. Not the most efficient!!! Loads all file in memory!!
**/
std::size_t Checker::hashFile(std::string &fPath)
{
	std::fstream targetFile(fPath);
	std::string loadFile((std::istreambuf_iterator<char>(targetFile)), std::istreambuf_iterator<char>());

	boost::hash<std::string> generateHash;
	return generateHash(loadFile);
}