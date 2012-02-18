#ifndef __LIBTRADING_ORDERREGISTER_H__
#define __LIBTRADING_ORDERREGISTER_H__

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>

#include "Order.h"
#include "OrderInfo.h"

namespace trading
{  
  class OrderRegister
  {
  public:
    void insertOrder(const OrderInfo & orderInfo);
    bool removeOrder(const OrderId & orderId, OrderInfo & orderInfo);
    
    bool getBestBid(OrderInfo & orderInfo) const;
    bool getBestOffer(OrderInfo & orderInfo) const;
    
  private:
    struct Item
    {
      Item(const OrderInfo & orderInfo);
      
      bool operator<(const Item & other) const;
      
      OrderId getOrderId() const;
      TraderId getTraderId() const;
      
      OrderInfo _orderInfo;
    };
    
    struct ByPrice {};
    struct ByOrder {};
    struct ByTrader {};
    
    typedef boost::multi_index_container<
      Item,
      boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<boost::multi_index::tag<ByPrice>, boost::multi_index::identity<Item> >,
        boost::multi_index::hashed_unique<boost::multi_index::tag<ByOrder>, boost::multi_index::const_mem_fun<Item, OrderId, &Item::getOrderId> >,
        boost::multi_index::ordered_non_unique<boost::multi_index::tag<ByTrader>, boost::multi_index::const_mem_fun<Item, TraderId, &Item::getTraderId> >
        > 
      > ItemContainerT;

    ItemContainerT _orders;
  };
}

#endif
