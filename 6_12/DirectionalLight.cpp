#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
	this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	this->type = 2;
}

DirectionalLight::DirectionalLight(glm::vec3 direction)
{
	this->direction = direction;
	this->type = 2;
}

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) : Light(color)
{
	this->direction = direction;
	this->type = 2;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

glm::vec3 DirectionalLight::getDirection()
{
	return this->direction;
}

DirectionalLight::~DirectionalLight()
{
	
}
