#pragma once
#include "MTSScene.h"
#include "MTSLabel.h"
#include "MTSTableView.h"
#include "SDL_mixer.h"
#include <vector>
class MTSMenu :
    public MTSScene
{
public:
    MTSMenu();
    explicit MTSMenu(const SDL_Rect& rect);
    void init() override;
    void renderCustom() override;
    void handleEvent(SDL_Event& event) override;
    void addCell(std::shared_ptr<MTSView> cell);
protected:
    virtual void nav_up();
    virtual void nav_down();
    virtual void nav_left();
    virtual void nav_right();
    virtual void press_enter() {};
    virtual void activate(unsigned index);
    virtual void inactivate(unsigned index);

    unsigned m_index = 0;
    std::shared_ptr<MTSTableView> m_tableView;
    Mix_Chunk* sound = nullptr;
};

