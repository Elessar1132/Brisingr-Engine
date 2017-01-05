#pragma once

#include "Layer.h";


namespace engine
{
	namespace graphics
	{
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			virtual ~TileLayer();
		};
	}
}