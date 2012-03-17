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
    orderInfo.onInsert();
    
    // Try to match the opposite price
    OrderInfo aggressor(orderInfo);
    OrderInfo initiator;

    while(aggressor.getOpenQuantity() > Quantity(0) &&
          _orderRegister.getBest(Side::reverse(aggressor.getOrder()->getSide()), initiator) &&
          isMatching(aggressor, initiator))
    {
      match(aggressor, initiator);
      if(initiator.getOpenQuantity() == Quantity(0))
      {
        _orderRegister.eraseOrder(initiator.getOrder()->getOrderId());
      }
      else
      {
        assert(initiator.getOpenQuantity() > Quantity(0));
        assert(aggressor.getOpenQuantity() == Quantity(0));
        _orderRegister.eraseOrder(initiator.getOrder()->getOrderId());
        _orderRegister.insertOrder(initiator);
        break;
      }
    }
    if(aggressor.getOpenQuantity() > Quantity(0))
    {
      _orderRegister.insertOrder(aggressor);
    }
  }
  else
  {
    orderInfo.onReject("InstrumentId mismatch");
  }
}

void trading::MatchingListing::doCancelOrder(const OrderId & orderId)
{
  OrderInfo orderInfo;
  if(_orderRegister.removeOrder(orderId, orderInfo))
  {
    orderInfo.onCancel();
  }
}

bool trading::MatchingListing::isMatching(const OrderInfo & aggressor, const OrderInfo & initiator) const
{
  assert(aggressor.getOrder()->getSide() != initiator.getOrder()->getSide());
  return((aggressor.getOrder()->getSide() == Side::BID && aggressor.getOrder()->getPrice() >= initiator.getOrder()->getPrice())
         ||(aggressor.getOrder()->getSide() == Side::OFFER && aggressor.getOrder()->getPrice() <= initiator.getOrder()->getPrice()));
}

void trading::MatchingListing::match(OrderInfo & aggressor, OrderInfo & initiator)
{
  assert(aggressor.getOrder()->getSide() != initiator.getOrder()->getSide());
  Quantity tradedQuantity = std::min(aggressor.getOpenQuantity(), initiator.getOpenQuantity());
  Price price = initiator.getOrder()->getPrice();
  aggressor.onTradeQuantity(tradedQuantity, price);
  initiator.onTradeQuantity(tradedQuantity, price);
}
