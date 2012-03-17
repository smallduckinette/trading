#ifndef __LIBTRADING_ORDERSTATUS_H__
#define __LIBTRADING_ORDERSTATUS_H__

#include <memory>
#include <string>

#include "Order.h"
#include "Quantity.h"
#include "Price.h"

namespace trading
{
  class Order;

  class OrderStatus
  {
  public:
    enum Status
      {
        ACCEPTED,
        PARTIAL_FILL,
        FILL,
        CANCELLED,
        REJECTED
      };
    
    OrderStatus(const OrderId & orderId,
                Status status,
                const std::string & text,
                const Quantity & initialQuantity,
                const Quantity & filledQuantity,
                const Quantity & remainingQuantity,
                const Price & cashValue);

    OrderId getOrderId() const;
    Status getStatus() const;
    std::string getText() const;
    Quantity getInitialQuantity() const;
    Quantity getFilledQuantity() const;
    Quantity getRemainingQuantity() const;
    Price getCashValue() const;
    
    bool operator==(const OrderStatus & orderStatus) const;
    
  private:
    OrderId _orderId;
    Status _status;
    std::string _text;
    Quantity _initialQuantity;
    Quantity _filledQuantity;
    Quantity _remainingQuantity;
    Price _cashValue;
  };

  std::ostream & operator<<(std::ostream & str, const OrderStatus & orderStatus);
}

#endif
