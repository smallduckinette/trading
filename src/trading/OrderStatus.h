#ifndef __LIBTRADING_ORDERSTATUS_H__
#define __LIBTRADING_ORDERSTATUS_H__

#include <memory>
#include <string>

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

    OrderStatus(const std::shared_ptr<Order> & order,
                Status status,
                const std::string & text,
                const Quantity & filledQuantity);

    std::shared_ptr<Order> getOrder() const;
    Status getStatus() const;
    std::string getText() const;
    Quantity getFilledQuantity() const;

  private:
    std::shared_ptr<Order> _order;
    Status _status;
    std::string _text;
    Quantity _filledQuantity;
  };
}

#endif
