#include "Sandbox.h"

using namespace Idol;

int main()
{
	//Setup VFS

	VFS::addVolume("shaders", "B:/Users/Pedro/Documents/Visual Studio 2017/Projects/LabGL/LabGL/shaders");

	//Run sandbox
	Sandbox app;
	app.run();


	return 0;
}
