#include "MTSScene.h"
#include "MTSSceneManager.h"

void MTSScene::quit()
{
	release();
	if(MTSSceneManager::getCurrent() == this)
		MTSSceneManager::popState();
}

void MTSScene::addSubView(std::shared_ptr<MTSView> view_ptr)
{
	m_view->addSubView(view_ptr);
}

void MTSScene::render()
{
	m_view->render();
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
