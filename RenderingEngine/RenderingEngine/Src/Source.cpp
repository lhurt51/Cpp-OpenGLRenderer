#include <iostream>
#include "3DEngine.h"
#include "FreeLook.h"
#include "FreeMove.h"

#define WIDTH 1920
#define HEIGHT 1080

class TestGame : public Game
{
public:

	TestGame() {}

	virtual void Init();

};

void TestGame::Init()
{
	GameObject* planeObject = new GameObject();
	GameObject* pointLightObject = new GameObject();
	GameObject* spotLightObject = new GameObject();
	GameObject* directionalLightObject = new GameObject();

	planeObject->AddComponent(new MeshRenderer(new Mesh("./Res/models/plane4.obj"), new Material(new Texture("bricks.jpg"), 0.5f, 4, new Texture("bricks_normal.jpg"), new Texture("bricks_disp.png"), 0.03f, -0.5f)));
	planeObject->GetTransform().SetPos(Vector3f(0, -1, 5));
	planeObject->GetTransform().SetScale(4.0f);

	pointLightObject->AddComponent(new PointLight(Vector3f(0, 1, 0), 0.4f, Attenuation(0, 0, 1)));
	pointLightObject->GetTransform().SetPos(Vector3f(7, 0, 7));

	spotLightObject->AddComponent(new SpotLight(Vector3f(0, 1, 1), 0.4f, Attenuation(0, 0, 0.02f), ToRadians(91.1f), 7, 0.0f));
	spotLightObject->GetTransform().Rotate(Quaternion(Vector3f(0, 1, 0), ToRadians(90.0f)));
	spotLightObject->GetTransform().Rotate(Quaternion(Vector3f(1, 0, 0), ToRadians(-60.0f)));
	spotLightObject->GetTransform().SetPos(Vector3f(10, 1.0f, 5));

	directionalLightObject->AddComponent(new DirectionalLight(Vector3f(1, 1, 1), 0.4f));

	GameObject* testMesh1 = new GameObject();
	GameObject* testMesh2 = new GameObject();

	testMesh1->AddComponent(new MeshRenderer(new Mesh("./Res/models/plane3.obj"), new Material(new Texture("bricks2.jpg"), 1, 8, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.jpg"), 0.04f, -1.0)));
	testMesh2->AddComponent(new MeshRenderer(new Mesh("./Res/models/plane3.obj"), new Material(new Texture("bricks2.jpg"), 1, 8, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.jpg"), 0.04f, -1.0)));

	testMesh1->GetTransform().SetPos(Vector3f(0, 2, 0));
	testMesh1->GetTransform().SetRot(Quaternion(Vector3f(0, 1, 0), 0.4f));
	testMesh1->GetTransform().SetScale(1.0f);

	testMesh2->GetTransform().SetPos(Vector3f(0, 0, 25));

	testMesh1->AddChild(testMesh2);

	AddToScene(planeObject);
	// AddToScene(pointLightObject);
	AddToScene(spotLightObject);
	// AddToScene(directionalLightObject);
	AddToScene(testMesh1);
	testMesh2->AddChild((new GameObject())->AddComponent(new Camera(Matrix4f().InitPerspective(ToRadians(70.0f), Window::GetAspect(), 0.1f, 1000.0f)))->AddComponent(new FreeLook())->AddComponent(new FreeMove()));

	directionalLightObject->GetTransform().SetRot(Quaternion(Vector3f(1, 0, 0), ToRadians(-45)));

	GameObject* box = new GameObject();
	box->AddComponent(new MeshRenderer(new Mesh("./Res/models/cube.obj"), new Material(new Texture("bricks2.jpg"), 1, 8, new Texture("bricks2_normal.png"), new Texture("bricks2_disp.jpg"), 0.04f, -1.0)));

	box->GetTransform().SetPos(Vector3f(14, 0, 5));
	box->GetTransform().SetRot(Quaternion(Vector3f(0, 1, 0), ToRadians(30.0f)));
	AddToScene(box);
}

int main(int argc, char* argv[])
{
	TestGame game;
	CoreEngine engine(WIDTH, HEIGHT, 60, &game);
	engine.CreateWindow("Ghost Engine");
	engine.Start();
	/*
	Display display(WIDTH, HEIGHT, "Ghost Engine");

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
		Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0))
	};

	unsigned int indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./Res/monkey3.obj");
	Shader shader("./Res/basicShader");
	Texture texture("./Res/bricks.jpg");
	Camera camera(glm::vec3(0, 0, 3), 90.0f, (float)WIDTH/(float)HEIGHT, 0.01f, 1000.0f);
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
		mesh2.Draw();
		display.Update();
		counter += 0.0001f;
	}
	*/
	return 0;
}
