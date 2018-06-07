#include "AssembleException.h"

#include <stdexcept>

using std::exception;

AssembleException::AssembleException()
{
}

AssembleException::AssembleException(const char * message): exception(message)
{
}

AssembleException::~AssembleException()
{
}

