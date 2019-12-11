#include "Application.h"

static Material redMaterial;
static Material greenMaterial;
static Material blueMaterial;
static Material whiteMaterial;
static Material yellowMaterial;
static Material orangeMaterial;

static SDL_Color white;
static SDL_Color red;
static SDL_Color blue;

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

	SceneTriangle floorT2;

	SceneSphere s1;
	SceneSphere s2;
	SceneSphere s3;

	PointLight l;

	scene = new Scene();
	scene->getMainCamera().setPosition(Vector3(0, -2, -5));

	// Initialize materials:
	redMaterial.setDiffuseColor(255, 0, 0);
	whiteMaterial.setDiffuseColor(255, 255, 255);
	greenMaterial.setDiffuseColor(0, 255, 0);
	blueMaterial.setDiffuseColor(0, 0, 255);
	yellowMaterial.setDiffuseColor(255, 255, 0);
	orangeMaterial.setDiffuseColor(255, 128, 0);

	//Initialize colors:
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 1;

	blue.r = 0;
	blue.g = 0;
	blue.b = 255;
	blue.a = 1;

	red.r = 255;
	red.g = 0;
	red.b = 0;
	red.a = 1;
	
	/*t1.material = &greenMaterial;
	t1.vertexA = Vector3(-5, -1, 5);
	t1.vertexB = Vector3(15, -1, 5);
	t1.vertexC = Vector3(15, -1, -15);
	scene->addTriangle(t1);*/

	t1.material = &greenMaterial;
	t1.vertexA = Vector3(-7, -1, -7);
	t1.vertexB = Vector3(1, -1, -15);
	t1.vertexC = Vector3(-1, -1, -5);
	scene->addTriangle(t1);

	/*t2.material = &greenMaterial;
	t2.vertexA = Vector3(15, -1, -15);
	t2.vertexB = Vector3(-5, -1, 5);
	t2.vertexB = Vector3(-15, -1, -15);

	scene->addTriangle(t2);*/
	
	/*
	t2.material = &green;
	t2.vertexA = Vector3(-1,2,2);
	t2.vertexB = Vector3(2,2,10);
	t2.vertexC = Vector3(0,-1,3);

	t3.material = &blue;
	t3.vertexA = Vector3(-1, 2, 2);
	t3.vertexB = Vector3(2, 2, 5);
	t3.vertexC = Vector3(0, -1, 3);
	*/
	
	//scene->addTriangle(t2);
	//scene->addTriangle(t3);

	// Create Spheres:

	s1.material = &greenMaterial;
	s1.center = Vector3(-7,0.5,-8);
	s1.radius = 0.5;
	scene->addSphere(s1);

	s2.material = &blueMaterial;
	s2.center = Vector3(-2, 0, -9);
	s2.radius = 1;
	scene->addSphere(s2);

	s3.material = &redMaterial;
	s3.center = Vector3(-1, 0, -5);
	s3.radius = 0.4;
	scene->addSphere(s3);

	/*
	s2.material = &red;
	s2.center = Vector3(0,2,7);
	s2.radius = 2;
	scene->addSphere(s2);
	*/
	// Create Point Light
	//l.color = white;
	//l.intensity = 1;
	//l.position = Vector3(-3, 0, -10);
	//scene->addLight(l);

	/*l.color = white;
	l.intensity = 1;
	l.position = Vector3(1, 0, -8);
	scene->addLight(l);*/

	l.color = white;
	l.intensity = 1;
	l.position = Vector3(2.41, 0.12, -9.15);
	scene->addLight(l);

	l.color = blue;
	l.intensity = 1;
	l.position = Vector3(0, 0, 0);
	scene->addLight(l);

	/*l.color = white;
	l.intensity = 1;
	l.position = Vector3(-6.87, 0.40, -13.85);
	scene->addLight(l);*

	/*
	l.color = white;
	l.intensity = 1;
	l.position = Vector3(-0.77, 0.08, -0.26);
	scene->addLight(l);*/


	//Create Point Light
	//l.color = white;
	//l.intensity = 1;
	//l.position = Vector3(0, 1, 0);
	//scene->addLight(l);
	
	/*Create Point Light
	l.color = whiteColor;
	l.intensity = 1;
	l.position = Vector3(5, 0, 6);
	scene->addLight(l);

	//Create Point Light
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
	auto& camPos = scene->getMainCamera().getPosition();
	printf("fps: %.0f position: %.2f %.2f %.2f\n", 1 / dt, camPos.x, camPos.y, camPos.z);
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