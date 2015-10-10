///
/// auth_service_test.cpp
///
/// Created on: 10 окт. 2015 г.
///     Author: alexen
///

#include "auth_service.h"

namespace alexen {
namespace learning {
namespace server {

} // namespace server
} // namespace learning
} // namespace alexen


#include <iostream>
#include <boost/exception/diagnostic_information.hpp>

int main()
{
     try
     {

     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e )
               << '\n';
          return 1;
     }

     return 0;
}
