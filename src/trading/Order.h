#ifndef __LIBTRADING_ORDER_H__
#define __LIBTRADING_ORDER_H__

#include <chrono>

#include "StrongId.h"
#include "Instrument.h"
#include "Trader.h"
#include "Price.h"
#include "Quantity.h"
#include "Side.h"

namespace trading
{
  typedef std::chrono::time_point<std::chrono::monotonic_clock> TimePointT;
  
  class OrderDiscriminator;
  typedef StrongId<OrderDiscriminator, int64_t> OrderId;
  
  class Order
  {
  public:
    Order(const OrderId & orderId,
          const InstrumentId & instrumentId,
          const TraderId & traderId,
          const Price & price,
          const Quantity & quantity,
          Side::Enum side,
          const TimePointT & creationTime);

    OrderId getOrderId() const;
    InstrumentId getInstrumentId() const;
    TraderId getTraderId() const;
    Price getPrice() const;
    Quantity getQuantity() const;
    Side::Enum getSide() const;
    TimePointT getCreationTime() const;
    
  private:
    OrderId _orderId;
    InstrumentId _instrumentId;
    TraderId _traderId;
    Price _price;
    Quantity _quantity;
    Side::Enum _side;
    TimePointT _creationTime;
  };
}

#endif
