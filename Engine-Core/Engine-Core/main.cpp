#include <time.h>
#include "src\utils\Timer.h"

#include "src/graphics/Window.h"
#include "src/utils/fileUtils.h"
#include "src/maths/Maths.h"
#include "src/graphics/Shader.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

#include "src/graphics/Simple2DRenderer.h"
#include "src/graphics/BatchRenderer2D.h"
#include "src/graphics/Renderable2D.h"
#include "src/graphics/layer/TileLayer.h"


#include "src/graphics/Static_Sprite.h"
#include "src/graphics/Sprite.h"


#include "src/graphics/layer/Group.h"

#include "src\graphics\Texture.h"

#define BATCH_RENDERER 1
#define TEXTURE_RENDERED 0


int main()
{
	using namespace engine;
	using namespace graphics;
	using namespace maths;

	Window window("Brisingr!", 960, 540);

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	Texture* ta = new Texture("test.png");
	Texture* tb = new Texture("test1.png");
	Texture* tc = new Texture("test2.png");

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("test1.png"),
		new Texture("test2.png")
	};

	TileLayer layer(&shader);

	//Sprite* sp1 = new Sprite(2, 2, 0.9f, 0.9f, ta);
	//Sprite* sp2 = new Sprite(2, 3, 0.9f, 0.9f, tb);
	//Sprite* sp3 = new Sprite(2, 4, 0.9f, 0.9f, tc);
	//Sprite* sp4 = new Sprite(5, 4, 0.9f, 0.9f, vec4(1, 0, 0, 1));
	//layer.add(sp1);
	//layer.add(sp2);
	//layer.add(sp3);
	//layer.add(sp4);


	

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{

			if (rand() % 4 == 0)
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			}
			else
			{
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
			}

			
			
			
			//layer.add(new sprite(x, y, 0.9f, 0.9f, tb));
		}
	}


	int texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};



	shader.enable();
	shader.setUniform1iv("textures", 10, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));


#if TEXTURE_RENDERED 1
	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}
#endif



	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	shader.setUniform4f("col", vec4(0.2, 0.3, 0.8, 1.0));
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	while (!window.Closed())
	{
		window.Clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));
		
		layer.render();

		window.Update();
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);

			frames = 0;
		}
	}
	//system("PAUSE");
	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}
	return 0;
}

#if 0
int main()
{
	const char* filename = "test.png";

	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return false;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	unsigned int bitsPerPixel = FreeImage_GetBPP(dib);
	unsigned int pitch = FreeImage_GetPitch(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	for (int x = 0; x < width; x++)
	{
		BYTE *pixel = (BYTE*)bits;
		for (int y = 0; y < width; y++)
		{
			std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
			pixel += 3;
		}
		bits += pitch;
	}
	FreeImage_Unload(dib);

	return 0;
}
#endif