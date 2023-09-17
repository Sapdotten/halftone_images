#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#include <iostream>
#include <matrix/matrix.cpp>
using namespace std;
using namespace halftone;

void test() { Matrix<int> matrix(5, 1); }

int main()
{
  test();
  _CrtDumpMemoryLeaks();
	return 0;
}
