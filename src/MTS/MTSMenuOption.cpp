#include "MTSMenuOption.h"
#include "MTSUtility.h"
#include <sstream>

void MTSMenuOption::draw()
{
	MTSTexture::fillRect(m_Rect, { 0,0,0,150 });
	int x = (m_Rect.x + m_Rect.w) / 10;
	int y = 150;
	for (int i = 0; i < m_vecLabel.size(); i++) {
		m_vecLabel[i].first.copyToRenderer(x, y, Align::LEFT);
		m_vecLabel[i].second.copyToRenderer(9 * x, y, Align::RIGHT);
		y += 80;
	}
}

void MTSMenuOption::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			nav_left();
			break;
		case SDLK_RIGHT:
			nav_right();
			break;
		case SDLK_UP:
			nav_up();
			break;
		case SDLK_DOWN:
			nav_down();
			break;
		case SDLK_ESCAPE:
			this->quit();
			break;
		}
		break;
	default:
		break;
	}
}

void MTSMenuOption::evaluate()
{
	for (unsigned i = 0; i < m_options.size(); i++) {
		auto& value = m_options[i].value;
		//m_vecLabel[i].first.setText(m_options[i].title);
		if (i == m_index) {
			highlight_current_option();
		}
		else {
			m_vecLabel[i].second.setText(m_options[i].getText());
		}
		
	}
}

void MTSMenuOption::nav_up()
{
	const unsigned size = static_cast<unsigned>(m_vecLabel.size());
	const auto& option_text_original = m_options[m_index].getText();
	// remove " < > " in last option text
	m_vecLabel[m_index].second.setText(option_text_original);

	scroll(m_index, size, -1);
	highlight_current_option();
	
}

void MTSMenuOption::nav_down()
{
	const unsigned size = static_cast<unsigned>(m_vecLabel.size());
	const auto& option_text_original = m_options[m_index].getText();
	// remove " < > " in last option text
	m_vecLabel[m_index].second.setText(option_text_original);

	scroll(m_index, size, 1);
	highlight_current_option();
}

void MTSMenuOption::nav_left()
{
	const auto& size = m_options[m_index].max;
	auto& option_value = m_options[m_index].value;
	scroll(option_value, size, -1);
	highlight_current_option();
}

void MTSMenuOption::nav_right()
{
	const auto& size = m_options[m_index].max;
	auto& option_value = m_options[m_index].value;
	scroll(option_value, size, 1);
	highlight_current_option();
}


void MTSMenuOption::add_cell(std::string_view title, std::shared_ptr<TextVector> options, const MTSFont& font)
{
	m_options.push_back(Option(title, options));
	m_vecLabel.push_back(std::make_pair(MTSLabel(title, font), MTSLabel("NULL", font)));
}

void MTSMenuOption::highlight_current_option()
{
	std::ostringstream ss;
	if (m_options[m_index].value == 0) {
		ss << "  " << m_options[m_index].getText() << " >";
	}
	else if(m_options[m_index].value == m_options[m_index].max - 1) {
		ss << "< " << m_options[m_index].getText() << "  ";
	}
	else {
		ss << "< " << m_options[m_index].getText() << " >";
	}
	m_vecLabel[m_index].second.setText(ss.view());
}