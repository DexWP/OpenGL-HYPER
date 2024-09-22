#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>


void callback_escape(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "Shaders", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Can not create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Can not get implementation from drivers" << std::endl;
		glfwTerminate();
		return -1;
	}


	float vertices[] =
	{
		//positions					//color
		-0.5f, -0.5f,  0.0f,		1.0f, 0.0f, 0.0f,
		 0.0f,  0.5f,  0.0f,		0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,		0.0f, 0.0f, 1.0f
	};

	const char* vertexPath =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"layout(location = 1) in vec3 aCol;\n"
		"out vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(aPos, 1.0f);\n"
		"ourColor = aCol;\n"
		"}\0";

	const char* fragmentPath =
		"#version 330 core\n"
		"out vec4 outColor;\n"
		"in vec3 ourColor;\n"
		"void main()\n"
		"{\n"
		"outColor = vec4(ourColor, 1.0f);\n"
		"}\0";

	unsigned int progID;
	unsigned int vertexShader, fragmentShader;

	progID = glCreateProgram();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexPath, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentPath, nullptr);
	glCompileShader(vertexShader);

	int  success;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
	}

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
	}

	glAttachShader(progID, vertexShader);
	glAttachShader(progID, fragmentShader);
	glLinkProgram(progID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);



	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		callback_escape(window);

		glUseProgram(progID);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}
