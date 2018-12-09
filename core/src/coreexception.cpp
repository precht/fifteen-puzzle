#include "coreexception.h"

CoreException::CoreException(const std::string &c_message)
  : m_message(c_message)
{ }

CoreException::CoreException(const std::string &c_file, const int c_line, const std::string &c_message)
{
  m_message.append(c_file);
  m_message.append(" [");
  m_message.append(std::to_string(c_line));
  m_message.append("] : ");
  m_message.append(c_message);
}

CoreException::~CoreException() noexcept
{ }

const char *CoreException::what() const noexcept
{
  return m_message.c_str();
}
