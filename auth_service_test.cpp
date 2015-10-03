///
/// auth_service_test.cpp
///
/// Created on: Oct 3, 2015
///     Author: alexen
///

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "auth_service.h"
#include "dao.h"

class MockDao : public server::IDao
{
public:
     MOCK_METHOD0( beginTransaction, server::ITransaction*( void ) );
     MOCK_METHOD3( findPerson, void( server::ITransaction& tr, const std::string& login, const std::string& password ) );
     MOCK_METHOD3( storeSessionInfo, void( server::ITransaction& tr, const std::string& sessionId, const server::SessionInfo& sessionInfo ) );
};

class MockAuthService : public server::AbstractAuthService
{
public:
     explicit MockAuthService( server::IDao* dao ) : AbstractAuthService( dao ) {}
     MOCK_METHOD1( ensureRequestIsValid, void( const server::IAuthService::CreateSessionRequest& request ) );
};


using ::testing::_;


TEST( AuthServiceTest, CreateSession )
{
     MockDao dao;

     server::IAuthService::CreateSessionRequest request;

     request.login = "login";
     request.password = "password";

     server::IAuthService::CreateSessionResponse response;

     MockAuthService authService( &dao );

     authService.createSession( request, response );

     EXPECT_CALL( authService, ensureRequestIsValid( request ) ).Times( 1 );
}
