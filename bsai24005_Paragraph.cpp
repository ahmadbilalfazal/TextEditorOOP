#include "bsai24005_Paragraph.h"
using namespace std;

Paragraph::Paragraph() {
    lines = nullptr;
    lineCount = 0;
}

Paragraph::~Paragraph() {
    delete[] lines;
}

void Paragraph::addLine(const char* txt) {
    Line* newLines = new Line[lineCount + 1];
    for (int i = 0; i < lineCount; i++)
        newLines[i] = lines[i];
    newLines[lineCount] = Line(txt);

    delete[] lines;
    lines = newLines;
    lineCount++;
}

void Paragraph::display() const {
    for (int i = 0; i < lineCount; i++)
        lines[i].display();
}
