#ifndef HALFTONE_MATRIX_H_
#define HALFTONE_MATRIX_H_
namespace halftone {

template <typename T>
class Vector {
  int count_;
  T* ptr_;

 public:
  Vector();
  Vector(int count) : count_(count);
  ~Vector();
  T& operator[](int num);
};

template <typename T>
class Matrix {
  int rows_;
  int columns_;
  Vector<T>* ptr_;

 public:
  Matrix();
  Matrix(int rows, int columns) : rows_(rows), columns_(columns);
  ~Matrix();
  Vector<T>& operator[](int num)
};
}  // namespace halftone
#endif