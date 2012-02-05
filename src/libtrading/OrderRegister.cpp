#include "OrderRegister.h"



void trading::OrderRegister::insertOrder(const std::shared_ptr<Order> & order)
{
  _orders.insert(Item(order));
}

void trading::OrderRegister::deleteOrder(const OrderId & orderId)
{
  _orders.get<ByOrder>().erase(orderId);
}

trading::OrderRegister::Item::Item(const std::shared_ptr<Order> & order):
  _order(order)
{
}

trading::OrderId trading::OrderRegister::Item::getOrderId() const
{
  return _order->getOrderId();
}

trading::TraderId trading::OrderRegister::Item::getTraderId() const
{
  return _order->getTraderId();
}

bool trading::OrderRegister::Item::operator<(const Item & other) const
{
  if(_order->getSide() < other._order->getSide())
    return false;
  if(_order->getSide() > other._order->getSide())
    return true;

  if(_order->getPrice() < other._order->getPrice())
    return true;
  if(_order->getPrice() > other._order->getPrice())
    return false;

  if(_order->getCreationTime() < other._order->getCreationTime())
    return true;
  if(_order->getCreationTime() > other._order->getCreationTime())
    return false;

  return(_order->getOrderId() < other._order->getOrderId());
}
