#ifndef __TRADING_SIDE_H__
#define __TRADING_SIDE_H__

namespace trading
{
  class Side
  {
  public:
    enum Enum
      {
        BID,
        OFFER
      };

    static Enum reverse(Enum side);
  };
}

#endif
