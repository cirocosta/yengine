#ifndef RENDERER2D_H
#define RENDERER2D_H

#include <glm/glm.hpp>
#include <vector>
#include <GL/glew.h>


namespace yengine { namespace gfx {

  class Renderable2D;

  /**
   * Base class for 2d renderers. Simply an
   * interface to be implemented by all of those
   * wanting to renderer renderable2d-a-like.
   *
   * Remember: some renderers will might want to
   *           take advantage of the
   *           transformation stack. This is up
   *           to the renderer to be implement it
   *           properly on its submit method.
   *
   */
  class Renderer2D
  {
  protected:
    std::vector<glm::mat4> m_TransformationStack;
    const glm::mat4* m_TransformationBack;
  protected:
    Renderer2D()
    {
      m_TransformationStack.push_back(glm::mat4(1.0f));
      m_TransformationBack = &m_TransformationStack.back();
    }
  public:
    virtual ~Renderer2D(){}
    inline void push(const glm::mat4 matrix, const bool overrideStack = false)
    {
      if (overrideStack)
        m_TransformationStack.push_back(matrix);
      else
        m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

      m_TransformationBack = &m_TransformationStack.back();
    }

    inline void pop()
    {
      if (m_TransformationStack.size() > 1)
        m_TransformationStack.pop_back();

      m_TransformationBack = &m_TransformationStack.back();
    }

    virtual void begin() {}
    virtual void submit(const Renderable2D* renderable) = 0;
    virtual void flush() = 0;
    virtual void end() {}
  };

}}
#endif
