/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

#include <numeric>

#include <boost/variant.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/make_shared.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "session_manager.h"
#include "utils.h"
#include "exception.h"


namespace {


using alexen::learning::server::Exception;
using alexen::learning::server::ErrorCode;
using alexen::learning::server::dao::ITransaction;
using alexen::learning::server::dao::ITransactionPtr;
using alexen::learning::server::dao::IDao;
using alexen::learning::server::dao::IDaoPtr;
using alexen::learning::server::Person;
using alexen::learning::server::SessionInfo;
using alexen::learning::server::AuthService;
using alexen::learning::server::ISessionManager;
using alexen::learning::server::protocol::CreateSessionRequest;
using alexen::learning::server::protocol::CreateSessionResponse;

namespace protocol = alexen::learning::server::protocol;


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


class MockSessionManager : public ISessionManager {
public:
     MOCK_CONST_METHOD2( createSessionInfo, SessionInfo( const Person& person, const boost::posix_time::time_duration& expiryPeriod ) );
     MOCK_CONST_METHOD1( generateSessionId, std::string( bool adminSession ) );
     MOCK_CONST_METHOD0( generateUniqueSequence, std::string( void ) );
};


class AuthServiceTest : public ::testing::Test {
public:
     AuthServiceTest()
          : settings( boost::posix_time::minutes( 15 ) )
          , dao( boost::make_shared< MockDao >() )
          , sessionManager( boost::make_shared< MockSessionManager >() )
          , authService( settings, dao, sessionManager )
     {}

protected:
     const AuthService::Settings settings;
     boost::shared_ptr< MockDao > dao;
     boost::shared_ptr< MockSessionManager > sessionManager;
     AuthService authService;
};


CreateSessionRequest createRequest()
{
     CreateSessionRequest request;

     request.login = "login";
     request.password = "password";
     request.admin = false;

     return request;
}


Person generatePerson()
{
     Person person;

     person.id = boost::uuids::random_generator()();
     person.admin = std::accumulate( person.id.begin(), person.id.end(), 0 ) % 2;

     return person;
}


SessionInfo createSessionInfo( const Person& person, const boost::posix_time::time_duration& duration )
{
     SessionInfo sessionInfo;

     sessionInfo.personId = person.id;
     sessionInfo.admin = person.admin;
     sessionInfo.createdAt = boost::posix_time::second_clock::universal_time();
     sessionInfo.expiresAt = sessionInfo.createdAt + duration;
     sessionInfo.sessionId = boost::lexical_cast< std::string >( person.admin ) + "/" + boost::uuids::to_string( boost::uuids::random_generator()() );

     return sessionInfo;
}


class CreateSessionResponseExtractor : public boost::static_visitor<> {
public:
     void operator()( const protocol::SessionInfo& sessionInfo )
     {
          sessionInfo_ = sessionInfo;
     }

     void operator()( const protocol::Error& error )
     {
          error_ = error;
     }

     bool hasSessionInfo() const
     {
          return !!sessionInfo_;
     }

     bool hasError() const
     {
          return !!error_;
     }

     const protocol::SessionInfo& sessionInfo() const
     {
          BOOST_ASSERT( hasSessionInfo() );
          return *sessionInfo_;
     }

     const protocol::Error& error() const
     {
          BOOST_ASSERT( hasError() );
          return *error_;
     }

private:
     boost::optional< protocol::SessionInfo > sessionInfo_;
     boost::optional< protocol::Error > error_;
};


} // namespace {unnamed}


TEST_F( AuthServiceTest, SuccessAuthorization )
{
     using namespace ::testing;

     auto transaction = boost::make_shared< MockTransaction >();

     EXPECT_CALL( *dao, beginTransaction() )
          .WillOnce( Return( transaction ) );

     EXPECT_CALL( *dao, findPerson( _, _, _, _ ) )
          .WillOnce( Return( Person() ) );

     EXPECT_CALL( *sessionManager, createSessionInfo( _, _ ) )
          .WillOnce( Return( SessionInfo() ) );

     EXPECT_CALL( *dao, storeSessionInfo( _, _ ) )
          .WillOnce( Return() );

     EXPECT_CALL( *transaction, commit() )
          .WillOnce( Return() );

     CreateSessionRequest request = createRequest();
     CreateSessionResponse response;

     ASSERT_NO_THROW( authService.createSession( request, response ) );
}


TEST_F( AuthServiceTest, CreateSession_InvalidRequest )
{
     CreateSessionRequest request;
     CreateSessionResponse response;

     boost::optional< ErrorCode > errorCode;

     try
     {
          authService.createSession( request, response );

          FAIL() << "Exception expected";
     }
     catch( const Exception& e )
     {
          errorCode = e.errorCode();
     }
     catch( ... )
     {
          FAIL() << "Unexpected exception type";
     }

     ASSERT_EQ( errorCode, ErrorCode::InvalidRequest);
}
