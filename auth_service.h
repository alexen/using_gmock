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


namespace alexen {
namespace learning {
namespace server {


namespace protocol {


enum class ErrorCode {
     InternalServerError,
     InvalidRequest,
     AuthFailed,
     SessionExpired
};


struct Error {
     ErrorCode code;
     std::string message;
};


struct CreateSessionRequest {
     std::string login;
     std::string password;
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
     AuthService();

     void createSession( const protocol::CreateSessionRequest& request, protocol::CreateSessionResponse& response ) override;
     void prolongSession( const protocol::ProlongSessionRequest& request, protocol::ProlongSessionResponse& response ) override;

private:
};


} // namespace server
} // namespace learning
} // namespace alexen
