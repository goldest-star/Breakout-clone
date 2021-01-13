#include "BreakOut.h"

int main()
{
	BreakOut demo;
	if (demo.Construct(520, 480, 2, 2))
		demo.Start();
	return 0;
}
