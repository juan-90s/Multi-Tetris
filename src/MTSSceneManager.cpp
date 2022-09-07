#include "MTSSceneManager.h"

std::stack<std::unique_ptr<MTSScene>> MTSSceneManager::m_vecScene = {};

void MTSSceneManager::pushState(MTSScene* pScene)
{
	std::unique_ptr<MTSScene> smt_p(pScene);
	m_vecScene.push(std::move(smt_p));
}

void MTSSceneManager::changeState(MTSScene* pScene)
{
	m_vecScene.pop();

	std::unique_ptr<MTSScene> smt_p(pScene);
	m_vecScene.push(std::move(smt_p));
}

void MTSSceneManager::popState()
{
	m_vecScene.pop();
}

MTSScene* MTSSceneManager::getCurrent()
{
	return m_vecScene.top().get();
}
