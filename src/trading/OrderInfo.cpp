#include "OrderInfo.h"


trading::OrderInfo::OrderInfo()
{
}

trading::OrderInfo::OrderInfo(const std::shared_ptr<Order> & order,
                              const std::shared_ptr<OrderListener> & orderListener,
                              const Quantity & quantity):
  _order(order),
  _orderListener(orderListener),
  _quantity(quantity)
{
}

std::shared_ptr<trading::Order> trading::OrderInfo::getOrder() const
{
  return _order;
}

std::shared_ptr<trading::OrderListener> trading::OrderInfo::getOrderListener() const
{
  return _orderListener;
}

trading::Quantity trading::OrderInfo::getQuantity() const
{
  return _quantity;
}
