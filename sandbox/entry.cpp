#include "Sandbox.h"

using namespace Idol;

int main()
{
	//Setup VFS
	VFS::addVolume("shaders", PROJECT_DIR("shaders"));

	//Run sandbox
	Sandbox app;
	app.run();


	return 0;
}
