#pragma once
#include "MTSScene.h"
#include <stack>
#include <memory>

class MTSSceneManager
{
public:
	static void pushState(MTSScene* pScene);
	static void changeState(MTSScene* pScene);
	static void popState();
	static MTSScene* getCurrent();
private:
	static std::stack<std::unique_ptr<MTSScene>> m_vecScene;
};

