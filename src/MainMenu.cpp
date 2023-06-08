#include "MainMenu.h"
#include "MainOption.h"
#include "Tetris.h"


void MainMenu::init(){
    MTSFont font("assets/repetition.ttf", 50, { 255, 255, 255 });
    m_vecLabel.push_back(MTSLabel("PLAY", font));
    m_vecLabel.push_back(MTSLabel("OPTION", font));
    m_vecLabel.push_back(MTSLabel("QUIT", font));
}

void MainMenu::enter_select(){
    switch (m_index)
    {
    case 0:
        push(new Tetris(m_Rect, 20, 10, 32, 2));
        break;
    
    case 1:
        push(new MainOption(m_Rect));
        break;
    
    case 2:
        quit();
        break;
    
    default:
        break;
    }
}