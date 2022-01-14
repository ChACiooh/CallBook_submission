#include "Handler.h"

int main()
{
	Handler myHandle;
	while (true)
	{
		if (!myHandle.Handling())	break;
	}
	cout << "exited" << endl;
	return 0;
}