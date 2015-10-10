///
/// exception.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <stdexcept>


namespace alexen {
namespace learning {
namespace server {


enum class ErrorCode {
     InternalServerError,
     InvalidRequest,
     AuthFailed,
     SessionExpired
};


class Exception : public std::runtime_error
{
public:
     explicit Exception( ErrorCode code );

     ErrorCode errorCode() const
     {
          return errorCode_;
     }

private:
     const ErrorCode errorCode_;
};


} // namespace server
} // namespace learning
} // namespace alexen
