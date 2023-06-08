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
    virtual void nav_up();
    virtual void nav_down();
    virtual void enter_select() = 0;

    std::vector<MTSLabel> m_vecLabel = {};
    unsigned m_index = 0;
};

