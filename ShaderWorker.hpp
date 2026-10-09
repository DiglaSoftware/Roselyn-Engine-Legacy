#ifndef SHADER_WORKER_HPP
#define SHADER_WORKER_HPP

#include <string>
#include <glm/glm.hpp>

namespace RoselynEngine {
	class ShaderWorker {
		public:
			ShaderWorker(const std::string& vertexShaderFile, const std::string& fragmentShaderFile, bool compile);
			~ShaderWorker();

			void CompileShaders();

			void Use();

			void SetInt(const std::string& name, int value);
			void SetFloat(const std::string& name, float value);
			void SetVec2(const std::string& name, glm::vec2& value);
			void SetVec3(const std::string& name, glm::vec3& value);
			void SetVec4(const std::string& name, glm::vec4& value);
			void SetMat4(const std::string& name, glm::mat4& value);

			unsigned int GetNative();

		private:
			const char* VertexShaderCode;
			const char* FragmentShaderCode;
			unsigned int ShaderProgram;

	};
}

#endif