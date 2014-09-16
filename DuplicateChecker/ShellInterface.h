#ifndef _H_ShellInterface
#define _H_ShellInterface

#include "gDuplicate.h"
#include <iostream>
#include <boost\filesystem\operations.hpp>

typedef std::map<int, std::string> traceLine;

namespace ublue {
	class ShellInterface
	{
	private:
		tDuplicated lDuplicated;

		void outputDuplicate();

		void processInput(std::string input, std::list<std::string> &selectedFiles);

		void expandTrace(std::string &s, char delimiter, traceLine &result);

		float calculateTotal(std::list<std::string> &selectedFiles);


		bool ShellInterface::deleteFiles(std::list<std::string> &selectedFiles);
	public:
		ShellInterface(tDuplicated &duplicated);
		~ShellInterface();

		void start();
	};
}
#endif