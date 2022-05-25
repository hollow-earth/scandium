CXX = g++
CFLAGS = 
BUILDDIR = ./build/
SRC = ./src/
LIBS = -I"C:\\Coding\\glfw-3.3.7\\include" -I"C:\\Coding\\VulkanSDK1.3.211.0\\Include" -L"C:\\Coding\\VulkanSDK1.3.211.0\\Lib" -L"C:\\Coding\\glfw-3.3.7\\lib-mingw-w64\\"  -lglfw3 -lvulkan-1 -lgdi32 -m64
OUTPUT =

debug: CFLAGS += -g
debug: OUTPUT = -o $(BUILDDIR)output_debug.exe
debug: all

build: OUTPUT = -o $(BUILDDIR)output.exe
build: all

all: main.o renderer.o application.o pipeline.o worldgen.o
	$(CXX) $(CFLAGS) $^ $(OUTPUT) $(LIBS) 

main.o: $(SRC)main.cpp
	$(CXX) $(CFLAGS) -c $< $(LIBS)

renderer.o: $(SRC)renderer.cpp $(SRC)renderer.h
	$(CXX) $(CFLAGS) -c $< $(LIBS)

application.o: $(SRC)application.cpp $(SRC)application.h
	$(CXX) $(CFLAGS) -c $< $(LIBS)

pipeline.o: $(SRC)pipeline.cpp $(SRC)pipeline.h
	$(CXX) $(CFLAGS) -c $< $(LIBS)

engine_device.o: $(SRC)engine_device.cpp $(SRC)engine_device.h
	$(CXX) $(CFLAGS) -c $< $(LIBS)

worldgen.o: $(SRC)worldgen.cpp $(SRC)worldgen.h
	$(CXX) $(CFLAGS) -c $< $(LIBS)

clean:
	del /F *.o
