#include <exception>

class InvalidStructureException: public std::exception
{
  public:
  virtual const char* what() const throw()
  {
    return "InvalidStructureException";
  }
};