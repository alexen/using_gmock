///
/// session_manager.h
///
/// Created on: 11 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include "types.h"

#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/shared_ptr.hpp>


namespace alexen {
namespace learning {
namespace server {


class ISessionManager
{
public:
     virtual ~ISessionManager() {}

     virtual SessionInfo createSessionInfo( const Person& person, const boost::posix_time::time_duration& expiryPeriod ) const = 0;

private:
     virtual std::string generateSessionId( bool adminSession ) const = 0;
     virtual std::string generateUniqueSequence() const = 0;
};

using ISessionManagerPtr = boost::shared_ptr< ISessionManager >;


} // namespace server
} // namespace learning
} // namespace alexen
