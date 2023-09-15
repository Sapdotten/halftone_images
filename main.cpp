#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#include <iostream>
using namespace std;

int main()
{
  _CrtDumpMemoryLeaks();
	return 0;
}
