#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <SOIL2.h>
#include <cmath>
#include <utility>
#include <iostream>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLShader.h"
#include "GLobject.h"


int w = 0, h = 0;

GLShader * shaderwrap;
GLobject * objectwrap;

std::vector<int> VertShaders;
std::vector<int> FragShaders;
glm::mat4 Matrix_projection;

float rotateX = 0;
float rotateY = 0;
float scaleX = 1;
float scaleY = 1;


std::vector<std::string> pathsVert = {
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



void Init(void)
{
	glClearColor(0, 0, 0, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0) return;

	w = x;
	h = y;
	glViewport(0, 0, w, h);

	Matrix_projection = glm::perspective(80.0f, (float)w / h, 0.01f, 200.0f);
	glm::vec3 eye = {5,0,0};
	glm::vec3 center = { 0,0,0 };
	glm::vec3 up = { 0,0,1};

	Matrix_projection  *= glm::lookAt(eye,center,up);

	

}



void Update(void) {
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(shaderwrap->ShaderProgram);
	

	glm::mat4 transfor = glm::scale(Matrix_projection, glm::vec3{ scaleX,scaleY,1 });
	transfor = glm::rotate(transfor, rotateX, glm::vec3( 1,0,0 ));
	transfor = glm::rotate(transfor, rotateY, glm::vec3(0, 1, 0));
	shaderwrap->setUniformmat4("transf",false, transfor);	
	
	shaderwrap->setUniformfv3("color", glm::vec3 { 1,0,0 });

	objectwrap->drawObject();

	glUseProgram(0);
	


	glFlush();
	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)	
{
	switch (key)
	{
	case 'w':
		rotateX += 0.1;
		break;
	case 's':
		rotateX -= 0.1;
		break;
	case 'a':
		rotateY -= 0.1;
		break;
	case 'd':
		rotateY += 0.1;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		scaleX += 0.1;
		break;
	case GLUT_KEY_DOWN:
		scaleX -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		scaleY -= 0.1;
		break;
	case GLUT_KEY_RIGHT:
		scaleY += 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void LoadShaders() {



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
	shaderwrap->linkProgram(VertShaders[0], FragShaders[0]);

	

	objectwrap->BindAttributesToShader(*shaderwrap);
	
	shaderwrap->checkOpenGLerror();

	glutMainLoop();


	return 0;         
}