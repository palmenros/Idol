#include "Sandbox.h"
#include "Idol.h"

using namespace Idol;

int main()
{
	//Setup VFS
	VFS::addVolume("shaders", PROJECT_DIR("shaders"));
	VFS::addVolume("textures", PROJECT_DIR("media/textures"));

	//Run sandbox
	Sandbox app;
	app.run();

	return 0;
}
