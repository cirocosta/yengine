#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include "../utils/fileinput.h"

namespace yengine { namespace gfx {

  class Texture
  {
  private:
    std::string m_Filename;
    GLuint m_TID;
    GLsizei m_Width, m_Height;
  public:
    Texture(const std::string& filename);
    ~Texture();

    void bind();
    void unbind();

    inline unsigned int getWidth() const { return m_Width; }
    inline unsigned int getHeight() const { return m_Height; }
  private:
    GLuint load();
  };

}} // ns

#endif
