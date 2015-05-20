#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>
#include <GL/glew.h>
#include "buffer.h"

namespace yengine { namespace gfx {
  /**
   * Encapsulates VAOs, which are responsible for
   * storing all of the state needed to supply
   * vertex data, i.e, the format of the vertex
   * data as well as the Buffer Objects, which
   * then provides the data arrays.
   */
  class VertexArray
  {
  private:
    GLuint m_ArrayId;
    std::vector<Buffer*> m_Buffers;
  public:
    VertexArray();
    // also call glDeleteVertexArrays ?
    ~VertexArray();

    /**
     * Adds a buffer to the buffers vector.
     * 'index' corresponds to the attribute that
     * a buffer object will be 'bounded' to (an
     * attribute from the vshader).
     */
    void addBuffer(Buffer* buffer, GLuint index);
    void bind() const;
    void unbind() const;
  };

}}


#endif
