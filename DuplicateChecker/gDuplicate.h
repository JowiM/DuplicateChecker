#ifndef _H_gDuplicate
#define _H_gDuplicate

#include <string>
#include <list>
#include <map>

/**
* Used to contain files
*/
typedef std::list<std::string> FileContainer;

/**
* Struct to hold details about a duplicate record
*/
struct duplicateInfo {
	FileContainer files;
	float totalSize;
	float avgFileSize;
};
typedef std::map<std::string, struct duplicateInfo > tDuplicated;

#endif