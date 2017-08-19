#pragma once
#include "Idol.h"
#include <map>

namespace Idol
{
class VFS
{
private:

	/*
	 * Map <Volume, Path>
	 * Map representing the virtual file system
	 */
	static std::map<String, String> volumes;

public:

	/*
	 * Get file from virtual file system
	 * Resolves to physical path
	 */
	static String getTextFile(const String& path);

	/*
	 * Resolve to physical path
	 * @return Physical path
	 */
	static String resolve(const String& path);

	/*
	 * Create a virtual volume pointing to a physical folder
	 * @param volume Virtual volume name
	 * @param path Physical path
	 */
	static void addVolume(String volume, String path);

};
}


