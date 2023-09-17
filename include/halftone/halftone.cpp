#ifndef INCLUDE_HALFTONE_HALFTONE_H_
#define INCLUDE_HALFTONE_HALFTONE_H_
namespace halftone {
 template<typename T>
class Image {
  int width_;
  int heigth_;
  Matrix<T> content_;

 public:
  Image();
  Image(int width, int height, bool random_filling)
      : width_(width), height_(height);
  Image(const Image<T> &other);
  ~Image() = default;
  Image<T> &operator=(const Image<T> &other);
  T& operator()(int row, int column);
  Image<T> operator*(const Image<T> &other) const;
  Image<T> operator+(const Image<T> &other) const;
  Image<T> operator*(const T) const;
  Image<T> operator+(const T) const;
  Image<T> operator!() const;
  int FillFactor() const;
 };
}//namespace halftone
#endif