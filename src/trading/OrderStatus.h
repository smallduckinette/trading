#ifndef __LIBTRADING_ORDERSTATUS_H__
#define __LIBTRADING_ORDERSTATUS_H__

#include <memory>
#include <string>

#include "Order.h"
#include "Quantity.h"

namespace trading
{
  class Order;

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
                Status status,
                const std::string & text,
                const Quantity & initialQuantity,
                const Quantity & filledQuantity,
                const Quantity & remainingQuantity);

    OrderId getOrderId() const;
    Status getStatus() const;
    std::string getText() const;
    Quantity getInitialQuantity() const;
    Quantity getFilledQuantity() const;
    Quantity getRemainingQuantity() const;
    
    bool operator==(const OrderStatus & orderStatus) const;
    
  private:
    OrderId _orderId;
    Status _status;
    std::string _text;
    Quantity _initialQuantity;
    Quantity _filledQuantity;
    Quantity _remainingQuantity;
  };
}

#endif
