#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "textBox.h"
#include "font.h"
#include "textTable.h"

class SampleText: public Sample{
    public:
        SampleText(wolf::App* p_pApp) : Sample(p_pApp, "Assignment 1 Text Rendering"){}
        ~SampleText();

        void init() override;
        void update(float dt) override;
        void render(int width, int height) override;

    private:
        float m_fUpdate = 0;
        TextBox* m_pTextBox = nullptr;
        TextBox* m_pTextBox2 = nullptr;
        TextBox* m_pTextBox3 = nullptr;
        TextBox* m_pTextBox4 = nullptr;
        Font* m_pFont = nullptr;
        Font* m_pFont2 = nullptr;
        Font* m_pFont3 = nullptr;
        Font* m_pFont4 = nullptr;

};