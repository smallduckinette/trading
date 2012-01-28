#ifndef __LIBTRADING_MARKET_H__
#define __LIBTRADING_MARKET_H__

#include <string>
#include <memory>
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

    // Thread unsafe - Only to be called during initialisation
    void registerListing(std::unique_ptr<Listing> listing);
    
    void addOrder(const Order & order);
    void updateOrder(const OrderId & orderId, 
                     const Order & order);
    void cancelOrder(const OrderId & orderId,
                     const InstrumentId & instrumentId);
    
  private:
    std::string _description;
    
    typedef std::unordered_map<InstrumentId, std::unique_ptr<Listing> > ListingMapT;
    ListingMapT _listingMap;
  };
}

#endif
