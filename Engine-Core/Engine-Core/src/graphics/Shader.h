#pragma once

#include "../utils/fileUtils.h"
#include "../maths/Maths.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>


namespace engine
{
	namespace graphics
	{
		class Shader
		{
			private:
				GLuint m_ShaderID;
				const char *m_VertPath, *m_FragPath;
			public:
				Shader(const char* vertPath, const char* fragPath);
				~Shader();


				void setUniformMat4(const GLchar* name, const maths::mat4& matrix);
				
				void setUniform1i(const GLchar* name, int value);
				void setUniform1iv(const GLchar* name, int count, int* value);
				void setUniform1f(const GLchar* name, float value);
				void setUniform1fv(const GLchar* name, int count, float* value);
				void setUniform2f(const GLchar* name, const maths::vec2& vector);
				void setUniform3f(const GLchar* name, const maths::vec3& vector);
				void setUniform4f(const GLchar* name, const maths::vec4& vector);

				void enable() const;
				void disable() const;
			private:
				GLuint load();
				GLint getUniformLocation(const GLchar* name);
		};
	}
}