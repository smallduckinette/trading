#include "OrderInfo.h"

#include "Order.h"

trading::OrderInfo::OrderInfo()
{
}

trading::OrderInfo::OrderInfo(const std::shared_ptr<Order> & order,
                              const std::shared_ptr<OrderListener> & orderListener):
  _order(order),
  _orderListener(orderListener),
  _openQuantity(order->getQuantity()),
  _tradedQuantity(0)
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

trading::Quantity trading::OrderInfo::getOpenQuantity() const
{
  return _openQuantity;
}

trading::Quantity trading::OrderInfo::getTradedQuantity() const
{
  return _tradedQuantity;
}

void trading::OrderInfo::tradeQuantity(const Quantity & tradedQuantity)
{
  _tradedQuantity += tradedQuantity;
  _openQuantity = std::max(Quantity(0), _openQuantity - tradedQuantity);
}
