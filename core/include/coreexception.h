#ifndef AI15EXCEPTION_H
#define AI15EXCEPTION_H

#include <stdexcept>

struct CoreException : public std::exception
{
  std::string m_message;
public:
  CoreException(const std::string &c_message);
  CoreException(const std::string &c_file, const int c_line, const std::string &c_message = ".");
  ~CoreException() noexcept;
  const char* what() const noexcept;
};

#endif // AI15EXCEPTION_H
