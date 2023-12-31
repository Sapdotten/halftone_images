#ifndef INCLUDE_HALFTONE_HALFTONE_H_
#define INCLUDE_HALFTONE_HALFTONE_H_
#include<matrix.cpp>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <limits>
#include <iostream>
namespace halftone {

 template<typename T>
class Image {
  int width_;
  int height_;
  Matrix<T> content_;

 public:
  friend std::ostream& operator<<(std::ostream& out, const Image<T> pers);
  Image();
  Image(int height, int width, bool random_filling);
  Image(const Image<T> &other);
  ~Image() = default;
  Image<T> &operator=(const Image<T> &other);
  T& operator()(int row, int column);
  T operator()(int row, int column) const;
  Image<T> operator*(const Image<T> &other) const;
  Image<T> operator+(const Image<T> &other) const;
  Image<T> operator*(const T num) const;
  Image<T> operator+(const T num) const;
  Image<T> operator!() const;
  bool operator==(const Image<T>& other) const;
  bool operator!=(const Image<T>& other) const;
  double FillFactor() const;
  void Swap(Image<T> &other);
  template <typename P>
  T isIn(const P value) const;

 private:
  void RandomFilling();
 };



template <typename T>
Image<T>::Image() {
  this->width_ = 0;
  this->height_ = 0;
  this->content_ = Matrix<T>();
 }

template <typename T>
Image<T>::Image(int height, int width, bool random_filling) {
   this->width_ = width;
   this->height_ = height;
   this->content_ = Matrix<T>(height, width);
   if (random_filling) {
     std::srand((unsigned int)std::time(NULL));
     this->RandomFilling();
   }
 }

void Image<bool>::RandomFilling() {
   for (int i = 0; i < this->height_; i++) {
     for (int j = 0; j < this->width_; j++) {
       (*this)(i, j) = rand() % 2;
     }
   }
 }

void Image<char>::RandomFilling() {
   for (int i = 0; i < this->height_; i++) {
     for (int j = 0; j < this->width_; j++) {
       (*this)(i, j) = -127 + rand() % 255;
     }
   }
 }

void Image<float>::RandomFilling() {
   for (int i = 0; i < this->height_; i++) {
     for (int j = 0; j < this->width_; j++) {
       (*this)(i, j) = -99 + (float)(rand()) / RAND_MAX * 99;
     }
   }
 }

void Image<short>::RandomFilling() {
   for (int i = 0; i < this->height_; i++) {
     for (int j = 0; j < this->width_; j++) {
       (*this)(i, j) = -99 + (rand()) % 200;
     }
   }
}

template <typename T>
Image<T>::Image(const Image<T>& other) {
  this->width_ = other.width_;
  this->height_ = other.height_;
  this->content_ = other.content_;
}

template <typename T>
 void Image<T>::Swap(Image<T> &other) {
  std::swap(this->width_, other.width_);
  std::swap(this->height_, other.height_);
  this->content_.Swap(other.content_);
}

template <typename T>
Image<T>& Image<T>::operator=(const Image<T> &other) {
  Image copy(other);
  this->Swap(copy);
  return *this;
}

template <typename T>
T& Image<T>::operator()(int row, int column) {
  return (this->content_)[row][column];
}

template <typename T>
T Image<T>::operator()(int row, int column) const{
  return (this->content_)[row][column];
}
template <typename T>
Image<T> Image<T>::operator*(const Image<T>& other) const {
  if (this->height_ != other.height_ || this->width_ != other.width_) {
    throw std::invalid_argument("Images have different sizes");
  }
  Image<T> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = ((*this)(i, j) * other(i, j));
      if (res > std::numeric_limits<T>::max())
        result(i, j) = std::numeric_limits<T>::max();
      else if (res < std::numeric_limits<T>::min())
        result(i, j) = std::numeric_limits<T>::min();
      else
        result(i, j) = (T)(res);
    }
  }
}



Image<bool> Image<bool>::operator+(const Image<bool>& other) const {
  if (this->height_ != other.height_ || this->width_ != other.width_) {
    throw std::invalid_argument("Images have different sizes");
  }
  Image<bool> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = (bool)((*this)(i, j) + other(i, j));
    }
  }
  return result;
}

