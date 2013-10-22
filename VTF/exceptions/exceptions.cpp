#include "exceptions.h"

using namespace VTF;

Exception::Exception(const char *message)
    : m_message(message)
{
}

const char *Exception::message() const
{
    return m_message.c_str();
}
