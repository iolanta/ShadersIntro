#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <SOIL2.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

class ShaderData {
public:
	GLuint shader;
	GLenum shader_type;

	ShaderData();
	ShaderData(GLuint sh, GLenum type);

};

class VariableData {
public:
	std::string name;
	GLint location;
	GLenum type;
	GLsizei size;

	VariableData();
	VariableData(GLint  l,std::string n, GLenum t, GLsizei sz);
};

class GLShader {
public:
	GLShader();
	~GLShader();

	bool load_shader(std::string filename, GLenum shader_type);

	bool setUniformfv4(std::string name, const GLfloat  * vec4);
	bool setUniformfv3(std::string name,  const  GLfloat  * vec3);
	bool setUniformfv2(std::string name,  const   GLfloat  *vec2);
	bool setUniformmat4(std::string name, bool transpose,   const GLfloat * mat);
	bool setUniform1i(std::string name,  const GLint value);

	GLint getAttributeLocation(std::string name);


private:
	GLuint ShaderProgram;
	int shader_count;

	std::map<int, ShaderData> shaders;
	std::map<std::string, VariableData> attributes;
	std::map<std::string, VariableData> uniforms;

	std::string loadSourceFile(const std::string& source_file_name);

	GLuint compileSource(std::string filename, GLenum shader_type);

	void printInfoLogShader(GLuint shader);

	void linkProgram(int vertex_id, int fragment_id);

	void checkOpenGLerror();



};

