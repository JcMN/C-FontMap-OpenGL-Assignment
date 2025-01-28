#include "sampleText.h"

SampleText::~SampleText(){
    delete m_pTextBox;
    m_pTextBox = nullptr;
    delete m_pFont;
    m_pFont = nullptr;
    delete m_pTextBox2;
    m_pTextBox2 = nullptr;
    delete m_pFont2;
    m_pFont2 = nullptr;
    delete m_pTextBox3;
    m_pTextBox3 = nullptr;
    delete m_pFont3;
    m_pFont3 = nullptr;
    delete m_pTextBox4;
    m_pTextBox4 = nullptr;
    delete m_pFont4;
    m_pFont4 = nullptr;
}

void SampleText::init(){
    if(!m_pFont){
    m_pFont = new Font("data/fontMap7_0.png", "data/fontMap7.xml");
    m_pFont2 = new Font("data/fontMap4_0.png", "data/fontMap4.xml");
    m_pFont3 = new Font("data/fontMap3_0.png", "data/fontMap3.xml");
    m_pFont4 = new Font("data/fontMap8_0.png", "data/fontMap8.xml");


    TextTable::load("data/Book(CSVAssignment1).csv");
    TextTable::setLanguage("ENGLISH");
 
    TextTable::setStringProperty("name", "Juan Carlos");
    TextTable::setStringProperty("age", "24");
    
    std::string str2 = TextTable::getString("str_greeting"); 
    std::string str = TextTable::getString("str_course_name");

    m_pTextBox = new TextBox(m_pFont, str, 400.0f, 200.0f);
    m_pTextBox2 = new TextBox(m_pFont2, str2, 250.0f, 200.0f);
    m_pTextBox3 = new TextBox(m_pFont3, str, 250.0f, 200.0f);
    m_pTextBox4 = new TextBox(m_pFont4, str, 500.0f, 500.0f);


    m_pTextBox->setPosition(glm::vec3(-650.0f, 50.0f, -50.0f));
    m_pTextBox2->setPosition(glm::vec3(300.0f, -250.0f, -50.0f));
    m_pTextBox3->setPosition(glm::vec3(0.0f, -100.0f, -50.0f));
    m_pTextBox4->setPosition(glm::vec3(500.0f, 50.0f, -50.0f));

    m_pTextBox->setVeticalAllignment(AL_BOTTOM);
    m_pTextBox2->setHorizantlAllignment(AL_CENTER);
    m_pTextBox2->setVeticalAllignment(AL_MIDDLE);
    m_pTextBox3->setHorizantlAllignment(AL_RIGHT);

    m_pTextBox->setText("Thats {} {}", "all", "folks!");
    m_pTextBox->setColour(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    m_pTextBox2->setColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_pTextBox3->setColour(glm::vec4(0.0f, 0.4f, 1.0f, 1.0f));
    }
}

void SampleText::update(float dt){
    m_fUpdate += dt;
}

void SampleText::render(int width, int height){
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 m_mProj = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 1000.0f);
    glm::mat4 m_mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 600.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    m_pTextBox->render(m_mView, m_mProj);
    m_pTextBox2->render(m_mView, m_mProj);
    m_pTextBox3->render(m_mView, m_mProj);
    m_pTextBox4->render(m_mView, m_mProj);

}
