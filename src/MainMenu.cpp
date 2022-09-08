#include "MainMenu.h"
#include "Tetris.h"


MainMenu::MainMenu(const SDL_Rect& rect){
    m_Rect = rect;
    MTSFont font("assets/novem___.ttf", 24, {255, 255, 255});
    m_arrLabel[0] = MTSLabel("Play", font);
    m_arrLabel[1] = MTSLabel("Option", font);
    m_arrLabel[2] = MTSLabel("Quit", font);
    m_Cursor = MTSLabel("->", font);
}

void MainMenu::init(){

}

void MainMenu::release(){

}

void MainMenu::update(){

}

void MainMenu::draw(){
    int centerX = (m_Rect.x + m_Rect.w) / 2;
    int centerY = (m_Rect.y + m_Rect.h) / 2;
    centerY -= 3 * 80;
    for (int i = 0; i < 3; i++){
        centerY += 80;
        m_arrLabel[i].copyToRenderer(centerX, centerY, Align::CENTER);
        int space = m_arrLabel[i].getWidth() / 2 + 50;
        if (i == m_index)
            m_Cursor.copyToRenderer(centerX - space, centerY, Align::RIGHT);
    }
}

void MainMenu::handleEvent(SDL_Event& event )
{
    switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			nav_in();
			break;
		case SDLK_UP:
			nav_up();
			break;
		case SDLK_DOWN:
			nav_down();
			break;
		}
		break;
	default:
		break;
	}
}

void MainMenu::nav_down(){
    m_index = (m_index + 1) % 3;
}

void MainMenu::nav_up(){
    m_index = (m_index - 1) % 3;
}

void MainMenu::nav_in(){
    switch (m_index)
    {
    case 0:
        Tetris* new_game;
        new_game = new Tetris(m_Rect, 20, 10, 32);
        new_game->init();
        push(new_game);
        break;
    
    case 1:
        
        break;
    
    case 2:
        quit();
        break;
    
    default:
        break;
    }
}