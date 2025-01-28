#pragma once
#include "../wolf/wolf.h"

struct QuadInfo {
    int m_leftPos, m_topPos, m_charWidth, m_charHeight, m_xOffset, m_yOffset, m_xAdvance,  m_pTexWidth, m_pTexHeight, m_totalLineHeight;
    float m_fU1, m_fV1, m_fU2, m_fV2;
    QuadInfo (int p_leftPos, int p_topPos, int p_charWidth, int p_charHeight, int p_xOffset, int p_yOffset, int p_xAdvance, int p_textureWidth, int p_textureHeight, int p_totalLineHeight) : 
    m_leftPos(p_leftPos), m_topPos(p_topPos), m_charWidth(p_charWidth), m_charHeight(p_charHeight), 
    m_xOffset(p_xOffset), m_yOffset(p_yOffset), m_xAdvance(p_xAdvance), m_pTexWidth(p_charWidth), m_pTexHeight(p_textureHeight), m_totalLineHeight(p_totalLineHeight)
    { }
    void calculateUVCoords(float p_fTextureWidth, float p_fTextureHeight){
        this->m_fU1 = m_leftPos / p_fTextureWidth;
        this->m_fV1 = m_topPos / p_fTextureHeight;
        this->m_fU2 = (m_leftPos + m_charWidth) /  p_fTextureWidth;
        this->m_fV2 = (m_topPos + m_charHeight) / p_fTextureHeight;
        this->m_pTexWidth = p_fTextureWidth;
        this->m_pTexHeight = p_fTextureHeight;
    }
};

struct Vertex {
    GLfloat x, y, z;
    GLfloat u, v;
};

enum Allignment {
    AL_LEFT,
    AL_CENTER,
    AL_RIGHT,   
    AL_TOP,
    AL_MIDDLE,
    AL_BOTTOM
};
