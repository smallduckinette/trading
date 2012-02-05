#ifndef __LIBTRADING_NUMBER_H__
#define __LIBTRADING_NUMBER_H__

namespace trading
{
  template<typename D, typename T>
  class Number : boost::operators<Number<D, T> >
  {
  public:
    Number();
    Number(const Number & n);
    Number(const T & value);
    
    bool operator<(const Number & n) const;
    bool operator==(const Number & n) const;
    Number & operator+=(const Number & n);
    Number & operator-=(const Number & n);
    Number & operator*=(const Number & n);
    Number & operator/=(const Number & n);
    Number & operator%=(const Number & n);
    Number & operator|=(const Number & n);
    Number & operator&=(const Number & n);
    Number & operator^=(const Number & n);
    Number & operator++();
    Number & operator--();
  
    T getValue() const;
    void setValue(const T & value);

    Number & operator=(const Number & n);

  private:
    T m_value;
  };

  template<typename D, typename T>
  Number<D, T>::Number():
    m_value()
  {
  }

  template<typename D, typename T>
  Number<D, T>::Number(const Number & n):
    m_value(n.m_value)
  {
  }

  template<typename D, typename T>
  Number<D, T>::Number(const T & value):
    m_value(value)
  {
  }

  template<typename D, typename T>
  bool Number<D, T>::operator<(const Number & n) const
  {
    return m_value < n.m_value;
  }

  template<typename D, typename T>
  bool Number<D, T>::operator==(const Number & n) const
  {
    return m_value == n.m_value;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator+=(const Number & n)  
  {
    m_value += n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator-=(const Number & n)
  {
    m_value -= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator*=(const Number & n)
  {
    m_value *= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator/=(const Number & n)
  {
    m_value /= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator%=(const Number & n)
  {
    m_value %= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator|=(const Number & n)
  {
    m_value |= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator&=(const Number & n)
  {
    m_value &= n.m_value;
    return *this;  
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator^=(const Number & n)
  {
    m_value ^= n.m_value;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator++()
  {
    m_value++;
    return *this;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator--()
  {
    m_value--;
    return *this;
  }

  template<typename D, typename T>
  T Number<D, T>::getValue() const
  {
    return m_value;
  }

  template<typename D, typename T>
  void Number<D, T>::setValue(const T & value)
  {
    m_value = value;
  }

  template<typename D, typename T>
  Number<D, T> & Number<D, T>::operator=(const Number & n)
  {
    m_value = n.m_value;
    return *this;
  }

  template<typename D, typename T>
  std::ostream & operator<<(std::ostream & os, const Number<D, T> & n)
  {
    return os << n.getValue();
  }
}

#endif
