#pragma once
#include "MTSTexture.h"
#include "MTSFont.h"
#include <string>
#include <string_view>

enum class Align {
    LEFT, CENTER, RIGHT
};


class MTSLabel :
    public MTSTexture
{
public:
    MTSLabel() = default;
    MTSLabel(std::string_view str_view, const MTSFont& font);

    using MTSTexture::copyToRenderer;
    void copyToRenderer(const int x, const int y, const Align align_flag);

    void setText(std::string_view str_view);
    std::string_view getText() const;
    MTSFont getFont() const;
private:
    MTSFont m_font;
    std::string m_text;
};

