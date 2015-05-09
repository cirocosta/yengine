CXX = clang++-3.5
CXXFLAGS = -Wall -std=c++11
LDLIBS = -lglfw

OBJ_DIR = bin

SOURCE = main.cpp
OBJECTS = ${SOURCE:%.cpp=$(OBJ_DIR)/%.o}
EXECUTABLE = main

all: init $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE):
	$(CXX) $(LDFLAGS) $(LIB_DIR) -o $@ $(OBJECTS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(INC_DIR) -c $< -o $@

init:
	@mkdir -p "$(OBJ_DIR)"
