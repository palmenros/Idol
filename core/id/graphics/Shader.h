#pragma once
#include "Idol.h"
#include <map>

namespace Idol {

class Shader
{
private:
	GLuint fragmentShader;
	GLuint vertexShader;
	GLuint program;

	static void tryCompile(const String& path, GLuint shader);
	
	String vertexPath;
	String fragmentPath;

	Shader(const String& vertexPath, const String& fragmentPath);

	std::map<String, uint> uniformCache;

public:

	virtual ~Shader();

	static Shader* createFromFile(const String& vertexPath, const String& fragmentPath);

	void compile();
	void use() const;
	void disuse() const;

	uint resolveUniform(const String& name);

	//uniforms


	void setInt(const String& name, int32 value);
	void setFloat(const String& name, float value);
	void setVec2(const String& name, const math::vec2& vec);
	void setVec3(const String& name, const math::vec3& vec);
	void setVec4(const String& name, const math::vec4& vec);
	void setMat4(const String& name, const math::mat4& mat);

	void setUniform1f(const String& name, float value);
	void setUniform1fv(const String& name, float* value, size_t count);
	void setUniform1i(const String& name, int32 value);
	void setUniform1iv(const String& name, int32* value, size_t count);
	void setUniform2f(const String& name, const math::vec2& vec);
	void setUniform3f(const String& name, const math::vec3& vec);
	void setUniform4f(const String& name, const math::vec4& vec);
	void setUniformMat4(const String& name, const math::mat4& mat);

	void setUniform1f(uint location, float value);
	void setUniform1fv(uint location, float* value, size_t count);
	void setUniform1i(uint location, int32 value);
	void setUniform1iv(uint location, int32* value, size_t count);
	void setUniform2f(uint location, const math::vec2& vec);
	void setUniform3f(uint location, const math::vec3& vec);
	void setUniform4f(uint location, const math::vec4& vec);
	void setUniformMat4(uint location, const math::mat4& mat);

};

}