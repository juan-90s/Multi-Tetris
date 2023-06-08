#include "MainOption.h"

void MainOption::init()
{
	MTSFont font("assets/repetition.ttf", 40, { 255, 255, 255 });
	TextVector binary_options{"ON", "OFF"};
	TextVector difficulty_options{"EASY", "NORMAL", "HARD"};
	add_cell("MUSIC", std::make_shared<TextVector>(binary_options), font);
	add_cell("DIFFICULTY", std::make_shared<TextVector>(difficulty_options), font);
	evaluate();
}
