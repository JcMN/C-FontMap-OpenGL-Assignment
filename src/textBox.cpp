#include "textBox.h"

TextBox::TextBox(Font *p_pFont, std::string p_sStr, float p_fWidth, float p_fHeight){
    m_pFont = p_pFont;
    m_sText = p_sStr;
    m_fWidth = p_fWidth;
    m_fHeight = p_fHeight;
    m_iVertexCount = 0;
    m_vColour = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    m_eHorizontalAllignment = AL_LEFT;
    m_eVerticalAllignment = AL_TOP;
    m_bNeedRecalc = false;

    if(m_pMat == nullptr){
        createQuads();
        

        m_pTex = m_pFont->getTextureFromChar();
        m_pTex->SetWrapMode(wolf::Texture::WM_Clamp);
        m_pMat = wolf::MaterialManager::CreateMaterial("text_material");
        m_pMat->SetTexture("texture1", m_pTex);
        m_pMat->SetProgram("data/text.vsh", "data/text.fsh");
        m_pMat->SetDepthTest(true);
        m_pMat->SetDepthWrite(true);
   
        m_pVB = wolf::BufferManager::CreateVertexBuffer(m_vVertices.data(), sizeof(Vertex) * m_iVertexCount);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }
}

TextBox::~TextBox(){ }


void TextBox::setColour(glm::vec4 p_vColour){
    m_vColour = p_vColour;
}

void TextBox::setHorizantlAllignment(Allignment p_eHorizontalAllignment){
    if (m_eHorizontalAllignment != p_eHorizontalAllignment)
    {
        m_eHorizontalAllignment = p_eHorizontalAllignment;
        m_bNeedRecalc = true;
    }
}

void TextBox::setVeticalAllignment(Allignment p_eVerticalAllignment){
    if (m_eVerticalAllignment != p_eVerticalAllignment)
    {
        m_eVerticalAllignment = p_eVerticalAllignment;
        m_bNeedRecalc = true;
    }
}

void TextBox::setPosition(glm::vec3 p_vPosition){
    m_vPosition = p_vPosition;
}


Font *TextBox::getFont() const{
    return m_pFont;
}

void TextBox::update(float dt){ }

void TextBox::render(const glm::mat4 &m_mView, const glm::mat4 &m_mProj){

    if (m_bNeedRecalc){
        createQuads();
    }

    glm::mat4 m_mWorld = glm::translate(glm::mat4(1.0f), m_vPosition);
    m_pMat->SetUniform("proj", m_mProj);
    m_pMat->SetUniform("view", m_mView);
    m_pMat->SetUniform("world", m_mWorld);
    m_pMat->SetTexture("texture1", m_pTex);
    m_pMat->SetUniform("textColor", m_vColour);
    m_pMat->SetUniform("tt", true);
    m_pMat->Apply();

    m_pDecl->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_pMat->SetUniform("tt", false);
    m_pMat->Apply();
    m_pDecl->Bind();

    glDrawArrays(GL_TRIANGLES, 6, m_iVertexCount);

}

