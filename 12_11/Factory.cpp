#include "Factory.h"

Factory* Factory::instance = 0;

Factory* Factory::GetInstance()
{
	if (!instance)
	{
		instance = new Factory();
	}

	return instance;
}

Factory::Factory()
{
	models["sphere"] = new Model(sphere, sizeof(sphere) / sizeof(sphere[0]));
	models["suziFlat"] = new Model(suziFlat, sizeof(suziFlat) / sizeof(suziFlat[0]));
	models["suziSmooth"] = new Model(suziSmooth, sizeof(suziSmooth) / sizeof(suziSmooth[0]));
	models["plain"] = new Model(plain, sizeof(plain) / sizeof(plain[0]));
	models["gift"] = new Model(gift, sizeof(gift) / sizeof(gift[0]));
	models["bushes"] = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]));
	models["tree"] = new Model(tree, sizeof(tree) / sizeof(tree[0]));
	
}

DrawableObject* Factory::createObject(int shaderType, int modelType, glm::mat4 transformationMatrix)
{
	const char* vertex;
	const char* fragment;

	switch (shaderType) {
	case 1:
		vertex = "LambertShader.vert";
		fragment = "LambertShader.frag";
		break;
	case 2:
		vertex = "PhongShader.vert";
		fragment = "PhongShader.frag";
		break;
	case 3:
		vertex = "BlinnPhongShader.vert";
		fragment = "BlinnPhongShader.frag";
		break;
	default:
		vertex = "ConstantShader.vert";
		fragment = "ConstantShader.frag";
	}
	

	switch (modelType)
	{
		// sphere
	case 1:
		return new DrawableObject(models.find("sphere")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// suziFlat
	case 2:
		return new DrawableObject(models.find("suziFlat")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// suziSmooth
	case 3:
		return new DrawableObject(models.find("suziSmooth")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// plain
	case 4:
		return new DrawableObject(models.find("plain")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// gift
	case 5:
		return new DrawableObject(models.find("gift")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// bushes
	case 6:
		return new DrawableObject(models.find("bushes")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
		// tree
	case 7:
		return new DrawableObject(models.find("tree")->second, new ShaderProgram(fragment, vertex), new Transformation(transformationMatrix));
		break;
	}
}

DrawableObject* Factory::createObjectTexture(glm::mat4 transformationMatrix, const char* textureName)
{
	const float plain_texture[] = {
		//vrchol, norm�la, uv sou�adnice
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
		1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,

	   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
	   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};


	return new DrawableObject(new Model(plain_texture, sizeof(plain_texture) / sizeof(plain_texture[0]), 1), new ShaderProgram("TextureShader.frag", "TextureShader.vert"), new Transformation(transformationMatrix), textureName);
}

Scene* Factory::createSpheresScene()
{
	Scene* scene = new Scene();
	scene->setCamera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))));
	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))));
	
	return scene;
}
Scene* Factory::createOneSphereScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))));

	return scene;
}
Scene* Factory::createMultipleObjectsScene()
{
	Scene* scene = new Scene();
	scene->getCamera()->setCamera(glm::vec3(-10.0f, 5.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObject(0, 1, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createObject(1, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 2.0f))));
	scene->addDrawableObject(this->createObject(2, 1, glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f))));
	scene->addDrawableObject(this->createObject(3, 1, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f))));

	srand(time(NULL));
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 4 + 0;	
		scene->addDrawableObject(this->createObject(rand_shader, 7, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand()% 100), 0.0f, 0.0f + (rand()% 100)))));
		scene->addDrawableObject(this->createObject(rand_shader, 6, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand() % 100), 0.0f, 0.0f + (rand() % 100)))));
	}
	for (int i = 0; i <= 100; i++)
	{
		int rand_shader = rand() % 4 + 0;
		int rand_model = rand() % 5 + 1;
		scene->addDrawableObject(this->createObject(rand_shader, rand_model, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f + (rand()% 100), 0.0f, 0.0f + (rand()% 100)))));
	}

	return scene;
}

Scene* Factory::createTextureScene()
{
	Scene* scene = new Scene();
	scene->setCamera(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	scene->addDrawableObject(this->createObjectTexture(glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)),"test.png"));
	scene->addDrawableObject(this->createObjectTexture(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 3.0f)), "test.png"));

	return scene;
}
