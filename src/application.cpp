#include "application.h"

namespace scandium{

	void Application::run(){
		while(!renderWindow.shouldClose()){
			glfwPollEvents();
		}
	}


}