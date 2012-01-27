#ifndef __LIBTRADING_QUANTITY_H__
#define __LIBTRADING_QUANTITY_H__

#include <boost/rational.hpp>
#include "Number.h"

namespace trading
{
  class QuantityDiscriminator;
  typedef Number<QuantityDiscriminator, boost::rational<int64_t> > Quantity;
}

#endif
