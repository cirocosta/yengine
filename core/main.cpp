#include "src/gfx/window.h"
#include "src/gfx/shader.h"
#include "src/gfx/sprite.h"
#include "src/gfx/layers/tilelayer.h"
#include "src/gfx/layers/group.h"
#include "src/gfx/texture.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <time.h>
#include <vector>

using namespace yengine;
using namespace gfx;

int main()
{
  Window window("Yengine!", 960, 540);
  glClearColor(0.0f, 0.0f, 0.1f, 1.0f);

  Shader* s = new Shader("./src/shaders/basic-vert.glsl",
                         "./src/shaders/basic-frag.glsl");
  Shader& shader = *s;
  TileLayer layer(&shader);

  for (float y = -9.0; y < 9.0f; y++)
    for (float x = -16.0f; x < 16.0f; x++)
      layer.add(new Sprite(x, y, 0.9f, 0.9f, glm::vec4(1.0, 1.0, 1.0, 1.0)));

  glActiveTexture(GL_TEXTURE0);
  Texture texture("test.png");
  texture.bind();

  shader.enable();
  shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
  shader.setUniform1i("tex", 0);

  while (!window.closed())
  {
    double x, y;

    window.clear();
    window.getMousePosition(x, y);
    shader.enable();
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
    layer.render();
    window.update();
  }

  return 0;
}

