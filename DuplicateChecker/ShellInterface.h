#ifndef _H_ShellInterface
#define _H_ShellInterface

#include "gDuplicate.h"
#include <iostream>
namespace ublue {
	class ShellInterface
	{
	private:
		tDuplicated lDuplicated;
	public:
		ShellInterface(tDuplicated &duplicated);
		~ShellInterface();

		void start();
	};
}
#endif