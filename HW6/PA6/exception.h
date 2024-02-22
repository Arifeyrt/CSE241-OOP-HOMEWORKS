#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <vector>
#include <string>
#include <fstream>
using std::string;
namespace PA6{


    // missing field exception
    class MissingField {
	public:
	    string what() const {return "missing field";}
    };

    // duplicate entry exception
    class DuplicateEntry{
	public:
	    string what() const {return "duplicate entry";}
    };

    // wrong command exception
    class WrongCommand{
	public:
	    string what() const {return "command is wrong";}
    };
    

}

#endif//EXCEPTIONS_HPP
