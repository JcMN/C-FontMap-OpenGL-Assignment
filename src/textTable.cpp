#include "textTable.h"

std::string TextTable::m_sLanguage = "";
std::string TextTable::m_sPathToFile = "";
std::string TextTable::m_sStr = "";
std::vector<std::vector<std::string>> TextTable::m_vStrings;
std::unordered_map<std::string, std::string> TextTable::m_mapStrings;

TextTable::TextTable(){}

TextTable::~TextTable(){}

void TextTable::load(std::string p_sPathToFile){
    TextTable::m_sPathToFile = p_sPathToFile;
    std::ifstream fileReader(m_sPathToFile);

    std::string line;
    while(std::getline(fileReader, line)){
        std::vector<std::string> row;
        std::stringstream strStream(line);
        std::string cell;
        while(std::getline(strStream, cell, ',')){
            row.push_back(cell);
        }
        TextTable::m_vStrings.push_back(row); 
    }
    fileReader.close();   
} 

void TextTable::setLanguage(std::string p_sLanguage){
    TextTable::m_sLanguage = p_sLanguage;
}

std::string TextTable::getString(std::string p_sStringID){
    int languageIndex = -1;
    if(!TextTable::m_vStrings.empty()){
        for (size_t i = 1; i < m_vStrings[0].size(); i++){
            if(m_vStrings[0][i] == m_sLanguage){
                languageIndex = i;
                break;
            }
        }
    }

    for (size_t i = 1; i < m_vStrings.size(); i++){
        if (m_vStrings[i][0] == p_sStringID){
            m_sStr = m_vStrings[i][languageIndex];
            for (const auto& pair : m_mapStrings){
                std::string placeHolder = "{" + pair.first + "}";
                size_t pos = m_sStr.find(placeHolder);
                
                while(pos != std::string::npos){
                    m_sStr.replace(pos, placeHolder.length(), pair.second);
                    pos = m_sStr.find(placeHolder, pos + pair.second.length());
                }
            }
            return m_sStr;
        }
        
    }
    
    return "Error";
}

void TextTable::setStringProperty(std::string p_sPropertyString, std::string p_sStringToReplacer){
    TextTable::m_mapStrings.insert({p_sPropertyString, p_sStringToReplacer});
}
