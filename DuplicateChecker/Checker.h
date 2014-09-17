#ifndef _H_Checker
#define _H_Checker

#include "gDuplicate.h"

#include <iostream>
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

		/**
		* Holds the progress made.
		*/
		int checkProgress;

		/**
		* Hold directory to check
		*/
		std::string gDir;

		/**
		* Holds files that where not checked for duplicate
		* @todo not being outputted yet
		*/
		std::list<std::string> errorFiles;

		/**
		* Parse directory and store files in them
		* @param string the directory to get the files in. This is recursive
		* @param FileContainer used to pass back the files found.
		*/
		void parseDir(std::string &dir, FileContainer &lsFile);

		/**
		* Find files that are duplicate. Parse through all the files passed and calculate MD5
		* @param FileContainer the files that need to be checked if any are duplicates
		* @param tDuplicated the files which are duplicated
		*/
		void findDuplicates(FileContainer& fList, tDuplicated &duplicated);

		/**
		* Calculates the percentage of files checked.
		* @param int total number of files that have to be checked
		* @param float files checked till now
		*/
		void calculateProgress(int totalFiles, float current);

		/**
		* Hash the file
		* @param string the full path of the file
		* @param string used to return the checksum of the file
		*/
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