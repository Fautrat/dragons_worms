#include "Scene.hpp"

Scene::Scene(Engine& Engine)
	: engine(&Engine)
{

}

Scene::~Scene() = default;

Engine& Scene::getParentEngine() const
{
	return *engine;
}