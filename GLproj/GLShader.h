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
	GLenum type;
	GLsizei size;

	VariableData();
	VariableData(std::string n, GLenum t, GLsizei sz);
};

class GLShader {
public:
	GLShader();
	~GLShader();

	int load_shader(std::string filename, GLenum shader_type);

private:
	GLuint ShaderProgram;
	int shader_count;

	std::map<int, ShaderData> shaders;
	std::map<std::string, VariableData> attributes;

	std::string loadSourceFile(const std::string& source_file_name);

	GLuint compileSource(std::string filename, GLenum shader_type);

	void printInfoLogShader(GLuint shader);

	void linkProgram(int vertex_id, int fragment_id);

	void checkOpenGLerror();
};
