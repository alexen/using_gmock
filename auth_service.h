///
/// auth_service.h
///
/// Created on: Oct 3, 2015
///     Author: alexen
///

#pragma once

#include <string>
#include <stdexcept>
#include <boost/optional/optional.hpp>

namespace server {


class IDao;


class IAuthService
{
public:
     struct Error
     {
          enum class Type
          {
               InternalError,
               InvalidInputData,
               AuthFailed
          };

          Type type;
          std::string message;
     };

     class Exception : public std::runtime_error
     {
     public:
          Exception( const Error::Type errorType, const std::string& message )
               : std::runtime_error( message )
               , errorType_( errorType )
          {}

          Error error() const
          {
               return Error{ errorType_, what() };
          }

     private:
          const Error::Type errorType_;
     };

     struct CreateSessionRequest
     {
          std::string login;
          std::string password;
     };

     struct CreateSessionResponse
     {
          std::string userId;
          std::string sessionId;

          boost::optional< Error > error;
     };

     struct ProlongSessionRequest
     {
          std::string sessionId;
     };

     struct ProlongSessionResponse
     {
          boost::optional< Error > error;
     };

     virtual ~IAuthService() {}

     virtual void createSession( const CreateSessionRequest& request, CreateSessionResponse& response ) = 0;
     virtual void prolongSession( const ProlongSessionRequest& request, ProlongSessionResponse& response ) = 0;
};


class AbstractAuthService : public IAuthService
{
public:
     explicit AbstractAuthService( IDao* dao );

     void createSession( const CreateSessionRequest& request, CreateSessionResponse& response ) override;
     void prolongSession( const ProlongSessionRequest& request, ProlongSessionResponse& response ) override;

private:
     virtual void ensureRequestIsValid( const CreateSessionRequest& request );

     void createSession( const std::string& login, const std::string& password, CreateSessionResponse& response );
     void prolongSession( const std::string& sessionId, ProlongSessionResponse& response );

     IDao* dao_;
};


} // namespace server
