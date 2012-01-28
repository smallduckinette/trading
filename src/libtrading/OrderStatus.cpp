#include "OrderStatus.h"


trading::OrderStatus::OrderStatus(const OrderId & orderId,
                                  const InstrumentId & instrumentId,
                                  const Price & price,
                                  Status status,
                                  const Quantity & initialQuantity,
                                  const Quantity & remainingQuantity,
                                  const Quantity & filledQuantity):
  _orderId(orderId),
  _instrumentId(instrumentId),
  _price(price),
  _status(status),
  _initialQuantity(initialQuantity),
  _remainingQuantity(remainingQuantity),
  _filledQuantity(filledQuantity)
{
}

trading::OrderId trading::OrderStatus::getOrderId() const
{
  return _orderId;
}

trading::InstrumentId trading::OrderStatus::getInstrumentId() const
{
  return _instrumentId;
}

trading::Price trading::OrderStatus::getPrice() const
{
  return _price;
}

trading::OrderStatus::Status trading::OrderStatus::getStatus() const
{
  return _status;
}

trading::Quantity trading::OrderStatus::getInitialQuantity() const
{
  return _initialQuantity;
}

trading::Quantity trading::OrderStatus::getRemainingQuantity() const
{
  return _remainingQuantity;
}

trading::Quantity trading::OrderStatus::getFilledQuantity() const
{
  return _filledQuantity;
}
