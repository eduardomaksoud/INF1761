#include "Application.h"

static Material red;
static Material green;
static Material blue;
static Material yellow;
static Material orange;

static float speed = 0.4f;

static bool movingForward = false;
static bool movingBack = false;
static bool movingRight = false;
static bool movingLeft = false;
static bool movingUp = false;
static bool movingDown = false;

Application::Application(RenderingFrame* rf)
{
	frame = rf;
}

void Application::OnStart()
{
	SceneTriangle t1;
	SceneTriangle t2;
	SceneTriangle t3;

	SceneSphere s1;

	scene = new Scene();
	scene->getMainCamera().setPosition(Vector3(0, 0, 0));

	// Initialize materials:
	red.setColor(255, 0, 0);
	green.setColor(0, 255, 0);
	blue.setColor(0, 0, 255);
	yellow.setColor(255, 255, 0);
	orange.setColor(255, 128, 0);

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

	// Create Spheres:

	s1.material = &orange;
	s1.center = Vector3(0, 0,7);
	s1.radius = 1;
	scene->addSphere(s1);

}

void Application::OnUpdate(float dt)
{
	Camera& cam = scene->getMainCamera();
	Vector3 pos = cam.getPosition();
	
	if (movingForward)
	{
		cam.setPosition(pos + cam.getLocalZAxis() * speed * dt);
	}
	if (movingBack)
	{
		cam.setPosition(pos - cam.getLocalZAxis() * speed * dt);
	}
	if (movingRight)
	{
		cam.setPosition(pos + cam.getLocalXAxis() * speed * dt);
	}
	if (movingLeft)
	{
		cam.setPosition(pos - cam.getLocalXAxis() * speed * dt);
	}
	if (movingUp)
	{
		cam.setPosition(pos + cam.getLocalYAxis() * speed * dt);
	}
	if (movingDown)
	{
		cam.setPosition(pos - cam.getLocalYAxis() * speed * dt);
	}
}

void Application::OnKeyPressed(SDL_Keycode kc)
{
	switch (kc)
	{
	case SDLK_w:
		movingForward = true;
		break;

	case SDLK_s:
		movingBack = true;
		break;

	case SDLK_a:
		movingLeft = true;
		break;

	case SDLK_d:
		movingRight = true;
		break;

	case SDLK_SPACE:
		movingUp = true;
		break;

	case SDLK_LSHIFT:
		movingDown = true;
		break;
	}
}

void Application::OnKeyReleased(SDL_Keycode kc)
{
	switch (kc)
	{
	case SDLK_w:
		movingForward = false;
		break;

	case SDLK_s:
		movingBack = false;
		break;

	case SDLK_a:
		movingLeft = false;
		break;

	case SDLK_d:
		movingRight = false;
		break;

	case SDLK_SPACE:
		movingUp = false;
		break;

	case SDLK_LSHIFT:
		movingDown = false;
		break;
	}
}

void Application::OnMouseMove(float dx, float dy)
{
	scene->getMainCamera().RotateY(dx / 1000);
}

void Application::OnDraw()
{
	frame->setColor(0, 0, 0);
	frame->clear();
	scene->render(*frame);
	frame->renderPresent();
}