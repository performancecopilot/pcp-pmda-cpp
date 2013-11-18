//               Copyright Paul Colby 2013.
// Distributed under the Boost Software License, Version 1.0.
//       (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef __PCP_CPP_EXCEPTION_HPP__
#define __PCP_CPP_EXCEPTION_HPP__

#include "config.hpp"

#include <pcp/pmapi.h>

#include <string>

PCP_CPP_BEGIN_NAMESPACE

namespace pcp {

class exception : public std::exception {

public:
    exception(const int pm_error_code,
              const std::string &message = std::string())
        : pm_error_code(pm_error_code),
          message(message)
    {
        if (message.empty()) {
            char buffer[PM_MAXERRMSGLEN];
            pmErrStr_r(pm_error_code, buffer, sizeof(buffer));
            this->message.assign(buffer);
        }
    }

    exception(const pcp::exception &other)
        : pm_error_code(other.error_code()),
          message(other.what())
    {
    }

    virtual ~exception() throw() { };

    virtual int error_code() const
    {
        return pm_error_code;
    }

    virtual const char* what() const throw()
    {
        return message.c_str();
    }

protected:
    int pm_error_code;
    std::string message;
};

} // pcp namespace.

PCP_CPP_END_NAMESPACE

#endif