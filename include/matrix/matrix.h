#ifndef INCLUDE_MATRIX_MATRIX_H_
#define INCLUDE_MATRIX_MATRIX_H_
namespace halftone {

template <typename T>
class Vector {
  int size_;
  T* ptr_;
  
 public:
  Vector();
  Vector(int size) : size_(size);
  Vector(const Vector<T>& other);
  Vector<T>& operator=(const Vector<T> other);
  void Swap(Vector<T>& other);

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
  Matrix(const Matrix<T> &other);
  Matrix<T>& operator=(const Matrix<T> other);
  ~Matrix();
  Vector<T>& operator[](int num);
  void Swap(Matrix<T> &other);
};
}  // namespace halftone
#endif