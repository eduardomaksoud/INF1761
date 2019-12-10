#include "Application.h"

static Material red;
static Material green;
static Material blue;
static Material white;
static Material yellow;
static Material orange;

static SDL_Color whiteColor;
static SDL_Color redColor;
static SDL_Color blueColor;

static float speed = 1.2f;

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
	SceneSphere s2;

	PointLight l;

	scene = new Scene();
	scene->getMainCamera().setPosition(Vector3(0, 0, 0));

	// Initialize materials:
	red.setDiffuseColor(255, 0, 0);
	white.setDiffuseColor(255, 255, 255);
	green.setDiffuseColor(0, 255, 0);
	blue.setDiffuseColor(0, 0, 255);
	yellow.setDiffuseColor(255, 255, 0);
	orange.setDiffuseColor(255, 128, 0);

	//Initialize colors:
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 1;

	blueColor.r = 0;
	blueColor.g = 0;
	blueColor.b = 255;
	blueColor.a = 1;

	redColor.r = 255;
	redColor.g = 0;
	redColor.b = 0;
	redColor.a = 1;
	/*
	t1.material = &green;
	t1.vertexA = Vector3(-1, 2, 5);
	t1.vertexB = Vector3(2, 2, 5);
	t1.vertexC = Vector3(0, -1, 5);
	
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
	scene->addTriangle(t3);*/

	// Create Spheres:
	
	s1.material = &green;
	s1.center = Vector3(0,2,4);
	s1.radius = 1;
	scene->addSphere(s1);

	s2.material = &red;
	s2.center = Vector3(0,2,7);
	s2.radius = 2;
	scene->addSphere(s2);
	
	// Create Point Light
	l.color = whiteColor;
	l.intensity = 1;
	l.position = Vector3(0, 2, -5);
	scene->addLight(l);

	// Create Point Light
	l.color = blueColor;
	l.intensity = 1;
	l.position = Vector3(0, 2, 20);
	scene->addLight(l);
	
	/*Create Point Light
	l.color = whiteColor;
	l.intensity = 1;
	l.position = Vector3(5, 0, 6);
	scene->addLight(l);

	// Create Point Light
	l.color = whiteColor;
	l.intensity = 1;
	l.position = Vector3(-5, 0, 6);
	scene->addLight(l);*/
}

void Application::OnUpdate(float dt)
{
	Camera& cam = scene->getMainCamera();
	const Vector3& pos = cam.getPosition();
	
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
	//printf("fps: %f", 1 / dt);
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
	//Camera& cam = scene->getMainCamera();
	scene->getMainCamera().RotateY(dx / 1000);
	//scene->getMainCamera().RotateX(dy / 1000);
	//printf("(%f,%f)-(%f,%f)\n",dx,dy,cam.getLocalZAxis().y,cam.getLocalZAxis().z);
	
}

void Application::OnDraw()
{
	frame->setColor(0, 0, 0);
	frame->clear();
	scene->render(*frame);
	frame->renderPresent();
}