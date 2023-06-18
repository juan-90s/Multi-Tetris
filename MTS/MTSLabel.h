#pragma once
#include "MTSTexture.h"
#include "MTSFont.h"
#include "MTSView.h"
#include <string>
#include <string_view>

enum class Align {
    LEFT, CENTER, RIGHT
};


class MTSLabel :
    public MTSView
{
public:
    
    MTSLabel() = default;
    MTSLabel(std::string_view str_view, const MTSFont& font);

    void render() override;

    void setText(std::string_view str_view);
    std::string_view getText() const;
    MTSFont getFont() const;

    Align align = Align::LEFT;
private:
    MTSFont m_font;
    std::string m_text;
    MTSTexture m_texture;
};

