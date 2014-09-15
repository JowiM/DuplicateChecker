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
#include <boost\functional\hash.hpp>

namespace ublue{
	class Checker
	{
	private:
		const int DEBUG = 1;

		/**
		* Hold directory to check
		*/
		std::string gDir;

		/**
		* Parse directory and store files in them
		*/
		bool parseDir(std::string &dir, FileContainer &lsFile);

		bool findDuplicates(FileContainer fList, tDuplicated duplicated);

		std::size_t hashFile(std::string &fPath);
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
		bool process(tDuplicated& duplicate);
	};
}

#endif