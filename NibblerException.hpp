#ifndef NIBBLEREXCEPTION_HPP
#define NIBBLEREXCEPTION_HPP

#include <fstream>
#include <iostream>

class NibblerException : std::exception {
   private:
    std::string _exc;

   public:
    NibblerException(std::string);
    NibblerException(NibblerException const &);
    NibblerException &operator=(NibblerException const &);
    virtual const char *what() const throw();
};
#endif  //NIBBLEREXCEPTION_HPP