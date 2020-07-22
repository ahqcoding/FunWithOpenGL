#pragma once
#include <GL/glew.h>
#include <string>
#include <map>
#include <glm/glm.hpp>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	// Make it non-copyable.
	GLSLProgram(const GLSLProgram&) = delete;
	GLSLProgram& operator=(const GLSLProgram&) = delete;

	void compileShader(const char* vs, const char* fs);
	void compileShader(const char* vs, const char* fs, const char* gs);
	void use();

	void bindAttribLocation(GLuint location, const char* name);
	void setUniform(const char* name, float x, float y, float z);
	void setUniform(const char* name, const glm::vec2& v);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat4& m);
	void setUniform(const char* name, const glm::mat3& m);
	void setUniform(const char* name, float val);
	void setUniform(const char* name, int val);
	void setUniform(const char* name, bool val);
	void setUniform(const char* name, GLuint val);

private:

	void checkCompileErrors(GLuint shader, std::string type);
	void findUniformLocations();
	GLuint handle;
	std::map<std::string, int> uniformLocations;
	inline GLint getUniformLocation(const char* name) {
		auto pos = uniformLocations.find(name);

		if (pos == uniformLocations.end()) {
			GLint loc = glGetUniformLocation(handle, name);
			uniformLocations[name] = loc;
			return loc;
		}

		return pos->second;
	}

};

