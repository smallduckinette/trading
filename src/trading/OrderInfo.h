#ifndef __TRADING_ORDERINFO_H__
#define __TRADING_ORDERINFO_H__

#include <memory>

#include "Quantity.h"

namespace trading
{
  class Order;
  class OrderListener;

  class OrderInfo
  {
  public:
    OrderInfo();
    OrderInfo(const std::shared_ptr<Order> & order,
              const std::shared_ptr<OrderListener> & orderListener,
              const Quantity & quantity);
    
    std::shared_ptr<Order> getOrder() const;
    std::shared_ptr<OrderListener> getOrderListener() const;
    Quantity getQuantity() const;

  private:
    std::shared_ptr<Order> _order;
    std::shared_ptr<OrderListener> _orderListener;
    Quantity _quantity;
  };
}

#endif
