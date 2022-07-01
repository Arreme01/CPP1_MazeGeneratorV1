#define OLC_PGE_APPLICATION
#include "LaberinthApp.h"

#define LAB_WIDTH 200
#define LAB_HEIGHT 120
int main() 
{
	LaberinthApp app(LAB_WIDTH, LAB_HEIGHT);
	if (app.Construct(LAB_WIDTH, LAB_HEIGHT, 5, 5))
	{
		app.Start();
	}
	return 0;
}