#pragma once
#include "MTSScene.h"
#include "MTSLabel.h"
#include <vector>
class MTSMenu :
    public MTSScene
{
public:
    using MTSScene::MTSScene;
    void draw() override;
    void handleEvent(SDL_Event& event) override;
protected:
    void nav_up();
    void nav_down();
    virtual void nav_in();

    std::vector<MTSLabel> m_vecLabel = {};
    int m_index = 0;
};

