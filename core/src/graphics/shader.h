/**
 * Shader is going to manage shaders for us
 * by loading it from files, sending data,
 * enabling and desabling them as well as storing
 * locations.
 */

#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/fileinput.h"

namespace yengine { namespace graphics {
  class Shader
  {
  private:
    // OpenGL gives us a number so that we can
    // refer to it later.
    // keeping here for debugging purposes
    const char* m_VertPath;
    const char* m_FragPath;
    GLuint m_ShaderId;
  public:
    Shader(const char* vertPath, const char* fragPath);
    ~Shader();

    void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
    void setUniform4f(const GLchar* name, const glm::vec4& vec);
    void setUniform2f(const GLchar* name, const glm::vec2& vec);

    void enable() const;
    void disable() const;
  private:
    GLuint load();
    GLint getUniformLocation(const GLchar* name);
  };

}} // ns ns

#endif