Image<short> Image<short>::operator+(const Image<short>& other) const {
  if (this->height_ != other.height_ || this->width_ != other.width_) {
    throw std::invalid_argument("Images have different sizes");
  }
  Image<short> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = (*this)(i, j) + other(i, j);
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<float> Image<float>::operator+(const Image<float>& other) const {
  if (this->height_ != other.height_ || this->width_ != other.width_) {
    throw std::invalid_argument("Images have different sizes");
  }
  Image<float> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      double res = (*this)(i, j) + other(i, j);
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<char> Image<char>::operator+(const Image<char>& other) const {
  if (this->height_ != other.height_ || this->width_ != other.width_) {
    throw std::invalid_argument("Images have different sizes");
  }
  Image<char> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      short res = (*this)(i, j) + other(i, j);
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<short> Image<short>::operator*(const short num) const {
  Image<short> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = (*this)(i, j) * num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<float> Image<float>::operator*(const float num) const {
  Image<float> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      double res = (*this)(i, j) * num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<char> Image<char>::operator*(const char num) const {
  Image<char> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = (*this)(i, j) * num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

Image<bool> Image<bool>::operator*(const bool num) const {
  Image<bool> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = (*this)(i, j) * num;
    }
  }
  return result;
}


Image<bool> Image<bool>::operator+(const bool num) const {
  Image<bool> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = ((*this)(i, j) + num);
    }
  }
  return result;
}


Image<short> Image<short>::operator+(const short num) const {
  Image<short> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = (*this)(i, j) + num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}


Image<float> Image<float>::operator+(const float num) const {
  Image<float> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      double res = (*this)(i, j) + num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}


Image<char> Image<char>::operator+(const char num) const {
  Image<char> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      int res = (*this)(i, j) + num;
      result(i, j) = this->isIn(res);
    }
  }
  return result;
}

template <typename T>
Image<T> Image<T>::operator!() const {
  Image<T> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = (T)((*this)(i, j)) * (-1);
    }
  }
  return result;
}

Image<char> Image<char>::operator!() const {
  Image<char> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = (char)((*this)(i, j)) * (-1);
    }
  }
  return result;
}


Image<bool> Image<bool>::operator!() const {
  Image<bool> result(this->height_, this->width_, false);
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      result(i, j) = !(*this)(i, j);
    }
  }
  return result;
}

template <typename T>
double Image<T>::FillFactor() const {
  T sum = 0;
  for (int i = 0; i < this->height_; i++) {
    for (int j = 0; j < this->width_; j++) {
      sum += (*this)(i, j);
    }
  }
  return sum / (double)(this->width_ * this->height_) *
         std::numeric_limits<T>::max();
}




std::ostream& operator<<(std::ostream& out, const Image<char> img) {
  for (int i = 0; i < img.height_; i++) {
    for (int j = 0; j < img.width_; j++) {
      if (img(i, j) == char(127) ||
          (img(i, j) <= char(31) && img(i, j) >= char(0))) {
        out << ' ' <<' ';
      } else
        out << img(i, j) <<' ';
    }
    out << std::endl;
  }
  return out;
}


std::ostream& operator<<(std::ostream& out, const Image<short> img) {
  for (int i = 0; i < img.height_; i++) {
    for (int j = 0; j < img.width_; j++) {
      out << img(i, j) <<' ';
    }
    out << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Image<float> img) {
  for (int i = 0; i < img.height_; i++) {
    for (int j = 0; j < img.width_; j++) {
      out << img(i, j) <<' ';
    }
    out << std::endl;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Image<bool> img) {
  for (int i = 0; i < img.height_; i++) {
    for (int j = 0; j < img.width_; j++) {
      out << img(i, j) << ' ';
    }
    out << std::endl;
  }
  return out;
}

template <typename T>
bool Image<T>::operator==(const Image<T>& other) const {
  return (this->content_ == other.content_);
}

template <typename T>
bool Image<T>::operator!=(const Image<T>& other) const {
  return (this->content_ != other.content_);
}

template <typename T> 
template<typename P>
T Image<T>::isIn(const P value) const {
  return (value > std::numeric_limits<T>::max())
      ? (std::numeric_limits<T>::max())
      : ((value < std::numeric_limits<T>::min())
             ? (std::numeric_limits<T>::min())
             : (value));
}

}//namespace halftone
#endif