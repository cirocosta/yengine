#ifndef RENDERABLE2D_H
#define RENDERABLE2D_H

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer2d.h"
#include "shader.h"

#include <glm/glm.hpp>


namespace yengine { namespace gfx {

  /**
   * Structure that represents the data that the
   * VBO holds for all of the 2D sprites that
   * the game contains (data of each vertex)
   */
  struct VertexData
  {
    glm::vec3 vertex;
    unsigned int color;
  };

  /**
   * Defines basic interface for any 2D sprites
   * that want to be rendered by 2drenderers that
   * we might define.
   */
  class Renderable2D
  {
  protected:
    glm::vec3 m_Position;
    glm::vec2 m_Size;
    glm::vec4 m_Color;
  protected:
    // a group, e.g., does not need to se size,
    // color and position.
    Renderable2D(){}
  public:
    Renderable2D(glm::vec3 position, glm::vec2 size, glm::vec4 color)
      : m_Position(position), m_Size(size), m_Color(color) {}
    virtual ~Renderable2D(){}

    inline const glm::vec3& getPosition() const { return m_Position; }
    inline const glm::vec2& getSize() const { return m_Size; }
    inline const glm::vec4& getColor() const { return m_Color; }

    /**
     * How the renderable should submit itself
     * to a renderer.
     */
    virtual void submit(Renderer2D* renderer) const
    {
      renderer->submit(this);
    }
  };

}} // ns gfx // ns yengine

#endif
