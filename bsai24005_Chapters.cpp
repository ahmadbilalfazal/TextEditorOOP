#include "bsai24005_Chapters.h"
using namespace std;

Chapter::Chapter() {
    sections = nullptr;
    secCount = 0;
}

Chapter::~Chapter() {
    delete[] sections;
}

void Chapter::addSection(const char* txt) {
    Section* newSecs = new Section[secCount + 1];
    for (int i = 0; i < secCount; i++)
        newSecs[i] = sections[i];
    newSecs[secCount] = Section();
    newSecs[secCount].addParagraph(txt);

    delete[] sections;
    sections = newSecs;
    secCount++;
}

void Chapter::display() const {
    for (int i = 0; i < secCount; i++)
        sections[i].display();
}
