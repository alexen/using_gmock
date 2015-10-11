///
/// utils.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

#include <ctime>

namespace alexen {
namespace learning {


template< typename T, typename ... Args >
inline std::unique_ptr< T > make_unique( Args&&... args )
{
     return std::unique_ptr< T >( new T( std::forward<Args>(args)... ) );
}


inline std::time_t toTime_t( const boost::posix_time::ptime& pt )
{
     static boost::posix_time::ptime epoch( boost::gregorian::date( 1970, 1, 1 ) );
     const boost::posix_time::time_duration diff( pt - epoch );
     return static_cast< std::time_t >( diff.ticks() / diff.ticks_per_second() );
}


} // namespace learning
} // namespace alexen
