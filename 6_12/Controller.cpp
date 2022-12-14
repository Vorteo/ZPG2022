#include "Controller.h"

Controller* Controller::instance = 0;

Controller* Controller::getInstance()
{
	if (!instance)
	{
		instance = new Controller();
	}

	return instance;
}

void Controller::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Controller::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		printf("space \n");
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Application::getInstance()->getScene()->getCamera()->toFront();
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Application::getInstance()->getScene()->getCamera()->toBack();
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Application::getInstance()->getScene()->getCamera()->toLeft();
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Application::getInstance()->getScene()->getCamera()->toRight();
	}

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Controller::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Controller::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Controller::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Controller::cursor_callback(GLFWwindow* window, double x, double y)
{
	
	if (Application::getInstance()->getRightClick() == 1)
	{
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		Application::getInstance()->getScene()->getCamera()->mouseMove(x,y,width, height);
	}

	printf("cursor_callback [%.1f,%.1f] \n", x, y);
	
}

void Controller::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		Application::getInstance()->setRightClick(1);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		Application::getInstance()->setRightClick(0);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		// ziskat aktualni polohu kam kliknul kurzor
		double cur_x, cur_y;
		glfwGetCursorPos(window, &cur_x, &cur_y);

		GLint x = (GLint)cur_x;
		GLint y = (GLint)cur_y;

		// ziskat velikost okna width a height
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		int new_y = h - y;

		// tam kde jsem kliknul, tak precist barvu, depth a id objektu
		glReadPixels(x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, new_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
		
		glm::vec3 screenX = glm::vec3(x, new_y, depth);
		glm::mat4 view = Application::getInstance()->getCamera()->getCamera();
		glm::mat4 projection = Application::getInstance()->getCamera()->getProjectionMatrix();
		glm::vec4 viewPort = glm::vec4(0, 0, w, h);

		// unproject prevod bodu z screen space do lokalnich
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		Application::getInstance()->factory->addTreeOnPosition(Application::getInstance()->getScene(), pos);
	}

	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

}
