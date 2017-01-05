#pragma once

#include "../Renderable2D.h"

namespace engine
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		public:
			std::vector<Renderable2D*> m_Renderables;
			maths::mat4 m_TransformationMatrix;
		public:
			Group(const maths::mat4& transform);
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
		};
	}
}