#include "MTSScene.h"
#include "MTSSceneManager.h"

void MTSScene::push(MTSScene* pScene)
{
	MTSSceneManager::pushState(pScene);
}

void MTSScene::jumpto(MTSScene* pScene)
{
	MTSSceneManager::changeState(pScene);
}
