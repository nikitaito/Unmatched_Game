
#ifndef exption_conrol
#define exption_conrol

#include<exception>
#include<stdexcept>
#include<string>

class NoSpaceException : public std::runtime_error {
    public:
        NoSpaceException(const std :: string & message = "There is no available space.")
            : std::runtime_error(message) {}
};

class No_Way : public std :: runtime_error {
    public:
        No_Way(const std :: string & message = "There is not way")
            : std::runtime_error(message) {}
};



#endif 
