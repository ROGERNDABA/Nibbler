#ifndef NIBBLEREXCEPTION_HPP
#define NIBBLEREXCEPTION_HPP

#include <fstream>
#include <iostream>

class NibblerException : std::exception {
   public:
    virtual const char *what() const throw() = 0;
};
#endif  //NIBBLEREXCEPTION_HPP