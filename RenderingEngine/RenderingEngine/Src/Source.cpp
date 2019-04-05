#include <iostream>
#include "Display.h"
#include "Shader.h"

int main(int argc, char* argv[])
{
	Display display(1280, 720, "Ghost Engine");

	Shader shader("./Res/basicShader");

	while (!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		shader.Bind();

		display.Update();
	}
	return 0;
}