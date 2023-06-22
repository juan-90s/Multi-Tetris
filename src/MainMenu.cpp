#include "MainMenu.h"
#include "MainOption.h"
#include "TetrisOption.h"
#include "Config.h"


void MainMenu::init(){
    MTSFont font("assets/repetition.ttf", 50, { 255, 255, 255 });
    m_view->setPos(100, 100);
    addCell(std::make_shared<MTSLabel>("PLAY", font));
    addCell(std::make_shared<MTSLabel>("OPTION", font));
    addCell(std::make_shared<MTSLabel>("QUIT", font));
    activate(0);

}

void MainMenu::press_enter(){
    switch (m_index)
    {
    case 0:
        push(new TetrisOption({ 0, 0, m_view->getRect().w, m_view->getRect().h }));
        break;
    
    case 1:
        push(new MainOption({ 0, 0, m_view->getRect().w, m_view->getRect().h }));
        break;
    
    case 2:
        quit();
        break;

    default:
        break;
    }
}