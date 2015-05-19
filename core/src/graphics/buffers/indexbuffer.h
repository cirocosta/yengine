#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <GL/glew.h>

namespace yengine { namespace graphics {

  /**
   * Holds reference to memory location of a
   * buffer on the GPU that's specialized for
   * indices
   */
  class IndexBuffer
  {
    private:
      GLuint m_BufferId;
      // how many components each data-section
      // contais (e.g., vec3 --> 3).
      GLuint m_Count;
    public:
      IndexBuffer (GLushort * data, GLsizei count);
      // use glDeleteBuffers here?
      ~IndexBuffer(){}

      void bind() const;
      void unbind() const;

      inline GLuint getCount() const {
        return m_Count;
      }
  };

}}


#endif
