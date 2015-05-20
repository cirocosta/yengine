#include "batchrenderer2d.h"

namespace yengine { namespace graphics {

  BatchRenderer2D::BatchRenderer2D()
  {
    init();
  }

  BatchRenderer2D::~BatchRenderer2D()
  {
    delete m_IBO;
    glDeleteBuffers(1, &m_VBO);
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
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE,
                          RENDERER_VERTEX_SIZE,
                          (const GLvoid*) 0);
    glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE,
                          RENDERER_VERTEX_SIZE,
                          (const GLvoid*)(3 * sizeof(GLfloat)));

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

    // origin
    m_Buffer->vertex = position;
    m_Buffer->color = color;
    m_Buffer++;

    // upper left
    m_Buffer->vertex = glm::vec3(position.x,
                                 position.y + size.y,
                                 position.z);
    m_Buffer->color = color;
    m_Buffer++;

    // upper right
    m_Buffer->vertex = glm::vec3(position.x + size.x,
                                 position.y + size.y,
                                 position.z);
    m_Buffer->color = color;
    m_Buffer++;

    // bottom right
    m_Buffer->vertex = glm::vec3(position.x + size.x,
                                 position.y,
                                 position.z);
    m_Buffer->color = color;
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

}} // ns yengine // ns graphics
