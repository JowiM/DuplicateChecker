#ifndef _H_Checker
#define _H_Checker

#include "gDuplicate.h"

#include <iostream>
#include <fstream>
#include <streambuf>
#include <list>
#include <map>
#include <string>

#include <boost\filesystem.hpp>
#include <cryptopp\sha.h>
#include <cryptopp\hex.h>
#include <cryptopp\files.h>

namespace ublue{
	class Checker
	{
	private:
		const int DEBUG = 1;

		int checkProgress;

		/**
		* Hold directory to check
		*/
		std::string gDir;

		std::list<std::string> errorFiles;

		/**
		* Parse directory and store files in them
		*/
		void parseDir(std::string &dir, FileContainer &lsFile);

		void findDuplicates(FileContainer& fList, tDuplicated &duplicated);

		void calculateProgress(int totalFiles, float current);

		void hashFile(std::string &fPath, std::string& checksum);
	public:

		/**
		* Constructor
		*/
		Checker(std::string& dir);

		/**
		* Destructor
		*/
		~Checker();

		/**
		* Initialize Checker!!
		* @param reference to hold duplicate files
		*/
		void process(tDuplicated& duplicate);
	};
}

#endif