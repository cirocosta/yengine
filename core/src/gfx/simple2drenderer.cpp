#include "simple2drenderer.h"
#include "renderable2d.h"

namespace yengine { namespace gfx {

    void Simple2DRenderer::submit(const Renderable2D* renderable)
    {
      m_RenderQueue.push_back((StaticSprite*) renderable);
    }

    void Simple2DRenderer::flush()
    {
      while (!m_RenderQueue.empty()) {
        const StaticSprite* sprite = m_RenderQueue.front();

        sprite->getVAO()->bind();
        sprite->getIBO()->bind();
        sprite->getShader().setUniformMat4("ml_matrix",
            glm::translate(glm::mat4(1.0f), sprite->getPosition()));

        glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(),
                       GL_UNSIGNED_SHORT, 0);

        sprite->getVAO()->unbind();
        sprite->getIBO()->unbind();

        m_RenderQueue.pop_front();
      }
    }

}} // ns
