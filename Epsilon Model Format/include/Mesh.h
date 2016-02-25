///========= Copyright Survtech, All rights reserved. ============//
///
/// Purpose:
///
///=============================================================================

#pragma once
/// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
/// GL Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


struct Vertex
{
    /// Position
    glm::vec3 Position;
    /// Normal
    glm::vec3 Normal;
    /// TexCoords
    glm::vec2 TexCoords;
    ///Tangents
    glm::vec3 Tangent;
    ///Bitangents
    glm::vec3 Bitangent;
};

struct Texture
{
    unsigned int id;
    string type;
    aiString path;
};

class Mesh
{
public:
    /**  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    /**  Functions  */
    /// Constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
    }

    ~Mesh()
    {

    }


private:

};
