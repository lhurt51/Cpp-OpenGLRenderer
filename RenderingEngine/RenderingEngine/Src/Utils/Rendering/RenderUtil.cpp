#include "RenderUtil.h"
#include <GL/glew.h>

void RenderUtil::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::InitGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Choose the Front face in the engine
	// glFrontFace(GL_CW);
	// Choose which faces to cull
	glCullFace(GL_BACK);
	// Enable face culling
	glEnable(GL_CULL_FACE);
	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	// Enable a clamp on the depth test
	glEnable(GL_DEPTH_CLAMP);
}
