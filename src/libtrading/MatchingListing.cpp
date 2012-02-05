#include "MatchingListing.h"



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

void trading::MatchingListing::addOrder(const Order & order,
                                        const std::shared_ptr<OrderListener> & orderListener)
{
  _strand.post(std::bind(&MatchingListing::doAddOrder,
                         shared_from_this(),
                         order,
                         orderListener));
}

void trading::MatchingListing::updateOrder(const OrderId & orderId, 
                                           const Order & order)
{
  _strand.post(std::bind(&MatchingListing::doUpdateOrder,
                         shared_from_this(),
                         orderId,
                         order));
}

void trading::MatchingListing::cancelOrder(const OrderId & orderId)
{
  _strand.post(std::bind(&MatchingListing::doCancelOrder,
                         shared_from_this(),
                         orderId));
}

void trading::MatchingListing::doAddOrder(const Order & order,
                                          const std::shared_ptr<OrderListener> & orderListener)
{
}

void trading::MatchingListing::doUpdateOrder(const OrderId & orderId,
                                             const Order & order)
{
}

void trading::MatchingListing::doCancelOrder(const OrderId & orderId)
{
}
