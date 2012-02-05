#ifndef __LIBTRADING_TRADER_H__
#define __LIBTRADING_TRADER_H__

#include "StrongId.h"

namespace trading
{
  class TraderDiscriminator;
  typedef StrongId<TraderDiscriminator, uint64_t> TraderId;
}

#endif
