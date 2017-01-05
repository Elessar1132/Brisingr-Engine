#pragma once

#include "Renderable2D.h"

namespace engine
{
	namespace graphics
	{
		class Label : Renderable2D
		{
		private:
			std::string m_Text;
		public:
			Label(std::string text, float x, float y, maths::vec4 color);
			void submit(Renderer2D* renderer) const override;
		};
	}
}