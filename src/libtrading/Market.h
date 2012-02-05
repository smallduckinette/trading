#ifndef __LIBTRADING_MARKET_H__
#define __LIBTRADING_MARKET_H__

#include <string>
#include <memory>
#include <thread>
#include <unordered_map>

#include "Instrument.h"
#include "Listing.h"

namespace trading
{
  class Listing;
  
  class Market 
  {
  public:
    Market(const std::string & description);
    
    void registerListing(const std::shared_ptr<Listing> & listing);
    std::shared_ptr<Listing> getListing(const InstrumentId & instrumentId);
    
  private:
    std::string _description;
    std::mutex _mutex;
    
    // Protected by the mutex
    typedef std::unordered_map<InstrumentId, std::shared_ptr<Listing> > ListingMapT;
    ListingMapT _listingMap;
  };
}

#endif
