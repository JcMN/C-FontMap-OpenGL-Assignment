#pragma once
#ifndef FONT_H
#define FONT_H
#include "../thirdparty/pugixml/src/pugixml.hpp"
#include "../wolf/wolf.h"
#include "extras.h"
#include <iostream>
#include <unordered_map>

class Font {
    public:
        Font(std::string p_pathToTexture, std::string p_pathToXML);
        ~Font();
        wolf::Texture* getTextureFromChar() const;
        const QuadInfo& getQuad(int p_uiCharId) const;
        const float getLineHeight() const;

    private:

        wolf::Texture* m_pTex = nullptr;
        std::string m_pathTotTexture;
        std::string m_pathToXML;
        std::unordered_map<int, QuadInfo> quadMap;
        float m_fLineHeight;
};

#endif