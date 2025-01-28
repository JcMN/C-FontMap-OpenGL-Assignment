#pragma once
#ifndef TEXTTABLE_H
#define TEXTTABLE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>


class TextTable {
    public:
        TextTable();
        ~TextTable();

        static void load(std::string p_sPathToFile);
        static void setLanguage(std::string p_sLanguage);
        static std::string getString(std::string p_sStringID);
        static void setStringProperty(std::string p_sPropertyString, std::string p_sStringToReplacer);

        static std::string m_sLanguage;
        static std::string m_sPathToFile;
        static std::string m_sStr;
        static std::vector<std::vector<std::string>> m_vStrings;
        static std::unordered_map<std::string, std::string> m_mapStrings;
        
};

#endif