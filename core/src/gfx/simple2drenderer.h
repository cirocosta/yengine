#ifndef SIMPLE2DRENDERER_H
#define SIMPLE2DRENDERER_H

#include "renderer2d.h"
#include "static_sprite.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <deque>

namespace yengine { namespace gfx {

  /**
   * Very naive implementation of a renderer
   * using a double-endend queue with simple
   * calls to drawElements for all elements
   * submitted.
   */
  class Simple2DRenderer : public Renderer2D
  {
  private:
    std::deque<const StaticSprite*> m_RenderQueue;
  public:
    virtual void submit(const Renderable2D* renderable) override;
    virtual void flush() override ;
  };

}}
#endif
