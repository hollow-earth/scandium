CXX = g++
CFLAGS = 
BUILDDIR = ./build/
SRC = ./src/
LIBS = -I"C:\\Coding\\glfw-3.3.7\\include" -I"C:\\Coding\\VulkanSDK1.3.211.0\\Include" -L"C:\\Coding\\VulkanSDK1.3.211.0\\Lib" -L"C:\\Coding\\glfw-3.3.7\\lib-mingw-w64\\"  -lglfw3 -lvulkan-1 -lgdi32 -m64
GLSC = "C:\\Coding\\VulkanSDK1.3.211.0\\Bin\\glslc.exe"
OUTPUT =


debug: CFLAGS += -g
debug: OUTPUT = -o $(BUILDDIR)output_debug.exe
debug: all

build: OUTPUT = -o $(BUILDDIR)output.exe
build: all

all: main.o renderer.o application.o pipeline.o worldgen.o engine_device.o scandium_swapchain.o scandium_model.o
	$(CXX) $(CFLAGS) $^ $(OUTPUT) $(LIBS) 

main.o: $(SRC)main.cpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

renderer.o: $(SRC)renderer.cpp $(SRC)renderer.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

application.o: $(SRC)application.cpp $(SRC)application.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

pipeline.o: $(SRC)pipeline.cpp $(SRC)pipeline.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

engine_device.o: $(SRC)engine_device.cpp $(SRC)engine_device.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

worldgen.o: $(SRC)worldgen.cpp $(SRC)worldgen.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

scandium_swapchain.o: $(SRC)scandium_swapchain.cpp $(SRC)scandium_swapchain.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

scandium_model.o: $(SRC)scandium_model.cpp $(SRC)scandium_model.hpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

shaders: ./shaders/simple_shader.vert ./shaders/simple_shader.frag
	$(GLSC) ./shaders/simple_shader.vert -o ./shaders/simple_shader.vert.spv
	$(GLSC) ./shaders/simple_shader.frag -o ./shaders/simple_shader.frag.spv

clean:
	del /F *.o
