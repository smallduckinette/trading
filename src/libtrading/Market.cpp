#include "Market.h"


trading::Market::Market(const std::string & description):
  _description(description)
{
}

void trading::Market::registerListing(const std::shared_ptr<Listing> & listing)
{
  std::unique_lock<std::mutex> lock(_mutex);
  _listingMap.insert(std::make_pair(listing->getInstrumentId(), listing));
}

std::shared_ptr<trading::Listing> trading::Market::getListing(const InstrumentId & instrumentId)
{
  std::unique_lock<std::mutex> lock(_mutex);
  ListingMapT::const_iterator it = _listingMap.find(instrumentId);
  if(it != _listingMap.end())
  {
    return it->second;
  }
  else
  {
    throw std::runtime_error("Unknown listing");
  }
}
