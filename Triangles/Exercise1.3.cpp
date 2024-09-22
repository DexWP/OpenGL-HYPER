#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void escape_callback(GLFWwindow* window, int width, int height)
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


	GLFWwindow* window = glfwCreateWindow(600, 600, "Hello Triangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Can not create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Can not load glad" << std::endl;
		glfwTerminate();
		return -1;
	}


	float vertices_first[] =
	{
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};

	float vertices_second[] =
	{
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout(location = 0) in vec3 InputVertex;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(InputVertex, 1.0f);\n"
		"}\0";

	const char* fragmentShaderSource1 = 
		"#version 330 core\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"outColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";

	const char* fragmentShaderSource2 =
		"#version 330 core\n"
		"out vec4 outColor;\n"
		"void main()\n"
		"{\n"
		"outColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\0";


	unsigned int VBO_first;
	glGenBuffers(1, &VBO_first);
	unsigned int VBO_second;
	glGenBuffers(1, &VBO_second);

	unsigned int VAO_first;
	glGenVertexArrays(1, &VAO_first);
	glBindVertexArray(VAO_first);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_first);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_first), vertices_first, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	unsigned int VAO_second;
	glGenVertexArrays(1, &VAO_second);
	glBindVertexArray(VAO_second);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_second);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_second), vertices_second, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	unsigned int vertexShader;
	unsigned int shaderProgram1;
	unsigned int shaderProgram2;
	unsigned int fragmentShader1;
	unsigned int fragmentShader2;

	vertexShader    = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader,    1, &vertexShaderSource,    nullptr);
	glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, nullptr);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, nullptr);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader1);
	glCompileShader(fragmentShader2);

	shaderProgram1 = glCreateProgram();
	shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader2);


	glClearColor(0, 0, 0, 1);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO_first);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shaderProgram2);
		glBindVertexArray(VAO_second);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


}
