#ifndef AI15EXCEPTION_H
#define AI15EXCEPTION_H

#include <stdexcept>

struct CoreException : public std::exception
{
  std::string mMessage;
public:
  CoreException(const std::string &message);
  CoreException(const std::string &file, const int line, const std::string &message = ".");
  ~CoreException() noexcept;
  const char* what() const noexcept;
};

#endif // AI15EXCEPTION_H
