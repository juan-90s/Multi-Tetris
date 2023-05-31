#include "MTSSceneManager.h"

std::stack<std::unique_ptr<MTSScene>> MTSSceneManager::m_stackScene = {};

void MTSSceneManager::pushState(MTSScene* pScene)
{
	std::unique_ptr<MTSScene> smt_p(pScene);
	m_stackScene.push(std::move(smt_p));
}

void MTSSceneManager::changeState(MTSScene* pScene)
{
	m_stackScene.pop();

	std::unique_ptr<MTSScene> smt_p(pScene);
	m_stackScene.push(std::move(smt_p));
}

void MTSSceneManager::popState()
{
	m_stackScene.pop();
}

MTSScene* MTSSceneManager::getCurrent()
{
	if (m_stackScene.empty())
		return nullptr;
	else
		return m_stackScene.top().get();
}
