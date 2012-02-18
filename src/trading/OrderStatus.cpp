#include "OrderStatus.h"


trading::OrderStatus::OrderStatus(const std::shared_ptr<Order> & order,
                                  Status status,
                                  const std::string & text,
                                  const Quantity & filledQuantity):
  _order(order),
  _status(status),
  _text(text),
  _filledQuantity(filledQuantity)
{
}

std::shared_ptr<trading::Order> trading::OrderStatus::getOrder() const
{
  return _order;
}

trading::OrderStatus::Status trading::OrderStatus::getStatus() const
{
  return _status;
}

std::string trading::OrderStatus::getText() const
{
  return _text;
}

trading::Quantity trading::OrderStatus::getFilledQuantity() const
{
  return _filledQuantity;
}
