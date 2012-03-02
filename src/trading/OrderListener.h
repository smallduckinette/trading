#ifndef __LIBTRADING_ORDERLISTENER_H__
#define __LIBTRADING_ORDERLISTENER_H__

namespace trading
{
  class OrderStatus;

  class OrderListener
  {
  public:
    virtual ~OrderListener();
    
    virtual void onOrderStatus(const OrderStatus & orderStatus) = 0;
  };
}

#endif
