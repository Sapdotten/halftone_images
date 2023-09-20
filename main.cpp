#include <iostream>
#include <halftone.cpp>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;
using namespace halftone;

void test() { 
  Image<bool> a(10, 10, true); 
  cout << a << endl; // or whatever
  std::chrono::duration<int, std::milli> timespan(1000);
  std::this_thread::sleep_for(timespan);
  Image<bool> b(10, 10, true);
  cout << b << endl << (a + b);

  
}

void ClearCin() {
  cin.clear();
  cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
}
void GetData(int& r, int& x, int& y) {
  cout << "Enter coordinates of center of circle" << endl;
  cout << "Enter x: ";
  cin >> x;
  cout << "Enter y: ";
  cin >> y;
  while (true) {
    cout << "\nEnter a radiues of circle: ";
    cin >> r;
    if (r < 0 || cin.fail()) {
      cout << "\n Wrong data! Radius can't be less then 0, try again: ";
      ClearCin();
    } else
     break;
  }
}

template <typename T>
T GetFillContent() {
  cout << "\nEnter a filling content for circle: ";
  T content = 0;
  cin >> content;
  return content;
}

bool IsRandomFiling() {
  cout << "\nDo you wanna fill the empty part of image with random content?\n"
       << "1 - yes\n"
       << "0 - no\n";
  int answer = 0;
  while (true) {
    cin >> answer;
    if (answer != 0 && answer != 1 || cin.fail()) {
      cout << "Wrong answer! Please, try again: ";
      ClearCin();
    } else
      break;
  }
  return answer;
}

int GetType() { 
 cout << "\nSelect a type of filling: \n"
       << "0: short int\n"
       << "1: float\n"
       << "2: bool\n"
       << "3: char\n";
  int type = 0;
 while (true) {
   cin >> type;
   if (type < 0 || type > 3 || cin.fail()) {
   cout << "Wrong answer! Please, try again: ";
   ClearCin();
 }
   else
     break;
 }
 return type;

}

template <typename T>
Image<T> GetMatrix(int r, int x, int y, T fill_content) {
  int width = (abs(x) + r+1);
  int height = (abs(y) + r+1);
  bool random_filling = IsRandomFiling();
  Image<T> circle(height*2+1, width*2+1, random_filling);
  for (int i = -height-1; i < height; i++) {
    for (int j = width; j >= -width; j--) {
      if ((pow(-i - y, 2) + pow(-j - x, 2)) <= (r * r)) {
        circle(i + height, width-j) = fill_content;
      }
    }
  }
  return circle;
}

int main()
{
  test();
  int r, y, x;
  GetData(r, x, y);
  int type = GetType();
  
  if (type == 0) {
    cout<< GetMatrix<short>(r, x, y, GetFillContent<short>());
  }
  else if(type == 1) {
    cout << GetMatrix<float>(r, x, y, GetFillContent<float>());
  } else if (type == 2) {
    cout << GetMatrix<bool>(r, x, y, GetFillContent<bool>());
  } else if (type == 3) {
    cout << GetMatrix<char>(r, x, y, GetFillContent<char>());
  }


	return 0;
}


