#include "stdafx.h"
#include "Checker.h"

using namespace ublue;

Checker::Checker(std::string& dir)
{
	gDir = dir;
	checkProgress = 0;
}


Checker::~Checker() {}

void Checker::process(tDuplicated& duplicate)
{
	FileContainer allFiles;

	//Recursively get all files in directory
	//Done so progress can be calculated!
	parseDir(gDir, allFiles);

	//Process found files to check for duplicates
	findDuplicates(allFiles, duplicate);
}

void Checker::parseDir(std::string &dir, FileContainer &lsFile)
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
}

void Checker::calculateProgress(int totalFiles, float current)
{
	if (current == 1){
		std::cout << "Progress: (10 '#' == 100%) [#";
	}

	float numOfHash = (current / totalFiles)*10;
	
	if ((checkProgress+1) < numOfHash){
		std::cout << "#";
		checkProgress++;
	}

	if (totalFiles == current){
		std::cout << "]" << std::endl;
	}
}

void Checker::findDuplicates(FileContainer& fList, tDuplicated &duplicated)
{
	std::map<std::string, std::string> fileMap;
	int numbFiles = fList.size();
	int count = 0;
	for (FileContainer::iterator file = fList.begin(); file != fList.end(); file++){
		std::string checksum;

		//Hash File
		hashFile(*file, checksum);
	
		calculateProgress(numbFiles, ++count);

		//@todo check for empty??
		//Check if checksum is already in Map
		if (fileMap.find(checksum) == fileMap.end()){
			//Original checksum add hash to file Map
			fileMap[checksum] = *file;
		}
		else {
			//Check if hash already init in duplicated map. If not add the file found in fileMap.
			if (duplicated.find(checksum) == duplicated.end()){
				duplicated[checksum].files.push_back(fileMap[checksum]);
				duplicated[checksum].totalSize += boost::filesystem::file_size(fileMap[checksum]);
			}
			//add duplicate file
			duplicated[checksum].files.push_back(*file);
			duplicated[checksum].totalSize += boost::filesystem::file_size(*file);
			duplicated[checksum].avgFileSize = boost::filesystem::file_size(*file);
		}
	}
}


void Checker::hashFile(std::string &fPath, std::string &checksum)
{
	CryptoPP::SHA1 hash;
	try {
		CryptoPP::FileSource(fPath.c_str(), true,
			new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
			new CryptoPP::StringSink(checksum), true)));
	}
	catch (const std::exception& ex)
	{
		errorFiles.push_back(fPath);
	}
}