#include "MatchingListing.h"

#include "OrderListener.h"
#include "OrderStatus.h"


trading::MatchingListing::MatchingListing(boost::asio::io_service & io_service,
                                          const InstrumentId & instrumentId):
  _strand(io_service),
  _instrumentId(instrumentId)
{
}

trading::InstrumentId trading::MatchingListing::getInstrumentId() const
{
  return _instrumentId;
}

void trading::MatchingListing::addOrder(const OrderInfo & orderInfo)
{
  _strand.post(std::bind(&MatchingListing::doAddOrder,
                         shared_from_this(),
                         orderInfo));
}

void trading::MatchingListing::cancelOrder(const OrderId & orderId)
{
  _strand.post(std::bind(&MatchingListing::doCancelOrder,
                         shared_from_this(),
                         orderId));
}

void trading::MatchingListing::doAddOrder(const OrderInfo & orderInfo)
{
  if(orderInfo.getOrder()->getInstrumentId() == _instrumentId)
  {  
    _orderRegister.insertOrder(orderInfo);
    orderInfo.getOrderListener()->onOrderStatus(OrderStatus(orderInfo.getOrder()->getOrderId(),
                                                            OrderStatus::ACCEPTED,
                                                            "Accepted",
                                                            orderInfo.getOrder()->getQuantity(),
                                                            Quantity(0),
                                                            orderInfo.getOrder()->getQuantity()));
  }
  else
  {
    orderInfo.getOrderListener()->onOrderStatus(OrderStatus(orderInfo.getOrder()->getOrderId(),
                                                            OrderStatus::ERRORED,
                                                            "InstrumentId mismatch",
                                                            Quantity(0),
                                                            Quantity(0),
                                                            Quantity(0)));
  }
}

void trading::MatchingListing::doCancelOrder(const OrderId & orderId)
{
  OrderInfo orderInfo;
  if(_orderRegister.removeOrder(orderId, orderInfo))
  {
    orderInfo.getOrderListener()->onOrderStatus(OrderStatus(orderId,
                                                            OrderStatus::CANCELLED,
                                                            "Cancelled",
                                                            Quantity(0),
                                                            Quantity(0),
                                                            Quantity(0)));
  }
}
