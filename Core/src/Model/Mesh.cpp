#include "cpch.h"
#include "Mesh.h"

#include <glad/glad.h>

#include "Renderer/Shader.h"

namespace Core {

	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint32_t> indices, std::vector<MeshTexture> textures)
		: Vertices(vertices), Indices(indices), Textures(textures)
    {
        SetupMesh();
    }

    void Mesh::Draw()
    {
        uint32_t diffuseIndex = 1;
        uint32_t specularIndex = 1;

        Shader::Bind("Model");

        for (int i = 0; i < Textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = Textures[i].Type;

            if (name == "texture_diffuse")
                number = std::to_string(diffuseIndex++);
            else if (name == "texture_specular")
                number = std::to_string(specularIndex++);

            Shader::UploadUniform("Model", ("material." + name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
        }
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

	void Mesh::SetupMesh()
	{
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(MeshVertex), &Vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));

        glBindVertexArray(0);
	}
}