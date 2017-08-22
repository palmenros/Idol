#pragma once

#include "id/Types.h"

namespace Idol
{
class FileUtils
{
public:
	/*
		* Load file from path
		*/
	static String readTextFile(const String &path);
};
}