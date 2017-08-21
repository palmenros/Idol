#pragma once

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <sstream>

namespace math = glm;

template<class T, math::precision P>
std::ostream& operator<<(std::ostream& out, const math::tmat4x4<T, P>& mat)
{
	out << "mat4: " << std::endl;
	
	uint max = 0;
	uint lengths[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::stringstream ss;
			ss << mat[j][i];

			lengths[j * 4 + i] = ss.str().length();
			if(max < lengths[j*4 + i])
			{
				max = lengths[j * 4 + i];
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		out << "[ ";
		for (int j = 0; j < 4; j++)
		{
			//find out padding
			uint padding = max - lengths[j * 4 + i];

			out << String(padding, ' ') << mat[j][i] << " ";
		}
		out << "]" << std::endl;
	}
	return out;
}

template <class T, math::precision P>
std::ostream& operator<<(std::ostream& out, const glm::tvec2<T, P> & vec)
{
	out << "vec2(" << vec.x << ", " << vec.y << ")" << std::endl;
	return out;
}

template <class T, math::precision P>
std::ostream& operator<<(std::ostream& out, const glm::tvec3<T, P> & vec)
{
	out << "vec3(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << std::endl;
	return out;
}

template <class T, math::precision P>
std::ostream& operator<<(std::ostream& out, const glm::tvec4<T, P> & vec)
{
	out << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")" << std::endl;
	return out;
}