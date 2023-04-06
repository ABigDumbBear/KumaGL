#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include <glad/glad.h>

#include "Vec3.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

#include "Mat4.hpp"

namespace Kuma3D {

struct MeshVertex
{
  Vec3 mPosition;
  Vec3 mColor;
  Vec3 mNormal;
  float mTexCoords[2] { 0.0, 0.0 };
};

class Mesh
{
  public:
    Mesh();
    ~Mesh();

    void Draw(const Shader& aShader,
              GLenum aMode = GL_TRIANGLES);
    void DrawInstanced(const Shader& aShader,
                       int aNumInstances,
                       GLenum aMode = GL_TRIANGLES);

    void UpdateVertices();
    void UpdateIndices();

    GLuint GetVertexArrayID() const { return mVertexArray; }
    GLuint GetVertexBufferID() const { return mVertexBuffer; }
    GLuint GetInstanceBufferID() const { return mInstanceBuffer; }
    GLuint GetElementBufferID() const { return mElementBuffer; }

    std::vector<MeshVertex> mVertices;
    std::vector<unsigned int> mIndices;

  private:
    GLuint mVertexArray { 0 };
    GLuint mVertexBuffer { 0 };
    GLuint mInstanceBuffer { 0 };
    GLuint mElementBuffer { 0 };
};

} // namespace Kuma3D

#endif
