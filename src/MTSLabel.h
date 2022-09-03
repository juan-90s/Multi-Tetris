#pragma once
#include "MTSTexture.h"
#include "MTSFont.h"
#include <map>
#include <string>

enum class Align {
    LEFT, CENTER, RIGHT
};


class MTSLabel :
    public MTSTexture
{
public:
    MTSLabel() = default;
    MTSLabel(const std::string str, const MTSFont& font);

    using MTSTexture::copyToRenderer;
    void copyToRenderer(const int x, const int y, const Align align_flag);

    void setText(const std::string str);

private:
    MTSFont m_font;
};

