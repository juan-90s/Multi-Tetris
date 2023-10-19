#pragma once
#include "MTSView.h"
#include "MTSLabel.h"

class MTSOptionView :
    public MTSView
{
public:
	MTSOptionView() = delete;
	MTSOptionView(std::string_view title, std::vector<std::string> options, const MTSFont& font);

	void render() override;

	void setTitle(std::string_view title);
	std::string_view getTitle();

	void addOption(std::string_view option);
	std::string_view getOption();
	std::string_view getOption(unsigned value);

	void setValue(unsigned value);
	unsigned getValue() const;

	const std::size_t getOptionNum() const;
	void activate();
	void inactivate();


	void setRect(const SDL_Rect& rect) override;

	std::weak_ptr<MTSLabel> title_label;
	std::weak_ptr<MTSLabel> option_label;
private:
	std::string m_title;
	std::vector<std::string> m_options;
	unsigned m_value = 0;
};

