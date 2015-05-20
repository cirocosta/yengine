#ifndef RENDERER2D_H
#define RENDERER2D_H

#include "renderable2d.h"
#include "static_sprite.h"

namespace yengine { namespace gfx {

  /**
   * Base class for 2d renderers. Simply an
   * interface to be implemented by all of those
   * wanting to renderer renderable2d-a-like.
   */
  class Renderer2D
  {
  protected:
    virtual void submit(const Renderable2D* renderable) = 0;
    virtual void flush() = 0;
  };

}}
#endif
