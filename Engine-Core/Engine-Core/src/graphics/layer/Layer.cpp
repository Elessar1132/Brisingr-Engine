#include "Layer.h"

namespace engine
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix)
			: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);
			//m_Shader->disable();
		}

		Layer::~Layer()
		{
			delete m_Shader;
			delete m_Renderer;

			for (int i = 0; i < m_Renderables.size(); i++)
			{
				delete m_Renderables[i];
			}
		}

		void Layer::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer::render()
		{
			m_Shader->enable();

			m_Renderer->begin();

			/*int i = 0;
			for (const Renderable2D* renderable : m_Renderables)
			{
				renderable->submit(m_Renderer);
			}*/

			m_Renderer->RenderText("This is sample text", maths::vec3(0,0,0), 1.0f, maths::vec4(0, 0, 0, 0));

			m_Renderer->end();

			m_Renderer->flush();
		}
	}
}