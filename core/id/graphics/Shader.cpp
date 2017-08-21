#include "Shader.h"

namespace Idol {

Shader::Shader(const String& vertexPath, const String& fragmentPath) : vertexPath(vertexPath), fragmentPath(fragmentPath)
{
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

Shader* Shader::createFromFile(const String& vertexPath, const String& fragmentPath)
{
	Shader* shader = new Shader(vertexPath, fragmentPath);

	String vertexSource = VFS::readTextFile(vertexPath);
	String fragmentSource = VFS::readTextFile(fragmentPath);

	shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	const char* vertexStr = vertexSource.c_str();
	const char* fragmentStr = fragmentSource.c_str();

	glShaderSource(shader->vertexShader, 1, &vertexStr, nullptr);
	glShaderSource(shader->fragmentShader, 1, &fragmentStr, nullptr);

	return shader;
}

void Shader::compile()
{
	tryCompile(vertexPath, vertexShader);
	tryCompile(fragmentPath, fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	//Handle link errors

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if(!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		ERROR("\nFailed linking program:");
		ERROR(infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::tryCompile(const String& path, GLuint shader)
{
	//Compile shader
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if(!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		
		ERROR("\nFailed compiling shader '" + path + "':");
		ERROR(infoLog);
	}
}

void Shader::use() const
{
	glUseProgram(program);
}

void Shader::disuse() const
{
	glUseProgram(0);
}

uint Shader::resolveUniform(const String& name)
{
	std::map<String, uint>::iterator it = uniformCache.find(name);

	if(it != uniformCache.end())
	{
		//Uniform found
		return it->second;
	}
	
	//Cache miss, find out and add to cache

	uint location = glGetUniformLocation(program, name.c_str());
	uniformCache[name] = location;

	return location;
}

void Shader::setInt(const String& name, int32 value)
{
	setUniform1i(name, value);
}

void Shader::setFloat(const String& name, float value)
{
	setUniform1f(name, value);
}

void Shader::setVec2(const String& name, const math::vec2& vec)
{
	setUniform2f(name, vec);
}

void Shader::setVec3(const String& name, const math::vec3& vec)
{
	setUniform3f(name, vec);

}

void Shader::setVec4(const String& name, const math::vec4& vec)
{
	setUniform4f(name, vec);
}

void Shader::setMat4(const String& name, const math::mat4& mat)
{
	setUniformMat4(name, mat);
}

void Shader::setUniform1f(const String& name, float value)
{
	setUniform1f(resolveUniform(name), value);
}

void Shader::setUniform1fv(const String& name, float* value, size_t count)
{
	setUniform1fv(resolveUniform(name), value, count);
}

void Shader::setUniform1i(const String& name, int32 value)
{
	setUniform1i(resolveUniform(name), value);
}

void Shader::setUniform1iv(const String& name, int32* value, size_t count)
{
	setUniform1iv(resolveUniform(name), value, count);
}

void Shader::setUniform2f(const String& name, const math::vec2& vec)
{
	setUniform2f(resolveUniform(name), vec);
}

void Shader::setUniform3f(const String& name, const math::vec3& vec)
{
	setUniform3f(resolveUniform(name), vec);
}

void Shader::setUniform4f(const String& name, const math::vec4& vec)
{
	setUniform4f(resolveUniform(name), vec);
}

void Shader::setUniformMat4(const String& name, const math::mat4& mat)
{
	setUniformMat4(resolveUniform(name), mat);
}

void Shader::setUniform1f(uint location, float value)
{
	glUniform1f(location, value);
}

void Shader::setUniform1fv(uint location, float* value, size_t count)
{
	glUniform1fv(location, count, value);
}

void Shader::setUniform1i(uint location, int32 value)
{
	glUniform1i(location, value);
}

void Shader::setUniform1iv(uint location, int32* value, size_t count)
{
	glUniform1iv(location, count, value);
}

void Shader::setUniform2f(uint location, const math::vec2& vec)
{
	glUniform2f(location, vec.x, vec.y);
}

void Shader::setUniform3f(uint location, const math::vec3& vec)
{
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setUniform4f(uint location, const math::vec4& vec)
{
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniformMat4(uint location, const math::mat4& mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}
}
