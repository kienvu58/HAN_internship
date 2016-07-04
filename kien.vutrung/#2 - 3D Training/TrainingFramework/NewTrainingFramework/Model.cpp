#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"


Model::Model(const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (f)
	{
		fscanf(f, "NrVertices: %d\n", &m_NVertices);
		Vertex* vertices = new Vertex[m_NVertices];
		for (int i = 0; i < m_NVertices; i++)
		{
			Vertex tmp;
			fscanf(f, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			       &tmp.pos.x, &tmp.pos.y, &tmp.pos.z, &tmp.norm.x, &tmp.norm.y, &tmp.norm.z,
			       &tmp.binorm.x, &tmp.binorm.y, &tmp.binorm.z, &tmp.tgt.x, &tmp.tgt.y, &tmp.tgt.z, &tmp.uv.x, &tmp.uv.y);
			vertices[i] = tmp;
		}
		fscanf(f, "NrIndices: %d\n", &m_NIndices);
		unsigned int* indices = new unsigned int[m_NIndices];
		for (int i = 0; i < m_NIndices / 3; i++)
		{
			fscanf(f, "%*d.    %d,    %d,    %d\n", &indices[3 * i], &indices[3 * i + 1], &indices[3 * i + 2]);
		}
		glGenBuffers(1, &m_VboId);
		glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
		glBufferData(GL_ARRAY_BUFFER, m_NVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &m_IboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_NIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		delete[] vertices;
		delete[] indices;
	}
	else
	{
		printf("Failed to open file: %s\n", filename);
	}
}

Model::~Model()
{
	glDeleteBuffers(1, &m_VboId);
	glDeleteBuffers(1, &m_IboId);
}

GLuint Model::GetVboId() const
{
	return m_VboId;
}

GLuint Model::GetIboId() const
{
	return m_IboId;
}

int Model::GetNIndices() const
{
	return m_NIndices;
}

int Model::GetNVertices() const
{
	return m_NVertices;
}