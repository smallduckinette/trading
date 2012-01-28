#include "Market.h"


trading::Market::Market(const std::string & description):
  _description(description)
{
}

void trading::Market::registerListing(std::unique_ptr<Listing> listing)
{
  InstrumentId instrumentId;
  _listingMap.insert(std::make_pair(instrumentId, std::move(listing)));
}

void trading::Market::addOrder(const Order & order)
{
  ListingMapT::iterator it = _listingMap.find(order.getInstrumentId());
  if(it != _listingMap.end())
  {
    it->second->addOrder(order);
  }
}

void trading::Market::updateOrder(const OrderId & orderId, 
                                  const Order & order)
{
  ListingMapT::iterator it = _listingMap.find(order.getInstrumentId());
  if(it != _listingMap.end())
  {
    it->second->updateOrder(orderId, order);
  }
}

void trading::Market::cancelOrder(const OrderId & orderId,
                                  const InstrumentId & instrumentId)
{
  ListingMapT::iterator it = _listingMap.find(instrumentId);
  if(it != _listingMap.end())
  {
    it->second->cancelOrder(orderId);
  }
}
