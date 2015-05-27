#include "batchrenderer2d.h"

namespace yengine { namespace gfx {

  BatchRenderer2D::BatchRenderer2D()
  {
    init();
  }

  BatchRenderer2D::~BatchRenderer2D()
  {
    delete m_IBO;
    glDeleteBuffers(1, &m_VBO);
  }

  void BatchRenderer2D::begin()
  {
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER,
                                        GL_WRITE_ONLY);
  }

  void BatchRenderer2D::end()
  {
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  /**
   * Not using our 'vertexarray' creation as this
   * is focused on rendering more than one sprite
   * with the same VAO. For doing that we need
   * specialized VertexAttrib calls.
   */
  void BatchRenderer2D::init()
  {
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE,
                 NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    glEnableVertexAttribArray(SHADER_UV_INDEX);
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);

    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
                          RENDERER_VERTEX_SIZE,
                          (const GLvoid*) 0);
    glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE,
                          RENDERER_VERTEX_SIZE,
                          (const GLvoid*)(offsetof(VertexData, uv)));
    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE,
                          RENDERER_VERTEX_SIZE,
                          (const GLvoid*)(offsetof(VertexData, color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
    int offset = 0;

    // incrementing 6 because we have 5 indices
    // per square
    for (int i = 0; i < RENDERER_INDICES_SIZE; i+= 6) {
      indices[i] = offset + 0;
      indices[i+1] = offset + 1;
      indices[i+2] = offset + 2;

      indices[i+3] = offset + 2;
      indices[i+4] = offset + 3;
      indices[i+5] = offset + 0;

      // each square has 4 vertices, which
      // contains the infos that we are
      // retrieving.
      offset += 4;
    }

    m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
    glBindVertexArray(0);
  }

  /**
   * A 2drenderable is a rectangle. A rectangle
   * is made of four vertices. As we're passing
   * attributes in a single array, each 'row'
   * contains an instance of our VertexData
   * structure. So, we must pass 4 by renderable.
   */
  void BatchRenderer2D::submit(const Renderable2D* renderable)
  {
    // glMapBuffer returns a void pointer. We
    // cast it to our vertex structure so that
    // we're able to directly manipulate it as it
    // must.
    glm::vec3 position = renderable->getPosition();
    glm::vec2 size = renderable->getSize();
    glm::vec4 color = renderable->getColor();
    std::vector<glm::vec2> uv = renderable->getUVs();

    int r = color.x * 255.0f;
    int g = color.y * 255.0f;
    int b = color.z * 255.0f;
    int a = color.w * 255.0f;

    unsigned int c = a << 24 | b << 16 | g << 8 | r;

    // TODO improve this. Lot's of conversions
    //      going on

    // origin
    m_Buffer->vertex = glm::vec3(
        *m_TransformationBack * glm::vec4(position, 1.0));
    m_Buffer->uv = uv[0];
    m_Buffer->color = c;
    m_Buffer++;

    // upper left
    m_Buffer->vertex = glm::vec3(
        *m_TransformationBack * glm::vec4(position.x,
                                          position.y + size.y,
                                          position.z, 1.0));
    m_Buffer->uv = uv[1];
    m_Buffer->color = c;
    m_Buffer++;

    // upper right
    m_Buffer->vertex = glm::vec3(
        *m_TransformationBack * glm::vec4(position.x + size.x,
                                          position.y + size.y,
                                          position.z, 1.0));
    m_Buffer->uv = uv[2];
    m_Buffer->color = c;
    m_Buffer++;

    // bottom right
    m_Buffer->vertex = glm::vec3(
        *m_TransformationBack * glm::vec4(position.x + size.x,
                                          position.y,
                                          position.z, 1.0));
    m_Buffer->uv = uv[3];
    m_Buffer->color = c;
    m_Buffer++;


    // tell that we have one more renderable2d to
    // be rendered.
    m_IndexCount += 6;
  }

  void BatchRenderer2D::flush()
  {
    glBindVertexArray(m_VAO);
    m_IBO->bind();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    m_IBO->bind();
    glBindVertexArray(0);

    m_IndexCount = 0;
  }

}} // ns yengine // ns gfx
