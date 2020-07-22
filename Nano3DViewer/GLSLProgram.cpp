#include "GLSLProgram.h"
#include <iostream>
#include <sstream>
#include <fstream>
GLSLProgram::GLSLProgram()
{
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::use()
{
    glUseProgram(this->handle);
}

void GLSLProgram::compileShader(const char* vsFile, const char* fsFile)
{
	std::string vertexCode;
	std::string fragmentCode;

	try {
        std::ifstream vertexShaderFile(vsFile);
        std::ifstream fragmentShaderFile(fsFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
	}

    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    this->handle = glCreateProgram();
    glAttachShader(this->handle, vertexShader);
    glAttachShader(this->handle, fragmentShader);
    glLinkProgram(this->handle);
    checkCompileErrors(this->handle, "PROGRAM");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    findUniformLocations();
}

void GLSLProgram::compileShader(const char* vsFile, const char* fsFile, const char* gsFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vertexShaderFile(vsFile);
        std::ifstream fragmentShaderFile(fsFile);
        std::ifstream geometryShaderFile(gsFile);
        std::stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        gShaderStream << geometryShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        geometryShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geometryCode = gShaderStream.str();
    }

    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    GLuint vertexShader, fragmentShader, geometryShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    checkCompileErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);
    checkCompileErrors(fragmentShader, "FRAGMENT");

    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &gShaderCode, NULL);
    glCompileShader(geometryShader);
    checkCompileErrors(geometryShader, "GEOMETRY");

    this->handle = glCreateProgram();
    glAttachShader(this->handle, vertexShader);
    glAttachShader(this->handle, fragmentShader);
    glAttachShader(this->handle, geometryShader);
    glLinkProgram(this->handle);
    checkCompileErrors(this->handle, "PROGRAM");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
    findUniformLocations();

}

void GLSLProgram::checkCompileErrors(GLuint object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

void GLSLProgram::findUniformLocations() {
    uniformLocations.clear();
    GLint numUniforms = 0;
    glGetProgramInterfaceiv(handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

    GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

    for (GLint i = 0; i < numUniforms; ++i) {
        GLint results[4];
        glGetProgramResourceiv(handle, GL_UNIFORM, i, 4, properties, 4, NULL, results);

        if (results[3] != -1) continue;  // Skip uniforms in blocks
        GLint nameBufSize = results[0] + 1;
        char* name = new char[nameBufSize];
        glGetProgramResourceName(handle, GL_UNIFORM, i, nameBufSize, NULL, name);
        uniformLocations[name] = results[2];
        delete[] name;
    }
}


void GLSLProgram::setUniform(const char* name, float x, float y, float z) {
    GLint loc = getUniformLocation(name);
    glUniform3f(loc, x, y, z);
}

void GLSLProgram::setUniform(const char* name, const glm::vec3& v) {
    this->setUniform(name, v.x, v.y, v.z);
}

void GLSLProgram::setUniform(const char* name, const glm::vec4& v) {
    GLint loc = getUniformLocation(name);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void GLSLProgram::setUniform(const char* name, const glm::vec2& v) {
    GLint loc = getUniformLocation(name);
    glUniform2f(loc, v.x, v.y);
}

void GLSLProgram::setUniform(const char* name, const glm::mat4& m) {
    GLint loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char* name, const glm::mat3& m) {
    GLint loc = getUniformLocation(name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char* name, float val) {
    GLint loc = getUniformLocation(name);
    glUniform1f(loc, val);
}

void GLSLProgram::setUniform(const char* name, int val) {
    GLint loc = getUniformLocation(name);
    glUniform1i(loc, val);
}

void GLSLProgram::setUniform(const char* name, GLuint val) {
    GLint loc = getUniformLocation(name);
    glUniform1ui(loc, val);
}

void GLSLProgram::setUniform(const char* name, bool val) {
    int loc = getUniformLocation(name);
    glUniform1i(loc, val);
}

void GLSLProgram::bindAttribLocation(GLuint location, const char* name) {
    glBindAttribLocation(handle, location, name);
}
