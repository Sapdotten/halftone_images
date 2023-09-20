#ifndef INCLUDE_MATRIX_MATRIX_H_
#define INCLUDE_MATRIX_MATRIX_H_
#include <stdexcept>

const float epsilon = 0.0001f;
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
  bool operator==(const Vector<T>& other) const;
  bool operator!=(const Vector<T>& other) const;
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
  Vector<T> operator[](int num) const;
  void Swap(Matrix<T> &other);
  bool operator==(const Matrix<T>& other) const;
  bool operator!=(const Matrix<T>& other) const;
};

template <typename T>
Vector<T>::Vector() {
  this->ptr_ = nullptr;
  this->size_ = 0;
}

template <typename T>
Vector<T>::Vector(int size){
  this->size_ = size;
  this->ptr_ = new T[size]{0};
}

template <typename T>
Vector<T>::~Vector() {
  if (this->ptr_ != nullptr) {
    delete[] this->ptr_;
  }
  
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
  if (this->size_ == other.size_) {
    for (int i = 0; i < this->size_; i++) {
      if ((*this)[i] != other[i]) return false;
    }
    return true;
  }
  return false;
}

bool Vector<float>::operator==(const Vector<float>& other) const {
  if (this->size_ == other.size_) {
    for (int i = 0; i < this->size_; i++) {
      if (fabs((*this)[i] - other[i])<=epsilon) return false;
    }
    return true;
  }
  return false;
}


template <typename T>
bool Vector<T>::operator!=(const Vector<T>& other) const {
  return !((*this) == other);
}

template <typename T>
T& Vector<T>::operator[](int num) {
  if (num < 0 || num >= this->size_) {
    throw std::out_of_range("Index out of range");
  }
  return this->ptr_[num];
}

template <typename T>
T Vector<T>::operator[](int num) const {
  if (num < 0 || num >= this->size_) {
    throw std::out_of_range("Index out of range");
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
  this->ptr_ = nullptr;
  this->rows_ = 0;
  this->columns_ = 0;
}

template <typename T>
Matrix<T>::Matrix(int rows, int columns) {
  this->rows_ = rows;
  this->columns_ = columns;
  this->ptr_ = new Vector<T>[rows]();
  for (int i = 0; i < rows; i++) {
    ptr_[i] = Vector<T>(columns);
  }
}
template <typename T>
Matrix<T>::~Matrix() {
  if(this->ptr_ !=nullptr)
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
Vector<T> Matrix<T>::operator[](int num) const{
  if (num < 0 || num >= rows_) {
    throw std::out_of_range("");
  } else {
    return this->ptr_[num];
  }
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
  if (this->rows_ == other.rows_ && this->columns_ == other.columns_) {
    for (int i = 0; i < this->rows_; i++) {
      if ((*this)[i] != other[i]) return false;
    }
    return true;
  }
  return false;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
  return !((*this) == other);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
  this->rows_ = other.rows_;
  this->columns_ = other.columns_;
  this->ptr_ = new Vector<T>[other.rows_]();
  for (int i = 0; i < other.rows_; i++) {
    (*this)[i] = other[i];
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
  Matrix copy(other);
  this->Swap(copy);
  return *this;
}
}  // namespace halftone
#endif