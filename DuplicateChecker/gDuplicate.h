#ifndef _H_gDuplicate
#define _H_gDuplicate

#include <string>
#include <list>
#include <map>



typedef std::list<std::string> FileContainer;

struct duplicateInfo {
	FileContainer files;
	float totalSize;
	float avgFileSize;
};
typedef std::map<std::string, struct duplicateInfo > tDuplicated;

#endif