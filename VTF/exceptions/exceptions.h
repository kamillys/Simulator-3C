#pragma once

#include <string>
#include <sstream>
#include <VTF/Traits>

namespace VTF {

/*
 * Base class for all exception types
 */
class Exception
{
    std::string m_message;
public:
    Exception(const char* message);
    const char* message() const;
    static const char* getName()
    {
        return "Exception";
    }
};

/*
 * Macros for defining exception types
 */

#define EXCEPTION_S(type, supertype) \
class type : public supertype {  public: \
    type(const char* message) : supertype(message) { } \
    static const char* getName() { return #type; } \
}

#define EXCEPTION(type) EXCEPTION_S(type, VTF::Exception)

/*
 * Macros for throwing exceptions
 */

#define THROW_EXCEPTION_T(message, type) \
do { \
    std::stringstream sstream; \
    sstream << type::getName() << ": " << message << std::endl; \
    sstream << "In function " << __VTF__FUNCTIONNAME__ << std::endl; \
    sstream << "File: " << __FILE__ << " at " << __LINE__  << std::endl; \
    throw type(sstream.str().c_str()); \
} while(0);

#define THROW_EXCEPTION(message) \
    THROW_EXCEPTION_T(message, VTF::Exception)


/*
 * Exception types
 */
EXCEPTION(UnknownException);
EXCEPTION(NullPointerException);
EXCEPTION(AccessException);
EXCEPTION_S(OutOfIndexException, AccessException);
}
