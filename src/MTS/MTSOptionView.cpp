#include "MTSOptionView.h"
#include <sstream>

MTSOptionView::MTSOptionView(std::string_view title, std::vector<std::string> options, const MTSFont& font) :
	m_title(title),
	m_options(options)
{
	auto title_label = std::make_shared<MTSLabel>(title, font);
	addSubView(title_label);
	this->title_label = title_label;

	auto option_label = std::make_shared<MTSLabel>("", font);
	if (m_options.size() > 0) {
		option_label->setText(m_options[0]);
	}
	option_label->align = Align::RIGHT;
	addSubView(option_label);
	this->option_label = option_label;
}

void MTSOptionView::render()
{
	MTSView::render();
}

void MTSOptionView::setTitle(std::string_view title)
{
	m_title = std::string(title);
	title_label.lock()->setText(title);
}

std::string_view MTSOptionView::getTitle()
{
	return std::string_view(m_title);
}

void MTSOptionView::addOption(std::string_view option)
{
	m_options.push_back(std::string(option));
	if (m_options.size() == 1) {
		option_label.lock()->setText(option);
	}
}

std::string_view MTSOptionView::getOption()
{
	return std::string_view(m_options.at(m_value));
}

std::string_view MTSOptionView::getOption(unsigned value)
{
	return std::string_view(m_options.at(value));
}

void MTSOptionView::setValue(unsigned value)
{
	if (value >= m_options.size())
		return;
	m_value = value;
	activate();
}

unsigned MTSOptionView::getValue() const
{
	return m_value;
}

const std::size_t MTSOptionView::getOptionNum() const
{
	return m_options.size();
}

void MTSOptionView::activate()
{
	std::ostringstream ss;
	if (m_value == 0) {
		ss << " " << getOption() << ">";
	}
	else if (m_value == m_options.size() - 1) {
		ss << "<" << getOption() << " ";
	}
	else {
		ss << "<" << getOption() << ">";
	}
	option_label.lock()->setText(ss.view());
}

void MTSOptionView::inactivate()
{
	std::ostringstream ss;
	ss << " " << getOption() << " ";
	option_label.lock()->setText(ss.view());
}

void MTSOptionView::setRect(const SDL_Rect& rect)
{
	MTSView::setRect(rect);
	option_label.lock()->setPos(rect.w, 0);
}
