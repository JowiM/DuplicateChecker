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
		/**
		* Holds the duplicated files locally
		*/
		tDuplicated lDuplicated;

		/**
		* Show the duplicated files
		*/
		void outputDuplicate();

		/**
		* Process the input passed from the user
		* @param string input passed by user to select files
		* @param list<> will contain the files selected by the user
		*/
		void processInput(std::string input, std::list<std::string> &selectedFiles);

		/**
		* Expand String according to delimiter
		* @param string to explode
		* @param char delimeter by which the string is expanded
		* @param traceLine all the expensions will be returned here.
		*/
		void expandTrace(std::string &s, char delimiter, traceLine &result);

		/**
		* Calculate the total size of passed files
		* @param list<> the files selected
		* @return float the total size used
		*/
		float calculateTotal(std::list<std::string> &selectedFiles);

		/**
		* Delete the selected files
		* @param list<> Files to delete
		*/
		bool ShellInterface::deleteFiles(std::list<std::string> &selectedFiles);
	public:
		ShellInterface(tDuplicated &duplicated);
		~ShellInterface();

		/**
		* Start Shell Interface
		*/
		void start();
	};
}
#endif