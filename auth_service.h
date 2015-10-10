///
/// auth_service.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <string>
#include <cstdint>

namespace alexen {
namespace learning {
namespace server {


namespace protocol {


struct CreateSessionRequest {
     std::string login;
     std::string password;
};


struct CreateSessionResponse {
     std::string sesionId;
     std::string userId;
     std::uint64_t expiresAt;
};

} // namespace protocol


class IAuthService {
public:
     virtual ~IAuthService() {}

     virtual void createSession() = 0;
     virtual void prolongSession()  = 0;
};


class AuthService : public IAuthService {
public:
     AuthService();

private:
};


} // namespace server
} // namespace learning
} // namespace alexen
