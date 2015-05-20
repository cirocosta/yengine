#include "vertexarray.h"

namespace yengine { namespace graphics {

  VertexArray::VertexArray ()
  {
    glGenVertexArrays(1, &m_ArrayId);
  }

  VertexArray::~VertexArray()
  {
    for (int i = 0; i < (int) m_Buffers.size(); i++)
      delete m_Buffers[i];

    glDeleteVertexArrays(1, &m_ArrayId);
  }

  /**
   * Notice: each VAO will only be compatible
   *         with one sprite. That's because
   *         we don't provide a stride here.
   *
   *         See how it's being done in the batch
   *         renderer.
   */
  void VertexArray::addBuffer(Buffer *buffer, GLuint index)
  {
    bind();
    buffer->bind();

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->getComponentCount(),
                          GL_FLOAT, GL_FALSE, 0, 0);

    buffer->unbind();
    unbind();
  }

  void VertexArray::bind() const
  {
    glBindVertexArray(m_ArrayId);
  }

  void VertexArray::unbind() const
  {
    glBindVertexArray(0);
  }


}}
