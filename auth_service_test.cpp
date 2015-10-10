///
/// auth_service_test.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

#include <algorithm>

#include <boost/make_shared.hpp>
#include <boost/uuid/random_generator.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::make_shared;

namespace {


using alexen::learning::server::dao::ITransaction;
using alexen::learning::server::dao::ITransactionPtr;
using alexen::learning::server::dao::IDao;
using alexen::learning::server::dao::IDaoPtr;
using alexen::learning::server::Person;
using alexen::learning::server::SessionInfo;
using alexen::learning::server::AuthService;
using alexen::learning::server::protocol::CreateSessionRequest;
using alexen::learning::server::protocol::CreateSessionResponse;


class MockTransaction : public ITransaction {
public:
     MOCK_CONST_METHOD0( isActive, bool( void ) );
     MOCK_METHOD0( commit, void( void ) );
     MOCK_METHOD0( rollback, void( void ) );
};


class MockDao : public IDao {
public:
     MOCK_METHOD0( beginTransaction, ITransactionPtr( void ) );
     MOCK_METHOD4( findPerson, boost::optional< Person >( ITransaction& tr, const std::string& login, const std::string& password, bool admin ) );
     MOCK_METHOD2( storeSessionInfo, void( ITransaction& tr, const SessionInfo& sessionInfo ) );
};


} // namespace {unnamed}


TEST( AuthServiceTest, SuccessAuthorization )
{
     using namespace ::testing;

     auto dao = boost::make_shared< MockDao >();

     auto transaction = boost::make_shared< MockTransaction >();

     EXPECT_CALL( *dao, beginTransaction() )
          .WillOnce( Return( transaction ) );

     CreateSessionRequest request;

     request.login = "login";
     request.password = "password";
     request.admin = false;

     Person person;

     person.id = boost::uuids::random_generator()();
     person.admin = std::accumulate( person.id.begin(), person.id.end(), 0 ) % 2;

     EXPECT_CALL( *dao, findPerson( Ref( *transaction ), request.login, request.password, request.admin ) )
          .WillOnce( Return( person ) );
     EXPECT_CALL( *transaction, commit() )
          .WillOnce( Return() );

     CreateSessionResponse response;

     AuthService( dao ).createSession( request, response );
}
