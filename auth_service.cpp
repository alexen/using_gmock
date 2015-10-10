///
/// auth_service.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

#include <boost/throw_exception.hpp>
#include "exception.h"

#include "types.h"
#include "session_manager.h"

namespace alexen {
namespace learning {
namespace server {


AuthService::AuthService( const Settings& settings, const dao::IDaoPtr& dao, const ISessionManagerPtr& sessionManager )
     : settings_( settings )
     , dao_( dao )
     , sessionManager_( sessionManager )
{
}


void AuthService::createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& /*response*/ )
{
     ensureRequestValid( request );

     auto transaction = dao_->beginTransaction();

     const auto authPerson = dao_->findPerson( *transaction, request.login, request.password, request.admin );

     if( !authPerson )
          BOOST_THROW_EXCEPTION( Exception( ErrorCode::AuthFailed ) );

     const auto sessionInfo = sessionManager_->createSessionInfo( *authPerson, settings_.expiryPeriod );

     dao_->storeSessionInfo( *transaction, sessionInfo );

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
