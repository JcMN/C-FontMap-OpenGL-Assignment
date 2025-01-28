#include "font.h"

Font::Font(std::string p_pathToTexture, std::string p_pathToXML){
    m_pathTotTexture = p_pathToTexture;
    m_pathToXML = p_pathToXML;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(p_pathToXML.c_str());
    pugi::xml_node font = doc.child("font");

    pugi::xml_node common = font.child("common");


    for(pugi::xml_node child : font.child("chars").children("char")){
        QuadInfo quad(child.attribute("x").as_int(), child.attribute("y").as_int(), child.attribute("width").as_int(),
        child.attribute("height").as_int(), child.attribute("xoffset").as_int(), child.attribute("yoffset").as_int(), 
        child.attribute("xadvance").as_int(), common.attribute("scaleW").as_int(), common.attribute("scaleH").as_int(),
        common.attribute("lineHeight").as_int());
        int keyId = child.attribute("id").as_int();
        quad.calculateUVCoords(common.attribute("scaleW").as_int(), common.attribute("scaleH").as_int());

        quadMap.insert({keyId, quad});
    }
    m_fLineHeight = common.attribute("lineHeight").as_int();
    m_pTex = wolf::TextureManager::CreateTexture(m_pathTotTexture);
}

Font::~Font(){
    m_pTex = nullptr;
 }

wolf::Texture* Font::getTextureFromChar() const{
    return m_pTex;
}

const QuadInfo& Font::getQuad(int p_uiCharId) const{
    return quadMap.at(p_uiCharId);
}

const float Font::getLineHeight() const{
    return m_fLineHeight;
}
