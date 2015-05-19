CXX = clang++-3.5
CXXFLAGS = -Wall -std=c++11
INCLUDES = -I/usr/local/include/
LIBS = -L/usr/local/lib
SOURCE = main.cpp

LDLIBS = -lGL -lglfw -lGLEW
OBJECTS = ./src/graphics/window.o \
					./src/graphics/shader.o \
					./src/graphics/buffers/buffer.o \
					./src/graphics/buffers/indexbuffer.o \
					./src/graphics/buffers/vertexarray.o

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
