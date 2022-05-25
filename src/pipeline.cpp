#include "pipeline.h"

#include <fstream>
#include <iostream>
#include <stdexcept>


namespace scandium{

	ScandiumPipeline::ScandiumPipeline(const std::string& vertFilepath, const std::string& fragFilepath){
		createGraphicsPipeline(vertFilepath, fragFilepath);
	}

	std::vector<char> ScandiumPipeline::readFile(const std::string& filepath){
		std::ifstream file{filepath, std::ios::ate | std::ios::binary};			//std::ios::ate reads the file and puts the cursor at the end
		
		if (!file.is_open()){
			throw std::runtime_error("failed to open file: " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());					//cursor is at the end of the file so we can get the filesize
		std::vector<char> buffer(fileSize);

		file.seekg(0);															//return cursor to start of file
		file.read(buffer.data(), fileSize);										//read from cursorpos 0 to fileSize
		
		file.close();
		return buffer;
	}

	void ScandiumPipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath){
		auto vertCode = readFile(vertFilepath);
		auto fragCode = readFile(fragFilepath);

		std::cout << "Vertex shader code size: " << vertCode.size() << "\nFragment shader code size: " 
		<< fragCode.size() << "\n";
	}
}