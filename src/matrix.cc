#include <matrix.h>
#include <stdexcept>
namespace halftone {
  template <typename T>
  Vector<T>::Vector(int count) : count_(count{
  this->ptr_ = new T[count];
  }
}//namespace halftone