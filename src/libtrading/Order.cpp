#include "Order.h"


trading::Order::Order(const OrderId & orderId,
                      const InstrumentId & instrumentId,
                      const TraderId & traderId,
                      const Price & price,
                      const Quantity & quantity):
  _orderId(orderId),
  _instrumentId(instrumentId),
  _traderId(traderId),
  _price(price),
  _quantity(quantity)
{
}

trading::OrderId trading::Order::getOrderId() const
{
  return _orderId;
}

trading::InstrumentId trading::Order::getInstrumentId() const
{
  return _instrumentId;
}

trading::TraderId trading::Order::getTraderId() const
{
  return _traderId;
}

trading::Price trading::Order::getPrice() const
{
  return _price;
}

trading::Quantity trading::Order::getQuantity() const
{
  return _quantity;
}
