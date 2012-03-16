#include "Utils.h"

trading::OrderInfo createBid(const trading::OrderId & orderId,
                             const trading::Price & price,
                             const trading::Quantity & quantity,
                             const std::shared_ptr<trading::OrderListener> & orderListener)
{
  return trading::OrderInfo(std::make_shared<trading::Order>(orderId,
                                                             trading::InstrumentId(1),
                                                             trading::TraderId(1),
                                                             price,
                                                             quantity,
                                                             trading::Side::BID,
                                                             trading::TimePointT()),
                            orderListener);
}

trading::OrderInfo createOffer(const trading::OrderId & orderId,
                               const trading::Price & price,
                               const trading::Quantity & quantity,
                               const std::shared_ptr<trading::OrderListener> & orderListener)
{
  return trading::OrderInfo(std::make_shared<trading::Order>(orderId,
                                                             trading::InstrumentId(1),
                                                             trading::TraderId(1),
                                                             price,
                                                             quantity,
                                                             trading::Side::OFFER,
                                                             trading::TimePointT()),
                            orderListener);
}
