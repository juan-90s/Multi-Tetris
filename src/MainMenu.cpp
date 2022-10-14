#include "MainMenu.h"
#include "Tetris.h"


void MainMenu::init(){
    MTSFont font("assets/repetition.ttf", 50, { 255, 255, 255 });
    m_vecLabel.push_back(MTSLabel("PLAY", font));
    m_vecLabel.push_back(MTSLabel("OPTION", font));
    m_vecLabel.push_back(MTSLabel("QUIT", font));
}

void MainMenu::release(){

}


void MainMenu::nav_right(){
    switch (m_index)
    {
    case 0:
        push(new Tetris(m_Rect, 20, 10, 32, 1));
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