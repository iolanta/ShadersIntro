
#include "OBJ_Loader.h"
#include "GLobject.h"

GLobject::GLobject(std::string path)
{
	objl::Loader modelloader;
	modelloader.LoadFile(path);
	count_indexes = modelloader.LoadedIndices.size();
	count_vertex = modelloader.LoadedVertices.size();

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glGenVertexArrays(1, &VAO);
	
	//		   XYZW					Normal XYZ		 TexCoords	UV					Color RGB		
	auto len = sizeof(GLfloat) * 4 + sizeof(GLfloat) * 3 + sizeof(GLfloat) * 2 + sizeof(GLfloat) * 3;
	CoordOffset = 0;
	NormalOffset = sizeof(GLfloat)*4;
	TexCoordOffset = NormalOffset + sizeof(GLfloat) * 3;
	ColorOffset = TexCoordOffset + sizeof(GLfloat) * 2;
	stride = len;

	glBindVertexArray(VAO);

	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	glBufferData(GL_ARRAY_BUFFER, len*modelloader.LoadedVertices.size(), NULL, GL_STATIC_DRAW);
	GLfloat * mapped_data = (GLfloat *)glMapBufferRange(GL_ARRAY_BUFFER, 0, len*modelloader.LoadedVertices.size(), GL_MAP_WRITE_BIT);
	int ind = 0;
	for (size_t i = 0; i < modelloader.LoadedVertices.size(); i+=12)
	{
		mapped_data[i] = modelloader.LoadedVertices[ind].Position.X;
		mapped_data[i+1] = modelloader.LoadedVertices[ind].Position.Y;
		mapped_data[i+2] = modelloader.LoadedVertices[ind].Position.Z;
		mapped_data[i + 3] = 1;
		mapped_data[i + 4] = modelloader.LoadedVertices[ind].Normal.X;
		mapped_data[i + 5] = modelloader.LoadedVertices[ind].Normal.Y;
		mapped_data[i + 6] = modelloader.LoadedVertices[ind].Normal.Z;
		mapped_data[i + 7] = modelloader.LoadedVertices[ind].TextureCoordinate.X;
		mapped_data[i + 8] = modelloader.LoadedVertices[ind].TextureCoordinate.Y;
		mapped_data[i + 8] = modelloader.LoadedVertices[ind].TextureCoordinate.Y;
		mapped_data[i + 9] = 0;
		mapped_data[i + 10] = 0;
		mapped_data[i + 11] = 0;
		ind++;
	}
	glUnmapBuffer(GL_ARRAY_BUFFER);
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelloader.LoadedIndices.size() * sizeof(unsigned int), modelloader.LoadedIndices.data(), GL_STATIC_DRAW);


	glBindVertexArray(0);

}

bool GLobject::BindAttributesToShader(GLShader & shaderobject)
{
	glBindVertexArray(VAO);
	GLint CoordAttrib = shaderobject.getAttributeLocation("coord");
	GLint NormAttrib = shaderobject.getAttributeLocation("norm");
	GLint TexCoordAttrib = shaderobject.getAttributeLocation("texcoord");
	GLint ColorAttriv = shaderobject.getAttributeLocation("color");
	if (CoordAttrib == -1 || NormAttrib == -1 || TexCoordAttrib == -1 || CoordAttrib == -1)
	{
		glBindVertexArray(0);
		return false;
	}

	glEnableVertexAttribArray(CoordAttrib);
	glEnableVertexAttribArray(NormAttrib);
	glEnableVertexAttribArray(TexCoordAttrib);
	glEnableVertexAttribArray(ColorAttriv);

	glVertexAttribPointer(CoordAttrib, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid *)CoordOffset);
	glVertexAttribPointer(NormAttrib, 3, GL_FLOAT, GL_TRUE, stride, (GLvoid *)NormalOffset);
	glVertexAttribPointer(TexCoordAttrib, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)TexCoordOffset);
	glVertexAttribPointer(ColorAttriv, 3, GL_FLOAT, GL_TRUE, stride, (GLvoid *)ColorOffset);

	glBindVertexArray(0);
	return true;
}

void GLobject::drawObject()
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, count_indexes);

	glBindVertexArray(0);
}


GLobject::~GLobject()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
