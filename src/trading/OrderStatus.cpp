#include "OrderStatus.h"


trading::OrderStatus::OrderStatus(const OrderId & orderId,
                                  Status status,
                                  const std::string & text,
                                  const Quantity & initialQuantity,
                                  const Quantity & filledQuantity,
                                  const Quantity & remainingQuantity,
                                  const Price & cashValue):
  _orderId(orderId),
  _status(status),
  _text(text),
  _initialQuantity(initialQuantity),
  _filledQuantity(filledQuantity),
  _remainingQuantity(remainingQuantity),
  _cashValue(cashValue)
{
}

trading::OrderId trading::OrderStatus::getOrderId() const
{
  return _orderId;
}

trading::OrderStatus::Status trading::OrderStatus::getStatus() const
{
  return _status;
}

std::string trading::OrderStatus::getText() const
{
  return _text;
}

trading::Quantity trading::OrderStatus::getInitialQuantity() const
{
  return _initialQuantity;
}

trading::Quantity trading::OrderStatus::getFilledQuantity() const
{
  return _filledQuantity;
}

trading::Quantity trading::OrderStatus::getRemainingQuantity() const
{
  return _remainingQuantity;
}

trading::Price trading::OrderStatus::getCashValue() const
{
  return _cashValue;
}

bool trading::OrderStatus::operator==(const OrderStatus & orderStatus) const
{
  return(_orderId == orderStatus._orderId &&
         _status == orderStatus._status &&
         _text == orderStatus._text &&
         _initialQuantity == orderStatus._initialQuantity &&
         _filledQuantity == orderStatus._filledQuantity &&
         _remainingQuantity == orderStatus._remainingQuantity &&
         _cashValue == orderStatus._cashValue);
}

std::ostream & trading::operator<<(std::ostream & str, const OrderStatus & orderStatus)
{
  str << "[OrderStatus OrderId=" << orderStatus.getOrderId()
      << " Status=" << orderStatus.getStatus()
      << " Text='" << orderStatus.getText() 
      << "` InitialQuantity=" << orderStatus.getInitialQuantity()
      << " FilledQuantity=" << orderStatus.getFilledQuantity()
      << " RemainingQuantity=" << orderStatus.getRemainingQuantity()
      << " CashValue=" << orderStatus.getCashValue() 
      << "]";
  return str;
}
