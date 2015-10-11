///
/// types.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

namespace alexen {
namespace learning {
namespace server {


struct Person {
     boost::uuids::uuid id;
     bool admin;
};


inline bool operator==( const Person& left, const Person& right )
{
     return( left.id == right.id )
          &&( left.admin == right.admin );
}


struct SessionInfo {
     std::string sessionId;
     boost::uuids::uuid personId;
     bool admin;
     boost::posix_time::ptime createdAt;
     boost::posix_time::ptime expiresAt;
};


inline bool operator==( const SessionInfo& left, const SessionInfo& right )
{
     return( left.sessionId == right.sessionId )
          &&( left.personId == right.personId )
          &&( left.createdAt == right.createdAt )
          &&( left.expiresAt == right.expiresAt )
          &&( left.admin == right.admin );
}


} // namespace server
} // namespace learning
} // namespace alexen
