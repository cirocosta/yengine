CXX = clang++-3.5
CXXFLAGS = -Wall -std=c++11
INCLUDES = -I/usr/local/include/
LIBS = -L/usr/local/lib
SOURCE = main.cpp

LDLIBS = -lGL -lglfw -lGLEW

main: ./src/graphics/window.o main.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE) $(INCLUDES) $(LIBS) $(LDLIBS) -o $@ $<

./src/graphics/window.o: ./src/graphics/window.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	find . -name "*.o" -delete
	rm main
