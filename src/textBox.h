#pragma once
#ifndef TEXTBOX_H
#define TEXTBOX_H
#include "../wolf/wolf.h"
#include <iostream>
#include "font.h"
#include "extras.h"
#include <vector>
#include <sstream>
#include <format>

class TextBox{
    public:
        TextBox(Font* p_pFont, std::string p_sStr, float p_fWidth, float p_fHeight);

        ~TextBox();

        void update(float dt);
        void render(const glm::mat4 &m_mView, const glm::mat4 &m_mProj);
        void setColour(glm::vec4 p_vColour);
        void setHorizantlAllignment(Allignment p_eHorizontalAllignment);
        void setVeticalAllignment(Allignment p_eVerticalAllignment);
        void setPosition(glm::vec3 p_vPosition);
        Font* getFont() const;

        //So templates need to have any function it uses said template declared and defined in the header file cause reasons?
        template <typename... Args>
        void setText(const std::string& p_sStringFormat, Args&&... args){
            m_sText = std::vformat(p_sStringFormat, std::make_format_args(args...));
            m_bNeedRecalc = true;
        }


    private:
        void createQuads();
        void renderLine(const std::string& p_sLine, float p_fLineHeight, float p_fCursorY);
        float calculateWordWidth (const std::string& word) const;

        wolf::Material* m_pMat = nullptr;
        wolf::VertexBuffer* m_pVB = nullptr;
        wolf::VertexDeclaration* m_pDecl = nullptr;
        wolf::Texture* m_pTex = nullptr;
        Font* m_pFont = nullptr;

        float m_fPosition;
        float m_fHeight, m_fWidth, m_fLineHeight;
        int m_iVertexCount;
        bool m_bNeedRecalc;

        std::vector<Vertex> m_vVertices;
        std::string m_sText;

        glm::vec4  m_vColour;
        glm::vec3 m_vPosition;

        Allignment m_eHorizontalAllignment;
        Allignment m_eVerticalAllignment;

};

#endif