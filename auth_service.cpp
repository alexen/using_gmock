///
/// auth_service.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

#include <boost/throw_exception.hpp>
#include "exception.h"

namespace alexen {
namespace learning {
namespace server {


AuthService::AuthService( const dao::IDaoPtr& dao )
     : dao_( dao )
{
}


void AuthService::createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& /*response*/ )
{
     ensureRequestValid( request );

     auto transaction = dao_->beginTransaction();

     const auto authPerson = dao_->findPerson( *transaction, request.login, request.password, request.admin );

     if( !authPerson )
          BOOST_THROW_EXCEPTION( Exception( ErrorCode::AuthFailed ) );

     transaction->commit();
}


void AuthService::prolongSession( const protocol::ProlongSessionRequest& request, protocol::ProlongSessionResponse& response )
{
     ( void ) request;
     ( void ) response;
}


void AuthService::ensureRequestValid( const protocol::CreateSessionRequest& request )
{
     if( request.login.empty() || request.password.empty() )
          BOOST_THROW_EXCEPTION( Exception( ErrorCode::InvalidRequest ) );
}


} // namespace server
} // namespace learning
} // namespace alexen
