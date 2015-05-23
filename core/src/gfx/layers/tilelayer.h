#ifndef TILELAYER_H
#define TILELAYER_H

#include "../batchrenderer2d.h"
#include "layer.h"
#include <glm/gtx/transform.hpp>

namespace yengine { namespace gfx {

  class TileLayer : public Layer
  {
  public:
    TileLayer(Shader* shader);
    ~TileLayer();
  };


}} // ns

#endif
