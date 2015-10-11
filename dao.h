///
/// dao.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/optional/optional.hpp>
#include <boost/shared_ptr.hpp>

#include "types.h"


namespace alexen {
namespace learning {
namespace server {
namespace dao {


class ITransaction {
public:
     virtual ~ITransaction() {}

     virtual bool isActive() const = 0;

     virtual void commit() = 0;
     virtual void rollback() = 0;
};

using ITransactionPtr = boost::shared_ptr< ITransaction  >;


class IDao {
public:
     virtual ~IDao() {}

     virtual ITransactionPtr beginTransaction() = 0;

     virtual boost::optional< Person > findPerson( ITransaction& tr, const std::string& login, const std::string& password, bool admin ) = 0;

     virtual std::size_t storeSessionInfo( ITransaction& tr, const SessionInfo& sessionInfo ) = 0;
};

using IDaoPtr = boost::shared_ptr< IDao >;


} // namespace dao
} // namespace server
} // namespace learning
} // namespace alexen
