#include "NibblerException.hpp"

NibblerException::NibblerException(std::string exc) {
    this->_exc = "\033[31m" + exc + "\033[0m";
}

NibblerException::NibblerException(NibblerException const& copy) {
    *this = copy;
}

const char* NibblerException::what() const throw() {
    return this->_exc.c_str();
}

NibblerException& NibblerException::operator=(NibblerException const& rhs) {
    if (this != &rhs) {
    }
    return *this;
}
