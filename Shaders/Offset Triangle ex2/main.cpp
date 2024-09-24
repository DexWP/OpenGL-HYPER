#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.hpp"

#include <iostream>

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(600, 600, "WIndow", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return  -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		return -2;
	}

	Shader shader("vertexShader.txt", "fragmentShader.txt");


	float vertices[] =
	{
		-0.5f, -0.5f,  0.0f,
		 0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
	};

	float colors[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	unsigned int VBO_points, VBO_colors;
	glGenBuffers(1, &VBO_points);
	glGenBuffers(1, &VBO_colors);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		
		float offset = 0.5;
		shader.setFloat("offset", offset);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}
