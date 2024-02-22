#ifndef LINALGEXCEPTIONS_H
#define LINALGEXCEPTIONS_H

#include <stdexcept>
#include <string>

class LinAlgExceptions : public std::runtime_error {

    public:
        LinAlgExceptions(const std::string& message) : std::runtime_error(message){};

};

#endif
