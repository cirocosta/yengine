#include "group.h"

namespace yengine { namespace gfx {

  Group::Group(const glm::mat4 transformation)
    : m_TransformationMatrix(transformation)
  { }

  void Group::add(Renderable2D* renderable)
  {
    m_Renderables.push_back(renderable);
  }

  void Group::submit(Renderer2D* renderer) const
  {
    renderer->push(m_TransformationMatrix);

    for (const Renderable2D* renderable : m_Renderables)
      renderable->submit(renderer);

    renderer->pop();
  }

}} // ns

