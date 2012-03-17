#include "Side.h"

#include <stdexcept>

trading::Side::Enum trading::Side::reverse(Enum side)
{
  switch(side)
  {
  case BID:
    return OFFER;
  case OFFER:
    return BID;
  default:
    throw std::runtime_error("Bad side");
  }
}
