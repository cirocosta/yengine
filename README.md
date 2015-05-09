# YENGINE

> A tiny gaming framework that also compiles to webbrowsers using emscripten

- we're going to use GLFW3 for window manipulation
- also, GLEW for opengl lib stuff
- and GLM for math regarding matrices, etc

```sh
$ sudo apt-get install libglm-dev libglew-dev libglfw3-dev
```

### GLFW3

`libglfw3-dev` will probably not be reachable from aptitute for your system (i'm on Ubuntu 14.04 lts now and it doesn't), so you might want to build it from source w/ cmake:

1.  Download it from GLFW website
2.  Unzip it somewhere
3.  Edit `CMakeLists.txt` setting `BUILD_SHARED_LIBS` to `ON`
4.  run:

```sh
# cmake -G "Unix Makefiles"
# make
# make install
```


## Conventions

`m_` stands for private stuff in classes.



