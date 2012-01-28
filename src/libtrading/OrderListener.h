#ifndef __LIBTRADING_ORDERLISTENER_H__
#define __LIBTRADING_ORDERLISTENER_H__

namespace trading
{
  class OrderListener
  {
  public:
    virtual ~OrderListener();
    
    virtual void onOrderInsert(bool success) = 0;
    virtual void onOrderUpdat(bool success) = 0;
    virtual void onOrderCancel(bool success) = 0;
    virtual void onOrderStatus() = 0;
  };
}

#endif
