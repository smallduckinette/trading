#include "OrderRegister.h"



void trading::OrderRegister::insertOrder(const OrderInfo & orderInfo)
{
  _orders.insert(orderInfo);
}

bool trading::OrderRegister::removeOrder(const OrderId & orderId, OrderInfo & orderInfo)
{
  auto it = _orders.get<ByOrder>().find(orderId);
  if(it != _orders.get<ByOrder>().end())
  {
    orderInfo = it->_orderInfo;
    _orders.get<ByOrder>().erase(it);
    return true;
  }
  else
  {
    return false;
  }
}

bool trading::OrderRegister::getBestBid(OrderInfo & orderInfo) const
{
  auto it = _orders.get<ByPrice>().rbegin();
  auto end = _orders.get<ByPrice>().rend();
  if(it != end && it->_orderInfo.getOrder()->getSide() == Side::BID)
  {
    orderInfo = it->_orderInfo;
    return true;
  }
  else
  {
    return false;
  }
}

bool trading::OrderRegister::getBestOffer(OrderInfo & orderInfo) const
{
  auto it = _orders.get<ByPrice>().begin();
  auto end = _orders.get<ByPrice>().end();
  if(it != end && it->_orderInfo.getOrder()->getSide() == Side::OFFER)
  {
    orderInfo = it->_orderInfo;
    return true;
  }
  else
  {
    return false;
  }
}

bool trading::OrderRegister::getBest(Side::Enum side, OrderInfo & orderInfo) const
{
  switch(side)
  {
  case Side::BID:
    return getBestBid(orderInfo);
  case Side::OFFER:
    return getBestOffer(orderInfo);
  default:
    throw std::runtime_error("Bad order side");
  }
}

trading::OrderRegister::Item::Item(const OrderInfo & orderInfo):
  _orderInfo(orderInfo)
{
}

trading::OrderId trading::OrderRegister::Item::getOrderId() const
{
  return _orderInfo.getOrder()->getOrderId();
}

trading::TraderId trading::OrderRegister::Item::getTraderId() const
{
  return _orderInfo.getOrder()->getTraderId();
}

bool trading::OrderRegister::Item::operator<(const Item & other) const
{
  if(_orderInfo.getOrder()->getSide() < other._orderInfo.getOrder()->getSide())
    return false;
  if(_orderInfo.getOrder()->getSide() > other._orderInfo.getOrder()->getSide())
    return true;

  if(_orderInfo.getOrder()->getPrice() < other._orderInfo.getOrder()->getPrice())
    return true;
  if(_orderInfo.getOrder()->getPrice() > other._orderInfo.getOrder()->getPrice())
    return false;

  if(_orderInfo.getOrder()->getCreationTime() < other._orderInfo.getOrder()->getCreationTime())
    return true;
  if(_orderInfo.getOrder()->getCreationTime() > other._orderInfo.getOrder()->getCreationTime())
    return false;

  return(_orderInfo.getOrder()->getOrderId() < other._orderInfo.getOrder()->getOrderId());
}
