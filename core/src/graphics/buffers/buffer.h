#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>

namespace yengine { namespace graphics {

  /**
   * Holds reference to memory location of a
   * buffer on the GPU. Used to instantiate basic
   * ARRAY_BUFFER buffer types.
   */
  class Buffer
  {
    private:
      GLuint m_BufferId;
      // how many components each data-section
      // contais (e.g., vec3 --> 3).
      GLuint m_ComponentCount;
    public:
      Buffer (GLfloat * data, GLsizei count, GLuint componentCount);
      // use glDeleteBuffers here?
      ~Buffer(){}

      void bind() const;
      void unbind() const;

      inline GLuint getComponentCount() const {
        return m_ComponentCount;
      }
  };

}}


#endif
