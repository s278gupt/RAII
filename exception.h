#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <string>

class InvalidMove{
	std::string s;
	public:
	InvalidMove(std::string s = "Invalid Move");
	std::string getErrorMessage();
};

#endif
