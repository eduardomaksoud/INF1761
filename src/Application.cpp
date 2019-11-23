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
	scene = new Scene();

	// Initialize materials:
	red.setColor(255, 0, 0);
	green.setColor(0, 255, 0);
	blue.setColor(0, 0, 255);

	// Create triangles:
	SceneTriangle t1; 
	t1.material = &red;
	t1.vertexA = Vector3(-2, 2, 4);
	t1.vertexB = Vector3(2, 2, 4);
	t1.vertexC = Vector3(0, -0, 4);

	scene->AddTriangle(t1);
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

	printf("fps: %.2f\n", (1 / dt));

	//cam.RotateY(2.5 * dt);

	//printf("Camera pos: (%f, %f, %f)\n", pos.x, pos.y, pos.z);
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