#pragma once

#include "Idol.h"

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