#include "coreexception.h"

CoreException::CoreException(const std::string &message)
  : mMessage(message)
{ }

CoreException::CoreException(const std::string &file, const int line, const std::string &message)
{
  mMessage.append(file);
  mMessage.append(" [");
  mMessage.append(std::to_string(line));
  mMessage.append("] : ");
  mMessage.append(message);
}

CoreException::~CoreException() noexcept
{ }

const char *CoreException::what() const noexcept
{
  return mMessage.c_str();
}
