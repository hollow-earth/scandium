## C++ specific stuff
CXX = g++
CFLAGS = 
OUTPUT =

## Includes
LIBS = -I"C:\\Coding\\glfw-3.3.7\\include" -I"C:\\Coding\\VulkanSDK1.3.211.0\\Include" -L"C:\\Coding\\VulkanSDK1.3.211.0\\Lib" -L"C:\\Coding\\glfw-3.3.7\\lib-mingw-w64\\"  -lglfw3 -lvulkan-1 -lgdi32 -m64
GLSC = "C:\\Coding\\VulkanSDK1.3.211.0\\Bin\\glslc.exe"

## Directories
OBJ_DIR = ./build/obj
SRC_DIR = ./src

RENDER_DIR = ./src/render
WORLD_DIR = ./src/world

SOURCES = $(SRC_DIR)/main.cpp $(wildcard $(RENDER_DIR)/*.cpp) $(wildcard $(WORLD_DIR)/*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
EXPECTED_OBJECTS =  $(patsubst %.o, $(OBJ_DIR)/%.o, $(notdir $(OBJECTS)))

debug: CFLAGS += -g
debug: OUTPUT = -o ./build/output_debug.exe
debug: all

build: OUTPUT = -o ./build/output.exe
build: all

all: $(OBJECTS)
	$(CXX) $(CFLAGS) $(OUTPUT) $(EXPECTED_OBJECTS) $(LIBS)

$(OBJECTS): src/%.o : src/%.cpp
	$(CXX) $(CFLAGS) -c $< $(LIBS) -o $(OBJ_DIR)/$(@F)

hi:
	$(info $(EXPECTED_OBJECTS))