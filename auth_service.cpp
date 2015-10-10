///
/// auth_service.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

namespace alexen {
namespace learning {
namespace server {


AuthService::AuthService()
{
}


void AuthService::createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& response )
{
     ( void ) request;
     ( void ) response;
}


void AuthService::prolongSession( const protocol::ProlongSessionRequest& request, protocol::ProlongSessionResponse& response )
{
     ( void ) request;
     ( void ) response;
}


} // namespace server
} // namespace learning
} // namespace alexen
