/**
 * To be used with the simple renderer
 */

#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include "renderable2d.h"

namespace yengine { namespace gfx {

  class StaticSprite : public Renderable2D
  {
  private:
    VertexArray* m_VertexArray;
    IndexBuffer* m_IndexBuffer;
    Shader& m_Shader;
  public:
    StaticSprite(float x, float y,
                 float width, float height,
                 glm::vec4 color,
                 Shader& shader);
    ~StaticSprite();

    /**
     * Accessing
     */
    inline const VertexArray* getVAO() const { return m_VertexArray; }
    inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
    inline Shader& getShader() const { return m_Shader; }
  };

}}

#endif
