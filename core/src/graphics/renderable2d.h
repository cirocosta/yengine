#ifndef RENDERABLE2D_H
#define RENDERABLE2D_H

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "shader.h"
#include <glm/glm.hpp>


namespace yengine { namespace graphics {

  class Renderable2D
  {
  protected:
    glm::vec3 m_Position;
    glm::vec2 m_Size;
    glm::vec4 m_Color;

    VertexArray* m_VertexArray;
    IndexBuffer* m_IndexBuffer;
    Shader& m_Shader;

  public:
    Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color, Shader& shader)
      : m_Position(position), m_Size(size), m_Color(color), m_Shader(shader)
    {
      m_VertexArray = new VertexArray();
      GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
      GLfloat vertices[] =
      {
        0, 0, 0,
        0, size.y, 0,
        size.x, size.y, 0,
        size.x, 0, 0,
      };

      GLfloat colors[] =
      {
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w,
      };

      m_VertexArray->addBuffer(new Buffer(vertices, 4*3, 3), 0);
      m_VertexArray->addBuffer(new Buffer(colors, 4*4, 4), 1);
      m_IndexBuffer = new IndexBuffer(indices, 6);
    }

    virtual ~Renderable2D()
    {
      delete m_VertexArray;
      delete m_IndexBuffer;
    }

    inline const VertexArray* getVAO() const { return m_VertexArray; }
    inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }

    inline const glm::vec3& getPosition() const { return m_Position; }
    inline const glm::vec2& getSize() const { return m_Size; }
    inline const glm::vec4& getColor() const { return m_Color; }

    inline Shader& getShader() const { return m_Shader; }
  };

}} // ns graphics // ns yengine

#endif
