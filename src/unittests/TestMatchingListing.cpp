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
                                   trading::Quantity(5),
                                   trading::Price(0)) ==
              orderListener->_orderStatus.at(0));

  matchingListing->cancelOrder(trading::OrderId(1));
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener->_orderStatus.size());
  BOOST_CHECK(trading::OrderStatus(trading::OrderId(1),
                                   trading::OrderStatus::CANCELLED,
                                   "Cancelled", 
                                   trading::Quantity(5),
                                   trading::Quantity(0),
                                   trading::Quantity(5),
                                   trading::Price(0)) ==
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

BOOST_AUTO_TEST_CASE(TestMatchingListingInsertNoTrade)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener));
  matchingListing->addOrder(createOffer(trading::OrderId(2),
                                        trading::Price(7),
                                        trading::Quantity(5),
                                        orderListener));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener->_orderStatus.size());
  BOOST_CHECK(trading::OrderStatus(trading::OrderId(1),
                                   trading::OrderStatus::ACCEPTED,
                                   "Accepted", 
                                   trading::Quantity(5),
                                   trading::Quantity(0),
                                   trading::Quantity(5),
                                   trading::Price(0)) ==
              orderListener->_orderStatus.at(0));
  BOOST_CHECK(trading::OrderStatus(trading::OrderId(2),
                                   trading::OrderStatus::ACCEPTED,
                                   "Accepted", 
                                   trading::Quantity(5),
                                   trading::Quantity(0),
                                   trading::Quantity(5),
                                   trading::Price(0)) ==
              orderListener->_orderStatus.at(1));
}

BOOST_AUTO_TEST_CASE(TestMatchingListingInsertPartialAggressor)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener1(new TestableOrderListener);
  std::shared_ptr<TestableOrderListener> orderListener2(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createOffer(trading::OrderId(2),
                                        trading::Price(3),
                                        trading::Quantity(12),
                                        orderListener2));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(0), orderListener2->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(2), orderListener2->_orderStatus.size());
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Price(25)),
                    orderListener1->_orderStatus.at(1));
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(12),
                                         trading::Quantity(0),
                                         trading::Quantity(12),
                                         trading::Price(0)),
                    orderListener2->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::PARTIAL_FILL,
                                         "Partially filled", 
                                         trading::Quantity(12),
                                         trading::Quantity(5),
                                         trading::Quantity(7),
                                         trading::Price(25)),
                    orderListener2->_orderStatus.at(1));
}

BOOST_AUTO_TEST_CASE(TestMatchingListingInsertPartialInitiator)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener1(new TestableOrderListener);
  std::shared_ptr<TestableOrderListener> orderListener2(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createOffer(trading::OrderId(2),
                                        trading::Price(3),
                                        trading::Quantity(3),
                                        orderListener2));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(0), orderListener2->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(2), orderListener2->_orderStatus.size());
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::PARTIAL_FILL,
                                         "Partially filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(3),
                                         trading::Quantity(2),
                                         trading::Price(15)),
                    orderListener1->_orderStatus.at(1));
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(3),
                                         trading::Quantity(0),
                                         trading::Quantity(3),
                                         trading::Price(0)),
                    orderListener2->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(3),
                                         trading::Quantity(3),
                                         trading::Quantity(0),
                                         trading::Price(15)),
                    orderListener2->_orderStatus.at(1));
}

BOOST_AUTO_TEST_CASE(TestMatchingListingFullMatch)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener1(new TestableOrderListener);
  std::shared_ptr<TestableOrderListener> orderListener2(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createOffer(trading::OrderId(2),
                                        trading::Price(5),
                                        trading::Quantity(5),
                                        orderListener2));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(0), orderListener2->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(2), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(2), orderListener2->_orderStatus.size());
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Price(25)),
                    orderListener1->_orderStatus.at(1));
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener2->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Price(25)),
                    orderListener2->_orderStatus.at(1));
}

BOOST_AUTO_TEST_CASE(TestMatchingListingMultiMatch)
{
  boost::asio::io_service io_service;
  trading::InstrumentId instrumentId(1);
  std::shared_ptr<trading::MatchingListing> matchingListing(new trading::MatchingListing(io_service, instrumentId));
  std::shared_ptr<TestableOrderListener> orderListener1(new TestableOrderListener);
  std::shared_ptr<TestableOrderListener> orderListener2(new TestableOrderListener);
  
  matchingListing->addOrder(createBid(trading::OrderId(1),
                                      trading::Price(5),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createBid(trading::OrderId(2),
                                      trading::Price(4),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createBid(trading::OrderId(3),
                                      trading::Price(3),
                                      trading::Quantity(5),
                                      orderListener1));
  matchingListing->addOrder(createOffer(trading::OrderId(4),
                                        trading::Price(3),
                                        trading::Quantity(12),
                                        orderListener2));
  
  BOOST_CHECK_EQUAL(size_t(0), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(0), orderListener2->_orderStatus.size());
  io_service.run();
  io_service.reset();
  BOOST_CHECK_EQUAL(size_t(6), orderListener1->_orderStatus.size());
  BOOST_CHECK_EQUAL(size_t(4), orderListener2->_orderStatus.size());
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(1));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(3),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Quantity(5),
                                         trading::Price(0)),
                    orderListener1->_orderStatus.at(2));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(1),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Price(25)),
                    orderListener1->_orderStatus.at(3));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(2),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(5),
                                         trading::Quantity(0),
                                         trading::Price(20)),
                    orderListener1->_orderStatus.at(4));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(3),
                                         trading::OrderStatus::PARTIAL_FILL,
                                         "Partially filled", 
                                         trading::Quantity(5),
                                         trading::Quantity(2),
                                         trading::Quantity(3),
                                         trading::Price(6)),
                    orderListener1->_orderStatus.at(5));
  
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(4),
                                         trading::OrderStatus::ACCEPTED,
                                         "Accepted", 
                                         trading::Quantity(12),
                                         trading::Quantity(0),
                                         trading::Quantity(12),
                                         trading::Price(0)),
                    orderListener2->_orderStatus.at(0));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(4),
                                         trading::OrderStatus::PARTIAL_FILL,
                                         "Partially filled", 
                                         trading::Quantity(12),
                                         trading::Quantity(5),
                                         trading::Quantity(7),
                                         trading::Price(25)),
                    orderListener2->_orderStatus.at(1));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(4),
                                         trading::OrderStatus::PARTIAL_FILL,
                                         "Partially filled", 
                                         trading::Quantity(12),
                                         trading::Quantity(10),
                                         trading::Quantity(2),
                                         trading::Price(45)),
                    orderListener2->_orderStatus.at(2));
  BOOST_CHECK_EQUAL(trading::OrderStatus(trading::OrderId(4),
                                         trading::OrderStatus::FILL,
                                         "Filled", 
                                         trading::Quantity(12),
                                         trading::Quantity(12),
                                         trading::Quantity(0),
                                         trading::Price(51)),
                    orderListener2->_orderStatus.at(3));
}
