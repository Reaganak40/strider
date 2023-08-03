#pragma once
#include "core.h"
#include "mathTypes.h"

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>


namespace core {

	typedef unsigned int ShaderID;
	typedef int UniformVariable;

	unsigned int CompileShader(unsigned int type, const std::string& source);

	ShaderID CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	inline void BindShader(ShaderID program) { glUseProgram(program); }

	UniformVariable GetUniformVariable(ShaderID id, const std::string& name);

	void SetUniform4f(UniformVariable uv, float v0, float v1, float v2, float v3);
	void SetUniform1i(UniformVariable uv, int v0);
	void SetUniformMat4f(UniformVariable uv, glm::mat4 matrix);

	class Shader {
	private:
		ShaderID m_ID;
		std::string vertexShader;
		std::string fragmentShader;

		std::unordered_map <const char *, UniformVariable> m_uniforms;

	public:
		Shader(const std::string& nVertexShader, const std::string& nFragmentShader);
		~Shader();

		template<typename DataType>
		void SetUniform(const char* uniformName, DataType data) {}

		template<>
		void SetUniform<Strider::vec4f>(const char* uniformName, Strider::vec4f data) {
			
			if (m_uniforms.find(uniformName) == m_uniforms.end()) {
				m_uniforms[uniformName] = GetUniformVariable(m_ID, uniformName);
			}

			glUniform4f(m_uniforms[uniformName], data.v0, data.v1, data.v2, data.v3);
		}

		template<>
		void SetUniform<glm::mat4>(const char* uniformName, glm::mat4 data) {

			if (m_uniforms.find(uniformName) == m_uniforms.end()) {
				m_uniforms[uniformName] = GetUniformVariable(m_ID, uniformName);
			}

			glUniformMatrix4fv(m_uniforms[uniformName], 1, GL_FALSE, &data[0][0]);
		}

		inline void Bind() { glUseProgram(m_ID); }

		inline ShaderID GetID() { return m_ID; }
	};

	class ShaderManager {
	private:
		std::unordered_map<const char*, std::shared_ptr<Shader>> m_shaders;
	public:
		ShaderManager() {}

		void AddShader(const char* shaderName, std::shared_ptr<Shader> shaderPtr);
		std::shared_ptr<Shader> GetShader(const char* shaderName);
	};
}