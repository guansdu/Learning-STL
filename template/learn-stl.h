#ifndef LEARN_STL_H_
#define LEARN_STL_H_

template <class T>
class CalcT
{
public:
  T DoMulitply(T x, T y);
  T DoAdd(T x, T y);
};

template <class T>
T CalcT<T>::DoMulitply(T x, T y)
{
  return x * y;
}

template <class T>
T CalcT<T>::DoAdd(T x, T y)
{
  return x + y;
}

#endif
