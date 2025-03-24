#include "bsai24005_Sections.h"
using namespace std;

Section::Section() {
    paragraphs = nullptr;
    paraCount = 0;
}

Section::~Section() {
    delete[] paragraphs;
}

void Section::addParagraph(const char* txt) {
    Paragraph* newParas = new Paragraph[paraCount + 1];
    for (int i = 0; i < paraCount; i++)
        newParas[i] = paragraphs[i];
    newParas[paraCount] = Paragraph();
    newParas[paraCount].addLine(txt);

    delete[] paragraphs;
    paragraphs = newParas;
    paraCount++;
}

void Section::display() const {
    for (int i = 0; i < paraCount; i++)
        paragraphs[i].display();
}
