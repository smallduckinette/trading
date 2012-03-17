#include "OrderInfo.h"

#include "Order.h"
#include "OrderStatus.h"
#include "OrderListener.h"

trading::OrderInfo::OrderInfo()
{
}

trading::OrderInfo::OrderInfo(const std::shared_ptr<Order> & order,
                              const std::shared_ptr<OrderListener> & orderListener):
  _order(order),
  _orderListener(orderListener),
  _openQuantity(order->getQuantity()),
  _tradedQuantity(0),
  _cashValue(0)
{
}

std::shared_ptr<trading::Order> trading::OrderInfo::getOrder() const
{
  return _order;
}

trading::Quantity trading::OrderInfo::getOpenQuantity() const
{
  return _openQuantity;
}

trading::Quantity trading::OrderInfo::getTradedQuantity() const
{
  return _tradedQuantity;
}

void trading::OrderInfo::onInsert() const
{
  _orderListener->onOrderStatus(OrderStatus(_order->getOrderId(),
                                            OrderStatus::ACCEPTED,
                                            "Accepted",
                                            _order->getQuantity(),
                                            _tradedQuantity,
                                            _openQuantity,
                                            _cashValue));
}

void trading::OrderInfo::onReject(const std::string & reason) const
{
  _orderListener->onOrderStatus(OrderStatus(_order->getOrderId(),
                                            OrderStatus::REJECTED,
                                            reason,
                                            _order->getQuantity(),
                                            _tradedQuantity,
                                            _openQuantity,
                                            _cashValue));
}

void trading::OrderInfo::onCancel() const
{
  _orderListener->onOrderStatus(OrderStatus(_order->getOrderId(),
                                            OrderStatus::CANCELLED,
                                            "Cancelled",
                                            _order->getQuantity(),
                                            _tradedQuantity,
                                            _openQuantity,
                                            _cashValue));
}

void trading::OrderInfo::onTradeQuantity(const Quantity & tradedQuantity, const Price & tradedPrice)
{
  _tradedQuantity += tradedQuantity;
  _openQuantity = std::max(Quantity(0), _openQuantity - tradedQuantity);
  _cashValue += tradedPrice * tradedQuantity.getValue();
  
  _orderListener->onOrderStatus(OrderStatus(_order->getOrderId(),
                                            _openQuantity > Quantity(0) ? OrderStatus::PARTIAL_FILL : OrderStatus::FILL,
                                            _openQuantity > Quantity(0) ? "Partially filled" : "Filled",
                                            _order->getQuantity(),
                                            _tradedQuantity,
                                            _openQuantity,
                                            _cashValue));
}
