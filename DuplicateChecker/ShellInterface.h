#ifndef _H_ShellInterface
#define _H_ShellInterface

#include "gDuplicate.h"
#include <iostream>

typedef std::map<int, std::string> traceLine;

namespace ublue {
	class ShellInterface
	{
	private:
		tDuplicated lDuplicated;

		void outputDuplicate();

		void processInput(std::string input);

		void expandTrace(std::string &s, char delimiter, traceLine &result);
	public:
		ShellInterface(tDuplicated &duplicated);
		~ShellInterface();

		void start();
	};
}
#endif