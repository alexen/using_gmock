///
/// types.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

namespace alexen {
namespace learning {
namespace server {


struct Person {
     boost::uuids::uuid id;
     bool admin;
};


struct SessionInfo {
     std::string sessionId;
     boost::uuids::uuid personId;
     bool admin;
     boost::posix_time::ptime createdAt;
     boost::posix_time::ptime expiresAt;
};


} // namespace server
} // namespace learning
} // namespace alexen
