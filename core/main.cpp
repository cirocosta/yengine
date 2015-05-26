#include "src/gfx/window.h"
#include "src/gfx/shader.h"
#include "src/gfx/sprite.h"
#include "src/gfx/layers/tilelayer.h"
#include "src/gfx/layers/group.h"

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
  shader.enable();
  shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));

  TileLayer layer(&shader);

  Group* group = new Group(glm::translate(glm::vec3(-15.0f, 5.0f, 0.0f)));
  group->add(new Sprite(0, 0, 6, 3, glm::vec4(1,1,1,1)));

  Group* button = new Group(glm::translate(glm::vec3(0.5f, 0.5f, 0.0f)));
  button->add(new Sprite(0, 0, 5.0f, 2.0f, glm::vec4(1,0,1,1)));
  button->add(new Sprite(0.5f, 0.5f, 3.0f, 1.0f, glm::vec4(0.9f, 1.0f, 0.8f, 1)));
  group->add(button);

  layer.add(group);

  while (!window.closed())
  {
    double x, y;

    window.clear();
    window.getMousePosition(x, y);
    shader.enable();
    shader.setUniform2f("light_pos", glm::vec2(
        (float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f))
    );

    layer.render();

    window.update();
  }

  delete s;
  delete group;
  delete button;

  return 0;
}
