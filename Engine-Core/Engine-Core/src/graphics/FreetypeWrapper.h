//Ollie Williams 2017

#pragma once

#include <GL\glew.h>
#include "../maths/Maths.h"
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H  
namespace engine
{
	namespace graphics
	{
		namespace ftw
		{
			struct Character
			{
				GLuint     TextureID;  // ID handle of the glyph texture
				maths::vec2 Size;       // Size of glyph
				maths::vec2 Bearing;    // Offset from baseline to left/top of glyph
				GLuint     Advance;    // Offset to advance to next glyph
			};

			static std::map<GLchar, Character> Characters;


			class FreetypeWrapper
			{
			private:
				FT_Face m_Face;
				FT_Library m_FTlib;
			public:

				void Init(const char* font, int fontSize);
				void SetGlyph(char glyph);
				void LoadGlyphs();
				void ReleaseFTData();
			};
		}
	}
}