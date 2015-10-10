///
/// exception.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "exception.h"

namespace alexen {
namespace learning {
namespace server {


namespace {
namespace aux {


std::string toString( ErrorCode code )
{
     switch( code )
     {
          case ErrorCode::InternalServerError:    return "internal server error";
          case ErrorCode::InvalidRequest:         return "invalid request";
          case ErrorCode::AuthFailed:             return "auth failed";
          case ErrorCode::SessionExpired:         return "session expired";

          default: ;
     }

     return "unknown error";
}


} // namespace aux
} // namespace {unnamed}


Exception::Exception( ErrorCode code )
     : std::runtime_error( aux::toString( code ) )
     , errorCode_( code )
{
}


} // namespace server
} // namespace learning
} // namespace alexen
