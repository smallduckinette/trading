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

void trading::MatchingListing::updateOrder(const OrderId & orderId, 
                                           const OrderInfo & orderInfo)
{
  _strand.post(std::bind(&MatchingListing::doUpdateOrder,
                         shared_from_this(),
                         orderId,
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
    orderInfo.getOrderListener()->onOrderInsert(OrderStatus(orderInfo.getOrder(),
                                                            OrderStatus::ACCEPTED,
                                                            "Accepted",
                                                            Quantity(0)));
  }
  else
  {
    orderInfo.getOrderListener()->onOrderInsert(OrderStatus(orderInfo.getOrder(),
                                                            OrderStatus::ERRORED,
                                                            "InstrumentId mismatch",
                                                            Quantity(0)));
  }
}

void trading::MatchingListing::doUpdateOrder(const OrderId & orderId,
                                             const OrderInfo & orderInfo)
{
  OrderInfo oldOrderInfo;
  if(_orderRegister.removeOrder(orderId, oldOrderInfo))
  {
    _orderRegister.insertOrder(orderInfo);
    orderInfo.getOrderListener()->onOrderUpdate(OrderStatus(orderInfo.getOrder(),
                                                            OrderStatus::ACCEPTED,
                                                            "Updated",
                                                            Quantity(0)));
  }
  else
  {
    orderInfo.getOrderListener()->onOrderUpdate(OrderStatus(orderInfo.getOrder(),
                                                            OrderStatus::ERRORED,
                                                            "Order not found",
                                                            Quantity(0)));    
  }
}

void trading::MatchingListing::doCancelOrder(const OrderId & orderId)
{
  OrderInfo orderInfo;
  if(_orderRegister.removeOrder(orderId, orderInfo))
  {
    orderInfo.getOrderListener()->onOrderCancel(OrderStatus(orderInfo.getOrder(),
                                                            OrderStatus::CANCELLED,
                                                            "Cancelled",
                                                            orderInfo.getQuantity()));
  }
  else
  {
    orderInfo.getOrderListener()->onOrderCancel(OrderStatus(std::shared_ptr<Order>(),
                                                            OrderStatus::ERRORED,
                                                            "Order not found",
                                                            Quantity(0)));
  }
}
