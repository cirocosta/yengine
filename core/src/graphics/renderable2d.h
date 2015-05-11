#ifndef RENDERABLE2D
#define RENDERABLE2D

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace glm;

namespace yengine { namespace graphics {

  class Renderable2D
  {
  protected:
    vec3 m_Position;
    vec2 m_Size;
    vec4 m_Color;
  };

}} // ns graphics // ns yengine

#endif
