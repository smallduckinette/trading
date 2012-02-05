#ifndef __LIBTRADING_INSTRUMENT_H__
#define __LIBTRADING_INSTRUMENT_H__

#include "StrongId.h"

namespace trading
{
  class InstrumentDiscriminator;
  typedef StrongId<InstrumentDiscriminator, uint64_t> InstrumentId;
}

#endif
