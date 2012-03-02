#include <boost/test/auto_unit_test.hpp>
#include "trading/MatchingListing.h"

#include "trading/OrderListener.h"
#include "trading/OrderStatus.h"
#include "Utils.h"

namespace
{
  class TestableOrderListener : public trading::OrderListener
  {
  public:
    void onOrderStatus(const trading::OrderStatus & orderStatus)
    {
      _orderStatus.push_back(orderStatus);
    }
    
    std::vector<trading::OrderStatus> _orderStatus;
  };
}

BOOST_AUTO_TEST_CASE(TestMatchingListingInsertRemove)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(1), orderListener->_orderStatus.size());
  BOOST_CHECK(trading::OrderStatus(trading::OrderId(1),
                                   trading::OrderStatus::ACCEPTED,
                                   "Accepted", 
                                   trading::Quantity(5),
                                   trading::Quantity(0),
                                   trading::Quantity(5)) ==
              orderListener->_orderStatus.at(0));

  matchingListing->cancelOrder(trading::OrderId(1));
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener->_orderStatus.size());
  BOOST_CHECK(trading::OrderStatus(trading::OrderId(1),
                                   trading::OrderStatus::CANCELLED,
                                   "Cancelled", 
                                   trading::Quantity(0),
                                   trading::Quantity(0),
                                   trading::Quantity(0)) ==
              orderListener->_orderStatus.at(1));  
}

BOOST_AUTO_TEST_CASE(TestMatchingListingBadRemove)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener(new TestableOrderListener);

  matchingListing->cancelOrder(trading::OrderId(1));
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(0), orderListener->_orderStatus.size());
}
