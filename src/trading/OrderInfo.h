#ifndef __TRADING_ORDERINFO_H__
#define __TRADING_ORDERINFO_H__

#include <memory>

#include "Quantity.h"
#include "Price.h"

namespace trading
{
  class Order;
  class OrderListener;

  class OrderInfo
  {
  public:
    OrderInfo();
    OrderInfo(const std::shared_ptr<Order> & order,
              const std::shared_ptr<OrderListener> & orderListener);
    
    std::shared_ptr<Order> getOrder() const;
    Quantity getOpenQuantity() const;
    Quantity getTradedQuantity() const;
    
    void onInsert() const;
    void onReject(const std::string & reason) const;
    void onCancel() const;
    void onTradeQuantity(const Quantity & tradedQuantity, const Price & tradedPrice);
    
  private:
    std::shared_ptr<Order> _order;
    std::shared_ptr<OrderListener> _orderListener;
    Quantity _openQuantity;
    Quantity _tradedQuantity;
    Price _cashValue;
  };
}

#endif
