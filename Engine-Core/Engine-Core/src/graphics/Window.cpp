#include "Window.h"

namespace engine
{
	namespace graphics
	{
		void window_resize(GLFWwindow *window, int width, int height);

		Window::Window(const char *title, unsigned int width, unsigned int height)
		{
			m_Title = title;
			m_Height = height;
			m_Width = width;
			if (!Init())
			{
				glfwTerminate();
			}

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::Init()
		{
			if(!glfwInit())
			{
				std::cout << "Failed to initialize GLFW" << std::endl;
				return false;
			}
			
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window)
			{
				std::cout << "Failed to create the GLFW window" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSwapInterval(0);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}
			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			//Log this error.
			if (keycode >= MAX_KEYS)
			{
				return false;
			}
			else
			{
				return m_Keys[keycode];
			}
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			//Log this error.
			if (button >= MAX_BUTTONS)
			{
				return false;
			}
			else
			{
				return m_MouseButtons[button];
			}
		}

		void Window::getMousePosition(double &x, double &y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}


		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update() 
		{
			GLenum error = glGetError();

			if (error != GL_NO_ERROR)
			{
				std::cout << "OpenGL Error: " << error << std::endl;
			}

			glfwPollEvents();
			glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glfwSwapBuffers(m_Window);
		}

		bool Window::Closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}


		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}
		
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}


		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseX = xpos;
			win->m_MouseY = ypos;
		}

	}
}