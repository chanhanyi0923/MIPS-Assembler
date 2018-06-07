#pragma once

#include <stdexcept>

class AssembleException: public std::exception
{
public:
	AssembleException();
	AssembleException(const char * message);
	~AssembleException();
};

