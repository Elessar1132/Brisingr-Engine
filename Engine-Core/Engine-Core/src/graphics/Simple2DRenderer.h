#pragma once

#include <deque>
#include "Renderer2D.h"
#include "Static_Sprite.h"
#include "Renderable2D.h"

namespace engine
{
	namespace graphics
	{
		class Simple2DRenderer : public Renderer2D
		{
		private:
			std::deque<const Static_Sprite*> m_RenderQueue;

		public:
			void submit(const Renderable2D* renderable) override;
			void flush() override;
		};

	}
}