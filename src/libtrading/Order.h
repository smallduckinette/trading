#ifndef __LIBTRADING_ORDER_H__
#define __LIBTRADING_ORDER_H__

#include "StrongId.h"
#include "Instrument.h"
#include "Trader.h"
#include "Price.h"
#include "Quantity.h"

namespace trading
{
  class OrderDiscriminator;
  typedef StrongId<OrderDiscriminator, int64_t> OrderId;
  
  class Order
  {
  public:
    Order(const OrderId & orderId,
          const InstrumentId & instrumentId,
          const TraderId & traderId,
          const Price & price,
          const Quantity & quantity);

    OrderId getOrderId() const;
    InstrumentId getInstrumentId() const;
    TraderId getTraderId() const;
    Price getPrice() const;
    Quantity getQuantity() const;
    
  private:
    OrderId _orderId;
    InstrumentId _instrumentId;
    TraderId _traderId;
    Price _price;
    Quantity _quantity;
  };
}

#endif
