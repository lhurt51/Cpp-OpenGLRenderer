#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char* argv[])
{
	Display display(WIDTH, HEIGHT, "Ghost Engine");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
	};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./Res/basicShader");
	Texture texture("./Res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, 2), 90.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
	Transform transform;

	float counter = 0.0f;

	while (!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter * 0.5);

		transform.GetPos().x = sinCounter;
		transform.GetPos().z = cosCounter;
		transform.GetRot().x = counter;
		transform.GetRot().y = counter;
		transform.GetRot().z = counter;
		// transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh.Draw();
		display.Update();
		counter += 0.0001f;
	}
	return 0;
}