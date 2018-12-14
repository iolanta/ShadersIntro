#include "GLShader.h"

ShaderData::ShaderData(){}

ShaderData::ShaderData(GLuint sh, GLenum type) {
	ShaderData::shader = sh;
	ShaderData::shader_type = type;
}

VariableData::VariableData() {}

VariableData::VariableData(std::string n, GLenum t, GLsizei sz) {
	VariableData::name = n;
	VariableData::type = t;
	VariableData::size = sz;
}

GLShader::GLShader()
{
	GLShader::ShaderProgram = 0;
	GLShader::shaders = std::map<int, ShaderData>();
	GLShader::attributes = std::map<std::string, VariableData>();
	shader_count = 0;
	ShaderProgram = glCreateProgram();
}


GLShader::~GLShader()
{
	glUseProgram(0);
	GLint act_cnt;
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &act_cnt);
	GLuint * attached = new GLuint[act_cnt];
	glGetAttachedShaders(ShaderProgram, act_cnt, &act_cnt, attached);
	for (int i = 0; i < act_cnt; ++i) {
		glDetachShader(ShaderProgram, attached[i]);
		
	}
	delete attached;
	glDeleteProgram(ShaderProgram);

	for (int i = 0; i < shaders.count; ++i) {
		glDeleteShader(shaders[i].shader);
	}
}

int GLShader::load_shader(std::string filename, GLenum shader_type) {
	GLuint s = compileSource(filename, shader_type);
	ShaderData sd = ShaderData(s, shader_type);
	shaders.insert(std::pair<int, ShaderData>(shader_count, sd));
	++shader_count;
}

std::string GLShader::loadSourceFile(const std::string& source_file_name) {
	std::ifstream f(source_file_name);
	std::stringstream ss;
	ss << f.rdbuf(); 
	return ss.str();
}

GLuint GLShader::compileSource(std::string filename, GLenum shader_type) {
	GLuint shader = glCreateShader(shader_type);
	std::string str = loadSourceFile(filename);
	const char * c = str.c_str();
	int len = str.length();
	glShaderSource(shader,1,&c,&len);
	glCompileShader(shader);
	printInfoLogShader(shader);
	return shader;
}

void GLShader::printInfoLogShader(GLuint shader) {
	int infologLen = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);
	if (infologLen > 1)
	{
		infoLog = new char[infologLen];
		if (infoLog == NULL)
		{
			std::cout << "ERROR: Could not allocate InfoLog buffer\n";
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
		std::cout << "InfoLog: " << infoLog << "\n\n\n";
		delete[] infoLog;
	}
}

void GLShader::linkProgram(int vertex_id, int fragment_id) {
	GLint act_cnt;
	glGetProgramiv(ShaderProgram, GL_ATTACHED_SHADERS, &act_cnt);
	GLuint * attached = new GLuint[act_cnt];
	glGetAttachedShaders(ShaderProgram, act_cnt, &act_cnt, attached);
	for (int i = 0; i < act_cnt; ++i)
		glDetachShader(ShaderProgram, attached[i]);
	delete attached;

	glAttachShader(ShaderProgram, shaders[vertex_id].shader);
	glAttachShader(ShaderProgram, shaders[fragment_id].shader);
	glLinkProgram(ShaderProgram);

	int link_ok;
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &link_ok);
	if (!link_ok)
	{
		std::cout << "error attach shaders \n";
		return;
	}

	int count_attributes, max_length;
	glGetProgramiv(ShaderProgram, GL_ACTIVE_ATTRIBUTES, &count_attributes);
	glGetProgramiv(ShaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_length);
	char* name = new char[max_length]; 
	for (int i= 0; i < count_attributes; ++i) {
		int size;
		GLenum type;
		glGetActiveAttrib(ShaderProgram, i, max_length, NULL, &size, &type, name);

		std::string sname = std::string(name);
		VariableData vb(sname, type, size);
		attributes.insert(std::pair<std::string, VariableData>(sname, vb));
	}
}

void GLShader::checkOpenGLerror()
{
	GLenum errCode;
	if ((errCode = glGetError()) != GL_NO_ERROR)
		std::cout << "OpenGl error! - " << gluErrorString(errCode);
}