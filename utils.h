///
/// utils.h
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#pragma once

namespace alexen {
namespace learning {


template< typename T, typename ... Args >
inline std::unique_ptr< T > make_unique( Args&&... args )
{
     return std::unique_ptr< T >( new T( std::forward<Args>(args)... ) );
}


} // namespace learning
} // namespace alexen
