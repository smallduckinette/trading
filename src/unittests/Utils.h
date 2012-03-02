#ifndef __UNITTESTS_UTILS_H__
#define __UNITTESTS_UTILS_H__

#include "trading/Order.h"
#include "trading/OrderInfo.h"

trading::OrderInfo createBid(const trading::OrderId & orderId,
                             const trading::Price & price,
                             const trading::Quantity & quantity,
                             const std::shared_ptr<trading::OrderListener> & orderListener = std::shared_ptr<trading::OrderListener>());
trading::OrderInfo createOffer(const trading::OrderId & orderId,
                               const trading::Price & price,
                               const trading::Quantity & quantity,
                               const std::shared_ptr<trading::OrderListener> & orderListener = std::shared_ptr<trading::OrderListener>());

#endif
