#include <boost/test/auto_unit_test.hpp>
#include "trading/OrderRegister.h"

namespace
{
  void addBid(trading::OrderRegister & orderRegister,
              const trading::OrderId & orderId,
              const trading::Price & price,
              const trading::Quantity & quantity)
  {
    orderRegister.insertOrder(std::make_shared<trading::Order>(orderId,
                                                               trading::InstrumentId(1),
                                                               trading::TraderId(1),
                                                               price,
                                                               quantity,
                                                               trading::Order::BID,
                                                               trading::TimePointT()));
  }

  void addOffer(trading::OrderRegister & orderRegister,
              const trading::OrderId & orderId,
              const trading::Price & price,
              const trading::Quantity & quantity)
  {
    orderRegister.insertOrder(std::make_shared<trading::Order>(orderId,
                                                               trading::InstrumentId(1),
                                                               trading::TraderId(1),
                                                               price,
                                                               quantity,
                                                               trading::Order::OFFER,
                                                               trading::TimePointT()));
  }
}

BOOST_AUTO_TEST_CASE(TestOrderRegisterInsert)
{
  trading::OrderRegister orderRegister;

  BOOST_CHECK(!orderRegister.getBestBid());
  BOOST_CHECK(!orderRegister.getBestOffer());
  
  addBid(orderRegister, 1, trading::Price(13), trading::Quantity(10));
  addBid(orderRegister, 2, trading::Price(14), trading::Quantity(10));
  addBid(orderRegister, 3, trading::Price(15), trading::Quantity(10));

  BOOST_CHECK_EQUAL(trading::OrderId(3), orderRegister.getBestBid()->getOrderId());
  BOOST_CHECK(!orderRegister.getBestOffer());
  

  addOffer(orderRegister, 4, trading::Price(16), trading::Quantity(10));
  addOffer(orderRegister, 5, trading::Price(17), trading::Quantity(10));
  addOffer(orderRegister, 6, trading::Price(18), trading::Quantity(10));

  BOOST_CHECK_EQUAL(trading::OrderId(3), orderRegister.getBestBid()->getOrderId());
  BOOST_CHECK_EQUAL(trading::OrderId(4), orderRegister.getBestOffer()->getOrderId());

  orderRegister.deleteOrder(trading::OrderId(3));
  
  BOOST_CHECK_EQUAL(trading::OrderId(2), orderRegister.getBestBid()->getOrderId());
  BOOST_CHECK_EQUAL(trading::OrderId(4), orderRegister.getBestOffer()->getOrderId());
}
