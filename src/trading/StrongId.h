#ifndef __AIRSHIP_STRONGID_H__
#define __AIRSHIP_STRONGID_H__

#include <ostream>

template <typename D, typename T>
class StrongId
{
public:
  typedef D DiscriminantT;
  typedef T UnderlyingTypeT;
  
  StrongId()
  {
  }
      
  StrongId(const T & value):
    m_value(value)
  {
  }

  StrongId(const StrongId<D, T> & other):
    m_value(other.m_value)
  {
  }

  StrongId<D, T> & operator=(const StrongId<D, T> & other)
  {
    m_value = other.m_value;
    return *this;
  }

  bool operator==(const StrongId<D, T> & other) const
  {
    return (m_value == other.m_value);
  }

  bool operator!=(const StrongId<D, T> & other) const
  {
    return (m_value != other.m_value);
  }

  bool operator<(const StrongId<D, T> & other) const
  {
    return (m_value < other.m_value);
  }

  T getValue() const
  {
    return m_value;
  }

  StrongId<D, T> next() const
  {
    return StrongId<D, T>(m_value + 1);
  }

private:
  T m_value;
};

template<typename D, typename T>
size_t hash_value(const StrongId<D, T> & id)
{
  std::hash<T> hash;
  return hash(id.getValue());
}

template<typename D, typename T>
std::ostream & operator<<(std::ostream & os, const StrongId<D, T> & id)
{
  return os << id.getValue();
}

template<typename T>
class StrongIdGenerator;

template <typename D, typename T>
class StrongIdGenerator<StrongId<D, T> >
{
public:
  StrongIdGenerator(const T & init = T()):
    m_nextValue(init)
  {
  }
  
  StrongId<D, T> generate()
  {
    StrongId<D, T> value(m_nextValue);
    m_nextValue++;
    return value;
  }
  
private:
  T m_nextValue;
};

#endif
