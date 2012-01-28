#ifndef __LIBTRADING_ORDERSTATUS_H__
#define __LIBTRADING_ORDERSTATUS_H__

#include "Order.h"

namespace trading
{
  class OrderStatus
  {
  public:
    enum Status
      {
        ACCEPTED,
        COMPLETED,
        CANCELLED,
        ERRORED
      };

    OrderStatus(const OrderId & orderId,
                const InstrumentId & instrumentId,
                const Price & price,
                Status status,
                const Quantity & initialQuantity,
                const Quantity & remainingQuantity,
                const Quantity & filledQuantity);
    
    OrderId getOrderId() const;
    InstrumentId getInstrumentId() const;
    Price getPrice() const;
    Status getStatus() const;
    Quantity getInitialQuantity() const;
    Quantity getRemainingQuantity() const;
    Quantity getFilledQuantity() const;

  private:
    OrderId _orderId;
    InstrumentId _instrumentId;
    Price _price;
    Status _status;
    Quantity _initialQuantity;
    Quantity _remainingQuantity;
    Quantity _filledQuantity;
  };
}

#endif
