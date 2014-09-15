#ifndef _H_Checker
#define _H_Checker

#include <iostream>
#include <fstream>
#include <streambuf>
#include <list>
#include <map>
#include <string>

#include <boost\filesystem.hpp>
#include <boost\functional\hash.hpp>

typedef std::list<std::string> FileContainer;
typedef std::map<std::string, FileContainer > tDuplicated;

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

#endif