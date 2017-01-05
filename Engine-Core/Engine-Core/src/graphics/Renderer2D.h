#pragma once

#include <GL/glew.h>
#include <vector>
#include "../maths/maths.h"


namespace engine
{
	namespace graphics
	{
		class Renderable2D;
		class Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_TransformationStack;
			const maths::mat4* m_TransformationBack;
		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(maths::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}
		public:
			void push(maths::mat4 matrix, bool override = false)
			{
				if (override)
				{
					m_TransformationStack.push_back(matrix);
				}
				else
				{
					m_TransformationStack.push_back(m_TransformationStack.back() *matrix);
					m_TransformationBack = &m_TransformationStack.back();
				}
			}

			void pop()
			{
				if (m_TransformationStack.size() > 1)
				{
					m_TransformationStack.pop_back();
				}
				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void RenderText(std::string text, maths::vec3 position, float scale, maths::vec4 color) {}
			virtual void end() {}
			virtual void flush() = 0;
		};

	}
}