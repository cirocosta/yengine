#ifndef GROUP_H
#define GROUP_H

#include "../renderable2d.h"

namespace yengine { namespace gfx {

  /**
   * Represents an abstract group of renderables.
   * Although this IS actually a renderable, it
   * does not has a drawing.
   */
  class Group : public Renderable2D
  {
  private:
    std::vector<Renderable2D*> m_Renderables;
    glm::mat4 m_TransformationMatrix;
  public:
    /**
     * Constructs a group. Each group starts from
     * a local transformation
     */
    Group(const glm::mat4 transformation);

    /**
     * Renderables are added to a group and
     * submitted to a renderer, which is then
     * responsible for ...
     */
    void add(Renderable2D* renderable);
    void submit(Renderer2D* renderer) const override;
  };

}} // ns

#endif
