#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <SOIL2.h>
#include <cmath>
#include <utility>
#include <iostream>
#include <vector>
#include <glm/gtc/matrix_inverse.hpp>



#include "GLShader.h"
#include "GLobject.h"


int w = 0, h = 0;

GLShader * shaderwrap;
GLobject * objectwrap;

std::vector<int> VertShaders;
std::vector<int> FragShaders;

void Init(void)
{
	glClearColor(0, 0, 0, 1.0f);



}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	w = x;
	h = y;

	glViewport(0, 0, w, h);

}



void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	


	glFlush();
	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)	
{
	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	glutPostRedisplay();
}


void LoadShaders() {
	std::vector<std::string> pathsVert =  {
	"shader_lab12.vert"
	};

	std::vector<std::string> pathsFrag = {
	"shader_lab12.frag",
	"shader_lab12_horizontal.frag",
	"shader_lab12_vertical.frag",
	"shader_lab12_tex.frag",
	"shader_lab12_texcolor.frag",
	"shader_lab12_twotex.frag",
	};


	for (size_t i = 0; i < pathsVert.size(); i++)
	{
		VertShaders.push_back(shaderwrap->load_shader(pathsVert[i], GL_VERTEX_SHADER));
	}

	for (size_t i = 0; i < pathsFrag.size(); i++)
	{
		FragShaders.push_back(shaderwrap->load_shader(pathsFrag[i], GL_FRAGMENT_SHADER));
	}

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);

	glutCreateWindow("OpenGL");
	glEnable(GL_DEPTH_TEST);

	
	glutDisplayFunc(Update);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << glewGetErrorString(err) << std::endl;

	}
	Init();

	shaderwrap = new GLShader();
	objectwrap = new GLobject("cat.obj");

	LoadShaders();
	glutMainLoop();


	return 0;         
}