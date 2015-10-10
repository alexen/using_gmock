///
/// auth_service.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <string>
#include <cstdint>
#include <boost/variant/variant.hpp>

#include "dao.h"


namespace alexen {
namespace learning {
namespace server {


namespace protocol {


struct Error {
     int code;
     std::string message;
};


struct CreateSessionRequest {
     std::string login;
     std::string password;
     bool admin;
};


using SessionExpirationTime = std::uint64_t;


struct SessionInfo {
     std::string sesionId;
     std::string userId;
     SessionExpirationTime expiresAt;
};


struct CreateSessionResponse {
     boost::variant< Error, SessionInfo > response;
};


struct ProlongSessionRequest {
     std::string sessionId;
};


struct ProlongSessionResponse {
     boost::variant< Error, SessionExpirationTime > response;
};


} // namespace protocol


class IAuthService {
public:
     virtual ~IAuthService() {}

     virtual void createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& response ) = 0;
     virtual void prolongSession( const protocol::ProlongSessionRequest& request, protocol::ProlongSessionResponse& response ) = 0;
};


class AuthService : public IAuthService {
public:
     explicit AuthService( const dao::IDaoPtr& dao );

     void createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& response ) override;
     void prolongSession( const protocol::ProlongSessionRequest& request, protocol::ProlongSessionResponse& response ) override;

private:
     void ensureRequestValid( const protocol::CreateSessionRequest& request );

     dao::IDaoPtr dao_;
};


} // namespace server
} // namespace learning
} // namespace alexen
