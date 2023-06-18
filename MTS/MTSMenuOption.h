#pragma once
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "MTSScene.h"
#include "MTSLabel.h"

using TextVector = std::vector<std::string_view>;

class MTSMenuOption :
	public MTSScene
{
public:
	using MTSScene::MTSScene;
	void renderCustom() override;
	void handleEvent(SDL_Event& event) override;
	
protected:
	class Option {
	public:
		const std::string_view title;
		const std::shared_ptr<TextVector> optionText_ptr;
		const unsigned max;
		unsigned value;
		Option() = delete;
		Option(std::string_view title, std::shared_ptr<TextVector> options) :
			title{ title },
			optionText_ptr{ options },
			max{ static_cast<unsigned>(options->size()) },
			value{ 0 }
		{}
		std::string_view getText() const{
			return optionText_ptr->at(value);
		}
	};
	virtual void nav_up();
	virtual void nav_down();
	virtual void nav_left();
	virtual void nav_right();

	void add_cell(std::string_view title, std::shared_ptr<TextVector> options, const MTSFont& font);
	void evaluate();

	std::vector<Option> m_options;

private:
	std::vector<std::pair<MTSLabel, MTSLabel>> m_vecLabel{};
	unsigned m_index = 0;
	void highlight_current_option();
};