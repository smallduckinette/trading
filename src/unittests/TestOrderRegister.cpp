#include <boost/test/auto_unit_test.hpp>
#include "trading/OrderRegister.h"

#include "Utils.h"

namespace
{
  void addBid(trading::OrderRegister & orderRegister,
              const trading::OrderId & orderId,
              const trading::Price & price,
              const trading::Quantity & quantity)
  {
    orderRegister.insertOrder(createBid(orderId, price, quantity));
  }

  void addOffer(trading::OrderRegister & orderRegister,
                const trading::OrderId & orderId,
                const trading::Price & price,
                const trading::Quantity & quantity)
  {
    orderRegister.insertOrder(createOffer(orderId, price, quantity));
  }
}

BOOST_AUTO_TEST_CASE(TestOrderRegisterInsert)
{
  trading::OrderRegister orderRegister;
  trading::OrderInfo orderInfo;

  BOOST_CHECK(!orderRegister.getBestBid(orderInfo));
  BOOST_CHECK(!orderRegister.getBestOffer(orderInfo));
  
  addBid(orderRegister, 1, trading::Price(13), trading::Quantity(10));
  addBid(orderRegister, 2, trading::Price(14), trading::Quantity(10));
  addBid(orderRegister, 3, trading::Price(15), trading::Quantity(10));

  BOOST_CHECK(orderRegister.getBestBid(orderInfo));
  BOOST_CHECK_EQUAL(trading::OrderId(3), orderInfo.getOrder()->getOrderId());
  BOOST_CHECK(!orderRegister.getBestOffer(orderInfo));
  

  addOffer(orderRegister, 4, trading::Price(16), trading::Quantity(10));
  addOffer(orderRegister, 5, trading::Price(17), trading::Quantity(10));
  addOffer(orderRegister, 6, trading::Price(18), trading::Quantity(10));

  BOOST_CHECK(orderRegister.getBestBid(orderInfo));
  BOOST_CHECK_EQUAL(trading::OrderId(3), orderInfo.getOrder()->getOrderId());
  BOOST_CHECK(orderRegister.getBestOffer(orderInfo));
  BOOST_CHECK_EQUAL(trading::OrderId(4), orderInfo.getOrder()->getOrderId());
  
  BOOST_CHECK(orderRegister.removeOrder(trading::OrderId(3), orderInfo));
  BOOST_CHECK(!orderRegister.removeOrder(trading::OrderId(3), orderInfo));
  
  BOOST_CHECK(orderRegister.getBestBid(orderInfo));
  BOOST_CHECK_EQUAL(trading::OrderId(2), orderInfo.getOrder()->getOrderId());
  BOOST_CHECK(orderRegister.getBestOffer(orderInfo));
  BOOST_CHECK_EQUAL(trading::OrderId(4), orderInfo.getOrder()->getOrderId());
}
