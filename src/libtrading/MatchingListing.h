#ifndef __LIBTRADING_MATCHINGLISTING_H__
#define __LIBTRADING_MATCHINGLISTING_H__


#include <memory>
#include <boost/asio.hpp>

#include "Listing.h"

namespace trading
{
  class MatchingListing : public Listing,
                          public std::enable_shared_from_this<MatchingListing>
  {
  public:
    MatchingListing(boost::asio::io_service & io_service,
                    const InstrumentId & instrumentId);
    
    // Thread safe interface
    InstrumentId getInstrumentId() const;
    
    void addOrder(const Order & order,
                  const std::shared_ptr<OrderListener> & orderListener);
    void updateOrder(const OrderId & orderId, 
                     const Order & order);
    void cancelOrder(const OrderId & orderId);
    
  private:
    void doAddOrder(const Order & order,
                    const std::shared_ptr<OrderListener> & orderListener);
    void doUpdateOrder(const OrderId & orderId, 
                       const Order & order);
    void doCancelOrder(const OrderId & orderId); 
    
    boost::asio::io_service::strand _strand;
    InstrumentId _instrumentId;
  };
}

#endif
