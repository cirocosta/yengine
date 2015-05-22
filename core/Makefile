CXX = clang++-3.5
INCLUDES = -I/usr/local/include/
LIBS = -L/usr/local/lib
BUILD := debug
LDLIBS = -lGL -lglfw -lGLEW

cxxflags.debug := -g -DNDEBUG
cxxflags.release := -O3
CXXFLAGS := -Wall -std=c++11 ${cxxflags.${BUILD}}

SOURCE = main.cpp
OBJECTS = ./src/gfx/window.o \
					./src/gfx/shader.o \
					./src/gfx/buffers/buffer.o \
					./src/gfx/buffers/indexbuffer.o \
					./src/gfx/buffers/vertexarray.o \
					./src/gfx/simple2drenderer.o \
					./src/gfx/batchrenderer2d.o \
					./src/gfx/sprite.o \
					./src/gfx/static_sprite.o


main: ./src/libyengine.a $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) $(INCLUDES) $(LIBS) $(LDLIBS) -o $@ $<

./src/libyengine.a: $(OBJECTS)
	$(AR) rvs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


.PHONY: clean run

run: main
	optirun ./main

clean:
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	rm main
