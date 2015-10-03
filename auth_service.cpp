///
/// auth_service.cpp
///
/// Created on: Oct 3, 2015
///     Author: alexen
///

#include "auth_service.h"

#include <boost/throw_exception.hpp>
#include <boost/optional/optional.hpp>

#include "dao.h"


namespace server {


AbstractAuthService::AbstractAuthService( IDao* dao )
     : dao_( dao )
{
     BOOST_ASSERT( dao_ != nullptr );
}


void AbstractAuthService::createSession( const CreateSessionRequest& request, CreateSessionResponse& response )
{
     try
     {
          ensureRequestIsValid( request );
          createSession( request.login, request.password, response );
     }
     catch( const IAuthService::Exception& e )
     {
          response.error = e.error();
     }
     catch( const std::exception& e )
     {
          IAuthService::Error error;

          error.type = IAuthService::Error::Type::InternalError;
          error.message = e.what();

          response.error = error;
     }
     catch( ... )
     {
          IAuthService::Error error;

          error.type = IAuthService::Error::Type::InternalError;
          error.message = "unknown error";

          response.error = error;
     }
}


void AbstractAuthService::ensureRequestIsValid( const CreateSessionRequest& request )
{
     if( request.login.empty() || request.password.empty() )
          BOOST_THROW_EXCEPTION( IAuthService::Exception( IAuthService::Error::Type::InvalidInputData, "login and password is not set but required" ) );
}


void AbstractAuthService::createSession( const std::string& login, const std::string& password, CreateSessionResponse& response )
{
}


void AbstractAuthService::prolongSession( const std::string& sessionId, ProlongSessionResponse& response )
{

}


void AbstractAuthService::prolongSession( const ProlongSessionRequest& request, ProlongSessionResponse& response )
{
}


} // namespace server
