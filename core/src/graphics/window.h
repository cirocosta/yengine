#ifndef WINDOW_H
#define WINDOW_H

namespace yengine {
  namespace graphics {

    class Window
    {
    private:
      const char * name;
      int width, height;
    public:
      Window(const char *name, int width, int height);
      ~Window();

      void update() const;
    };
  } // ns graphics
} // ns yengine


#endif // WINDOW_H
