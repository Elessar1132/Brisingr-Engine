#include "Texture.h"

namespace engine
{
	namespace graphics
	{
		Texture::Texture(const std::string& filename)
			: m_Filename(filename)
		{
			m_TID = load();
		}

		Texture::~Texture()
		{

		}

		unsigned int Texture::load()
		{
			BYTE* pixels = load_image(m_Filename.c_str(), &m_Width, &m_Height);
			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			//delete[] pixels 

			return result;
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}