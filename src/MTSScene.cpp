#include "MTSScene.h"
#include "MTSSceneManager.h"

void MTSScene::quit()
{
	release();
	if(MTSSceneManager::getCurrent() == this)
		MTSSceneManager::popState();
}

void MTSScene::push(MTSScene* pScene)
{
	pScene->init();
	MTSSceneManager::pushState(pScene);
}

void MTSScene::jumpto(MTSScene* pScene)
{
	MTSSceneManager::changeState(pScene);
}
