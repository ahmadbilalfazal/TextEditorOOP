#include "bsai24005_Document.h"
using namespace std;

Document::Document() {
    chapters = nullptr;
    chapCount = 0;
}

Document::~Document() {
    delete[] chapters;
}

void Document::addChapter(const char* txt) {
    Chapter* newChaps = new Chapter[chapCount + 1];
    for (int i = 0; i < chapCount; i++)
        newChaps[i] = chapters[i];
    newChaps[chapCount] = Chapter();
    newChaps[chapCount].addSection(txt);

    delete[] chapters;
    chapters = newChaps;
    chapCount++;
}

void Document::display() const {
    for (int i = 0; i < chapCount; i++)
        chapters[i].display();
}
