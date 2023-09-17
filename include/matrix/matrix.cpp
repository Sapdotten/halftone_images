#ifndef INCLUDE_MATRIX_MATRIX_H_
#define INCLUDE_MATRIX_MATRIX_H_
#include <stdexcept>
#include <iostream>
namespace halftone {

template <typename T>
class Vector {
  int size_;
  T* ptr_;
  
 public:
  Vector();
  Vector(int size);
  Vector(const Vector<T>& other);
  Vector<T>& operator=(const Vector<T>& other);
  void Swap(Vector<T>& other);

  ~Vector();
  T& operator[](int num);
  T operator[](int num) const;
};

template <typename T>
class Matrix{
  int rows_;
  int columns_;
  Vector<T>* ptr_;

 public:
  Matrix();
  Matrix(int rows, int columns);
  Matrix(const Matrix<T> &other);
  Matrix<T>& operator=(const Matrix<T> &other);
  ~Matrix();
  Vector<T>& operator[](int num);
  void Swap(Matrix<T> &other);
};

template <typename T>
Vector<T>::Vector() {
  this->ptr_ = nullptr;
  this->size_ = 0;
}

template <typename T>
Vector<T>::Vector(int size) : size_(size) {
  this->ptr_ = new T[size];
}

template <typename T>
Vector<T>::~Vector() {
  if (this->ptr_ != nullptr) {
    delete[] this->ptr_;
  }
  
}

template <typename T>
T& Vector<T>::operator[](int num) {
  if (num < 0 || num >= size_) {
    throw std::out_of_range("");
  }
  return this->ptr_[num];
}
template <typename T>
T Vector<T>::operator[](int num) const {
  if (num < 0 || num >= size_) {
    throw std::out_of_range("");
  }
  return this->ptr_[num];
}

template <typename T>
void Vector<T>::Swap(Vector<T>& other) {
  std::swap(this->ptr_, other.ptr_);
  std::swap(this->size_, other.size_);
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) {
  this->size_ = other.size_;
  this->ptr_ = new T[size_];
  for (int i = 0; i < size_; i++) {
    this->ptr_[i] = other[i];
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other){
  Vector<T> other_copy(other);
  this->Swap(other_copy);
  return *this;
}

template <typename T>
Matrix<T>::Matrix() {
  this->rows_ = 0;
  this->columns_ = 0;
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns) : rows_(rows), columns_(columns) {
  this->ptr_ = new Vector<T>[rows](columns);
}
template <typename T>
Matrix<T>::~Matrix() {
  delete[] this->ptr_;
}

template <typename T>
Vector<T>& Matrix<T>::operator[](int num) {
  if (num < 0 || num >= rows_) {
    throw std::out_of_range("");
  } else {
    return this->ptr_[num];
  }
}
template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
  this->rows_ = other.rows_;
  this->columns_ = other.columns_;
  this->ptr_ = new Vector<T>[other.rows_]();
  for (int i = 0; i < other.rows_; i++) {
    this->ptr_[i] = other[i];
  }
}

template <typename T>
void Matrix<T>::Swap(Matrix<T>& other) {
  std::swap(this->ptr_, other.ptr_);
  std::swap(this->rows_, other.rows_);
  std::swap(this->columns_, other.columns_);
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T> &other) {
  this->Swap(other);
  return *this;
}
}  // namespace halftone
#endif