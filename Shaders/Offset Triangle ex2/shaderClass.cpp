	#include "shaderClass.hpp"

	#include <glad/glad.h>

	#include <string>
	#include <fstream>
	#include <sstream>
	#include <iostream>


	Shader::Shader(const char* vertexPath, const char* fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (...)
		{
			std::cout << "Something wrong with stream" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		unsigned int vertex, fragment;
		vertex   = glCreateShader(GL_VERTEX_SHADER);
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(vertex,   1, &vShaderCode, nullptr);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
		glCompileShader(vertex);

		int success;
		char log_info[512];
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, log_info);
			std::cout << "ERROR OCCURED IN VERTEX SHADER" << std::endl;
		}

		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, log_info);
			std::cout << "ERROR OCCURED IN FRAGMENT SHADER" << std::endl;
		}

		programID = glCreateProgram();
		glAttachShader(programID, vertex);
		glAttachShader(programID, fragment);
		glLinkProgram(programID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}


	void Shader::use()
	{
		glUseProgram(programID);
	}


	void Shader::setBool(const std::string& name, bool value)	const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	}


	void Shader::setInt(const std::string& name, int value)		const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	}


	void Shader::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	}
