#ifndef LAYER_H
#define LAYER_H

#include "../renderer2d.h"
#include "../renderable2d.h"
#include "../shader.h"
#include <glm/glm.hpp>
#include <vector>

namespace yengine { namespace gfx {

  class Layer
  {
  protected:
    Renderer2D* m_Renderer;
    std::vector<Renderable2D*> m_Renderables;
    Shader* m_Shader;
    glm::mat4 m_ProjectionMatrix;

  protected:
    Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projection);

  public:
    virtual ~Layer();
    virtual void add(Renderable2D* renderable);

    /**
     * Enables the shader associated with the
     * layer, begins the layer's renderer and
     * the start calling its renderables
     * submit method (for submitting themselves
     * to the renderer). Notice that the
     * renderables implements the submit routine
     * for getting inserted in a renderable.
     */
    virtual void render();
  };

}} // ns

#endif
