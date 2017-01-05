//Ollie Williams 2017

#include "FreetypeWrapper.h"
namespace engine
{
	namespace graphics
	{
		namespace ftw
		{


			void FreetypeWrapper::Init(const char* font, int fontSize)
			{

				if (FT_Init_FreeType(&m_FTlib))
					std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

				if (FT_New_Face(m_FTlib, font, 0, &m_Face))
					std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

				FT_Set_Pixel_Sizes(m_Face, 0, fontSize);
			}


			void FreetypeWrapper::SetGlyph(char glyph)
			{
				if (FT_Load_Char(m_Face, glyph, FT_LOAD_RENDER))
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			}

			void FreetypeWrapper::LoadGlyphs()
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

				for (GLubyte c = 0; c < 128; c++)
				{
					// Load character glyph 
					if (FT_Load_Char(m_Face, c, FT_LOAD_RENDER))
					{
						std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
						continue;
					}
					// Generate texture
					GLuint texture;
					glGenTextures(1, &texture);
					glBindTexture(GL_TEXTURE_2D, texture);
					glTexImage2D(
						GL_TEXTURE_2D,
						0,
						GL_RED,
						m_Face->glyph->bitmap.width,
						m_Face->glyph->bitmap.rows,
						0,
						GL_RED,
						GL_UNSIGNED_BYTE,
						m_Face->glyph->bitmap.buffer
					);

					// Set texture options
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


					// Now store character for later use
					Character character = {
						texture,
						maths::vec2(m_Face->glyph->bitmap.width, m_Face->glyph->bitmap.rows),
						maths::vec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
						m_Face->glyph->advance.x
					};
					Characters.insert(std::pair<GLchar, Character>(c, character));

				}

			};

			void FreetypeWrapper::ReleaseFTData()
			{
				FT_Done_Face(m_Face);
				FT_Done_FreeType(m_FTlib);
			}
		}
	}
}