#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>

#include <glad/glad.h>

#include"Vertex.h"

static std::vector<Vertex> loadOBJ(const char* file_name)
{
	//Vertex portions
	std::vector<glm::fvec3> vertex_positions;
	std::vector<glm::fvec2> vertex_texcoords;
	std::vector<glm::fvec3> vertex_normals;
	
	//Face vectors
	std::vector<GLint> vertex_position_indicies;
	std::vector<GLint> vertex_texcoord_indicies;
	std::vector<GLint> vertex_normal_indicies;

	//Vertex array
	std::vector<Vertex> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;
	GLint temp_glint = 0;

	//Check if the file can be opened
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v") //Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_texcoords.push_back(temp_vec2);
		}
		else if (prefix == "f")
		{
			int counter = 0;
			while (ss >> temp_glint)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					vertex_position_indicies.push_back(temp_glint);
				else if (counter == 1)
					vertex_texcoord_indicies.push_back(temp_glint);
				else if (counter == 2)
					vertex_normal_indicies.push_back(temp_glint);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
		}
	}
	
	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size(), Vertex());
	
	//Load in all indices
	for (size_t i = 0; i < vertex_position_indicies.size(); ++i)
	{
		if (vertex_position_indicies[i] - 1 < vertex_positions.size() &&
			vertex_texcoord_indicies[i] - 1 < vertex_texcoords.size())
		{
			vertices[i].position = vertex_positions[vertex_position_indicies[i] - 1];
			vertices[i].textcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
		}
		else
		{
			std::cerr << "Index out of bounds at vertex " << i << "\n";
		}
		vertices[i].color = glm::vec3(1.f, 1.f, 1.f); // Default color
	}

	//DEBUG
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	return vertices;
}