#include "ShaderWorker.hpp"
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RoselynEngine {
	ShaderWorker::ShaderWorker(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, bool compile) {
		std::string VertexShaderSource = "";
		std::string FragmentShaderSource = "";

		std::ifstream VertexShaderFile;
		std::ifstream FragmentShaderFile;

		// reading vertex shader source file
		VertexShaderFile.open(vertexShaderFile);
		if (VertexShaderFile.good()) {
			std::string temp;
			while (getline(VertexShaderFile, temp)) { VertexShaderSource.append(temp.append("\n")); }
		}
		else {
			std::cout << "ROSELYN::SHADER_WORKER | Failed to read vertex shader" << std::endl;
			return;
		}
		VertexShaderFile.close();

		// reading fragment shader source file
		FragmentShaderFile.open(fragmentShaderFile);
		if (FragmentShaderFile.good()) {
			std::string temp;
			while (getline(FragmentShaderFile, temp)) { FragmentShaderSource.append(temp.append("\n")); }
		}
		else {
			std::cout << "ROSELYN::SHADER_WORKER | Failed to read fragment shader" << std::endl;
			return;
		}
		FragmentShaderFile.close();
		
		this->VertexShaderCode = VertexShaderSource.c_str();
		this->FragmentShaderCode = FragmentShaderSource.c_str();

		if (!compile) return; // exit if compilation is deferred

		CompileShaders();
	}

	ShaderWorker::~ShaderWorker() {
		glDeleteProgram(this->ShaderProgram);
	}

	void ShaderWorker::CompileShaders() {
		int Success;
		char InfoLog[512];

		unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VertexShader, 1, &this->VertexShaderCode, NULL);
		glCompileShader(VertexShader);
		glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Success);
		if (!Success) {
			glGetShaderInfoLog(VertexShader, 512, NULL, InfoLog);
			std::cout << "ROSELYN::SHADER_WORKER | Vertex shader compilation failure:\n" << InfoLog << std::endl;
		}

		unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FragmentShader, 1, &this->FragmentShaderCode, NULL);
		glCompileShader(FragmentShader);
		glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Success);
		if (!Success) {
			glGetShaderInfoLog(FragmentShader, 512, NULL, InfoLog);
			std::cout << "ROSELYN::SHADER_WORKER | Fragment shader compilation failure:\n" << InfoLog << std::endl;
		}

		unsigned int ShaderProgram = glCreateProgram();
		glAttachShader(ShaderProgram, VertexShader);
		glAttachShader(ShaderProgram, FragmentShader);
		glLinkProgram(ShaderProgram);
		glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
		if (!Success) {
			glGetProgramInfoLog(ShaderProgram, 512, NULL, InfoLog);
			std::cout << "ROSELYN:SHADER_WORKER | Shader Program linking failure:\n" << InfoLog << std::endl;
		}

		this->ShaderProgram = ShaderProgram;

		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);
	}

	unsigned int ShaderWorker::GetNative() {
		return this->ShaderProgram;
	}

	void ShaderWorker::Use() {
		glUseProgram(this->ShaderProgram);
	}

	void ShaderWorker::SetInt(const std::string& name, int value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform1i(Uniform, value);
	}

	void ShaderWorker::SetFloat(const std::string& name, float value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform1f(Uniform, value);
	}

	void ShaderWorker::SetVec2(const std::string& name, glm::vec2 &value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform2f(Uniform, value.x, value.y);
	}

	void ShaderWorker::SetVec3(const std::string& name, glm::vec3 &value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform3f(Uniform, value.x, value.y, value.z);
	}

	void ShaderWorker::SetVec4(const std::string& name, glm::vec4 &value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniform4f(Uniform, value.x, value.y, value.z, value.w);
	}

	void ShaderWorker::SetMat4(const std::string& name, glm::mat4 &value) {
		int Uniform = glGetUniformLocation(this->ShaderProgram, name.c_str());
		glUniformMatrix4fv(Uniform, 1, false, glm::value_ptr(value));
	}
}