#include "Application.h"

static Material red;
static Material green;
static Material blue;

static float speed = 0.4f;

static bool movingUp = false;
static bool movingBack = false;
static bool movingRight = false;
static bool movingLeft = false;

Application::Application(RenderingFrame* rf)
{
	frame = rf;
}

void Application::OnStart()
{
	SceneTriangle t1;
	SceneTriangle t2;
	SceneTriangle t3;

	scene = new Scene();
	scene->getMainCamera().setPosition(Vector3(0, 0, 0));

	// Initialize materials:
	red.setColor(255, 0, 0);
	green.setColor(0, 255, 0);
	blue.setColor(0, 0, 255);

	// Create triangles:
	t1.material = &red;
	t1.vertexA = Vector3(-2, 2, 7);
	t1.vertexB = Vector3(2, 3, 7);
	t1.vertexC = Vector3(0, 0, 7);

	t2.material = &green;
	t2.vertexA = Vector3(-1,2,2);
	t2.vertexB = Vector3(2,2,10);
	t2.vertexC = Vector3(0,-1,3);

	t3.material = &blue;
	t3.vertexA = Vector3(-1, 2, 2);
	t3.vertexB = Vector3(2, 2, 5);
	t3.vertexC = Vector3(0, -1, 3);

	scene->addTriangle(t1);
	scene->addTriangle(t2);
	scene->addTriangle(t3);
}

void Application::OnUpdate(float dt)
{
	Camera& cam = scene->getMainCamera();
	Vector3 pos = cam.getPosition();

	if (movingUp)
	{
		cam.setPosition(pos + cam.getLocalZAxis() * speed * dt);
	}
	if (movingBack)
	{
		cam.setPosition(pos - cam.getLocalZAxis() * speed * dt);
	}
}

void Application::OnKeyPressed(SDL_Keycode kc)
{
	switch (kc)
	{
	case SDLK_w:
		movingUp = true;
		break;

	case SDLK_s:
		movingBack = true;
		break;
	}
}

void Application::OnKeyReleased(SDL_Keycode kc)
{
	switch (kc)
	{
	case SDLK_w:
		movingUp = false;
		break;

	case SDLK_s:
		movingBack = false;
		break;
	}
}

void Application::OnMouseMove(float dx, float dy)
{

}

void Application::OnDraw()
{
	frame->setColor(0, 0, 0);
	frame->clear();
	scene->render(*frame);
	frame->renderPresent();
}