#ifndef __LIBTRADING_PRICE_H__
#define __LIBTRADING_PRICE_H__

#include <boost/rational.hpp>
#include "Number.h"

namespace trading
{
  class PriceDiscriminator;
  typedef Number<PriceDiscriminator, boost::rational<int64_t> > Price;
}

#endif
