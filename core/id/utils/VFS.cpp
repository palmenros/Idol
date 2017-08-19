#include "VFS.h"
#include "FileUtils.h"

namespace Idol
{

std::map<String, String> VFS::volumes;

void VFS::addVolume(String volume, String path)
{

	while (volume.length() > 0 && volume.front() == '/')
	{
		volume.erase(0, 1);
	}

	if (path.back() != '/')
	{
		path.push_back('/');
	}

	if (volume == "")
	{
		//Set default volume
		VFS::volumes[""] = path;
		return;
	}

	volume.insert(0, "//");

	if(volume.back() != '/')
	{
		volume.push_back('/');
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
		if(volume == "")
		{
			continue;
		}

		const String& virtualPath = obj.second;

		size_t size = volume.length();
		if(volume == path.substr(0, size))
		{
			return virtualPath + path.substr(size);
		}
	}

	//Check for default volume
	if(path.length() >= 2)
	{
		if(path[0] == '/' && path[1] == '/')
		{
			//Check if default volume is set
			std::map<String, String>::iterator it = VFS::volumes.find("");
			if(it != VFS::volumes.end())
			{
				return it->second + path.substr(2);
			}
		}
	}

	return path;
}

}