void TextBox::createQuads(){
    m_vVertices.clear();
    float cursorY = m_fHeight; 
    m_fLineHeight = m_pFont->getLineHeight();;
    float currentLineWidth = 0.0f;

    std::vector<std::string> lines;
    std::istringstream streamString(m_sText);
    std::string word;
    std::string currentLine;
    std::string previousLine;

    float totalHeight = 0.0f;
    bool textFits = false;

    
    // The TextBox itself!
    Vertex vT1 = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    Vertex vT2 = {0.0f, m_fHeight, 0.0f, 0.0f , 0.0f};
    Vertex vT3 = {m_fWidth, 0.0f, 0.0f, 0.0f, 0.0f };
    Vertex vT4 = {m_fWidth, m_fHeight, 0.0f, 0.0f, 0.0f};
    //Triangle 1 textbox
    m_vVertices.push_back(vT1);
    m_vVertices.push_back(vT2);
    m_vVertices.push_back(vT3);

    //Triangle 2 textbox
    m_vVertices.push_back(vT2);
    m_vVertices.push_back(vT3);
    m_vVertices.push_back(vT4);

    while (!textFits)
    {
        lines.clear();
        totalHeight = 0.0f;
        currentLineWidth = 0.0f;
        currentLine = "";

        streamString.clear();
        streamString.str(m_sText);
            

        while(streamString >> word){

            float wordWidth = calculateWordWidth(word);

            if (currentLineWidth + wordWidth > m_fWidth){

                if (!currentLine.empty()){
                    
                    lines.push_back(currentLine);
                    totalHeight += m_fLineHeight;
                    currentLine = "";
                    currentLineWidth = 0.0f;

                    if(totalHeight > m_fHeight){
                        break;
                    }
                }
                currentLine = word + " ";
                previousLine = "";
                currentLineWidth += wordWidth;
            }else{
                previousLine = currentLine;
                currentLine += word + " ";
                currentLineWidth += wordWidth;
            }
        }
        if (!currentLine.empty()){
            lines.push_back(currentLine);
            totalHeight += m_fLineHeight;
        }

        if(totalHeight <= m_fHeight){
            textFits = true;
        }else{
            m_fLineHeight *= 0.9f;
        }
    }


    if (m_eVerticalAllignment == AL_TOP){
        cursorY = m_fHeight;
    } else if (m_eVerticalAllignment == AL_MIDDLE) {
        cursorY = (m_fHeight + totalHeight) / 2.0f;
    } else if (m_eVerticalAllignment == AL_BOTTOM) {
        cursorY = totalHeight;
    }

    for (const auto& line : lines) {
        renderLine(line, m_fLineHeight, cursorY);
        cursorY -= m_fLineHeight;
    }
    
    m_iVertexCount = m_vVertices.size();
    if (m_bNeedRecalc) {
        //This feels dangerous but wolf doesn't have somehting to update the buffer, I think...
        m_pVB = wolf::BufferManager::CreateVertexBuffer(m_vVertices.data(), sizeof(Vertex) * m_iVertexCount);
        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }
    m_bNeedRecalc = false;
}
void TextBox::renderLine(const std::string &p_sLine, float p_fLineHeight, float p_fCursorY){
    float cursorX = 0.0f;
    float lineWidth = 0.0f;
    float scaleFactor = p_fLineHeight / m_pFont->getLineHeight();

    for (auto character : p_sLine) {
        QuadInfo quad = m_pFont->getQuad(int(character));
        lineWidth += quad.m_xAdvance * scaleFactor;
    }

    if (m_eHorizontalAllignment == AL_CENTER) {
        cursorX = (m_fWidth - lineWidth) / 2.0f;
    } else if (m_eHorizontalAllignment == AL_RIGHT) {
        cursorX = m_fWidth - lineWidth;
    }

    for (auto character : p_sLine) {
        QuadInfo quad = m_pFont->getQuad(int(character));
        quad.calculateUVCoords(quad.m_pTexWidth, quad.m_pTexHeight);

        float scaledCharWidth = quad.m_charWidth * scaleFactor;
        float scaledCharHeight = quad.m_charHeight * scaleFactor;
        float scaledXOffset = quad.m_xOffset * scaleFactor;
        float scaledYOffset = quad.m_yOffset * scaleFactor;

        float x1 = cursorX + scaledXOffset;
        float y1 = p_fCursorY - scaledYOffset;
        float x2 = x1 + scaledCharWidth;
        float y2 = y1 - scaledCharHeight;

        Vertex v1 = {x1, y1, 0.0f, quad.m_fU1, quad.m_fV1};
        Vertex v2 = {x2, y1, 0.0f, quad.m_fU2, quad.m_fV1};
        Vertex v3 = {x2, y2, 0.0f, quad.m_fU2, quad.m_fV2};
        Vertex v4 = {x1, y2, 0.0f, quad.m_fU1, quad.m_fV2};

        //Triangle 1
        m_vVertices.push_back(v1);
        m_vVertices.push_back(v2);
        m_vVertices.push_back(v3);

        //Triangle 2
        m_vVertices.push_back(v1);
        m_vVertices.push_back(v3);
        m_vVertices.push_back(v4);

        cursorX += quad.m_xAdvance * scaleFactor;
    }
}

float TextBox::calculateWordWidth(const std::string &word) const{
    float wordWidth = 0.0f;

    for (auto character : word) {
        const QuadInfo& quad = m_pFont->getQuad(int(character));
        float scaleWidth = (m_fLineHeight / m_pFont->getLineHeight()) * quad.m_xAdvance;
        wordWidth += scaleWidth;  
    }

    return wordWidth;
}