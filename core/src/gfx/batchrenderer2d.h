#ifndef BATCHRENDERER2D_H
#define BATCHRENDERER2D_H

#include "renderer2d.h"
#include "renderable2d.h"
#include "buffers/indexbuffer.h"
#include <glm/gtc/type_ptr.hpp>


namespace yengine { namespace gfx {

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

/**
 * PS: here we define a contract between our
 *     renderer and those shaders that are
 *     capable of dealing with it. They MUST have
 *     their attribute locations se to what's
 *     defined here. (at least for now)
 */
#define SHADER_VERTEX_INDEX     0
#define SHADER_UV_INDEX         1
#define SHADER_COLOR_INDEX      2

  class BatchRenderer2D : public Renderer2D
  {
  private:
    GLuint m_VAO;
    GLuint m_VBO;
    IndexBuffer* m_IBO;
    VertexData* m_Buffer;

    GLsizei m_IndexCount;
  public:
    BatchRenderer2D ();
    ~BatchRenderer2D ();

    /**
     * This basic begin->submit->end->flush flow
     * lets us not have to waste time with
     * glMapBuffer pointer retrieving, casting,
     * etc. Just submit on iteration.
     */
    void begin() override;
    void submit(const Renderable2D* renderable) override;
    void end() override;
    void flush() override;
  private:
    void init();
  };


}} // ns

#endif // batchrenderer2d_h
