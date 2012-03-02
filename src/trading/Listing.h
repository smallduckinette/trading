#ifndef __LIBTRADING_LISTING_H__
#define __LIBTRADING_LISTING_H__

#include "Order.h"

namespace trading
{
  class OrderInfo;

  class Listing
  {
  public:
    virtual ~Listing();
    
    virtual InstrumentId getInstrumentId() const = 0;
    
    virtual void addOrder(const OrderInfo & order) = 0;
    virtual void cancelOrder(const OrderId & orderId) = 0;
  };
}

#endif
