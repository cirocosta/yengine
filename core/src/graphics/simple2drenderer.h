#ifndef SIMPLE2DRENDERER_H
#define SIMPLE2DRENDERER_H

#include "renderer2d.h"
#include "renderable2d.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <deque>

namespace yengine { namespace graphics {

  class Simple2DRenderer : public Renderer2D
  {
  private:
    std::deque<const Renderable2D*> m_RenderQueue;
  public:
    virtual void submit(Renderable2D* renderable) override;
    virtual void flush() override ;
  };

}}
#endif
