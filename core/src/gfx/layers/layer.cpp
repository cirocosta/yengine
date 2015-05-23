#include "layer.h"

/**
 * Default implementation for our base class.
 */

namespace yengine { namespace gfx {

  Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projection)
    : m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projection)
  {
    m_Shader->enable();
    m_Shader->setUniformMat4("pr_matrix",
                             m_ProjectionMatrix);
    m_Shader->disable();
  }

  Layer::~Layer()
  {
    delete m_Shader;
    delete m_Renderer;

    for (Renderable2D* renderable : m_Renderables)
      delete renderable;
  }

  void Layer::add(Renderable2D* renderable)
  {
    m_Renderables.push_back(renderable);
  }

  void Layer::render()
  {
    m_Shader->enable();

    m_Renderer->begin();
    for (const Renderable2D* renderable : m_Renderables)
      m_Renderer->submit(renderable);
    m_Renderer->end();
    m_Renderer->flush();
  }

}} // ns
