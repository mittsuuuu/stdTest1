#include "SceneManager.hpp"
#include "Title.h"

SceneManager::SceneManager() :
	mScene(Title())
{}

SceneManager::~SceneManager()
{
	delete mScene;
}

void SceneManager::update()
{
	Scene* p = mScene->update();
	if (p != mScene)
	{
		delete mScene;
		mScene = p;
	}
}

void SceneManager::draw() const
{
	mScene->draw();
}