#include "VFS.h"
#include "FileUtils.h"

namespace Idol
{

std::map<String, String> VFS::volumes;

void VFS::addVolume(String volume, String path)
{

	while(volume.front() == '/')
	{
		volume.erase(0, 1);
	}

	volume.insert(0, "//");

	if(volume.back() != '/')
	{
		volume.push_back('/');
	}

	if(path.back() != '/')
	{
		path.push_back('/');
	}

	VFS::volumes[volume] = path;
}

String VFS::getTextFile(const String &path)
{
	return FileUtils::readTextFile(VFS::resolve(path));
}
String VFS::resolve(const String &path)
{
	for(const std::pair<String, String>& obj : VFS::volumes)
	{
		const String& volume = obj.first;
		const String& virtualPath = obj.second;

		size_t size = volume.length();
		if(volume == path.substr(0, size))
		{
			return virtualPath + path.substr(size);
		}
	}

	return path;
}

}