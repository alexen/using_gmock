///
/// dao.h
///
/// Created on: Oct 3, 2015
///     Author: alexen
///

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

namespace server {


struct Person
{
     boost::uuids::uuid id;
     bool admin;
};


struct SessionInfo
{
     boost::uuids::uuid personId;
     bool admin;
     boost::posix_time::ptime createdAt;
     boost::posix_time::ptime expiresAt;
};


class ITransaction
{
public:
     virtual ~ITransaction() {}

     virtual void commit() = 0;
     virtual void rollback() = 0;
};


class IDao
{
public:
     virtual ~IDao() {}

     virtual ITransaction* beginTransaction() = 0;

     virtual void findPerson( ITransaction& tr, const std::string& login, const std::string& password ) = 0;

     virtual void storeSessionInfo( ITransaction& tr, const std::string& sessionId, const SessionInfo& sessionInfo ) = 0;
};


} // namespace server
