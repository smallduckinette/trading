#ifndef __LIBTRADING_ORDERLISTENER_H__
#define __LIBTRADING_ORDERLISTENER_H__

namespace trading
{
  class OrderStatus;

  class OrderListener
  {
  public:
    virtual ~OrderListener();
    
    virtual void onOrderInsert(const OrderStatus & orderStatus) = 0;
    virtual void onOrderUpdate(const OrderStatus & orderStatus) = 0;
    virtual void onOrderCancel(const OrderStatus & orderStatus) = 0;
  };
}

#endif
