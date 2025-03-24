#pragma once
#include "bsai24005_Line.h"

class Paragraph {
private:
    Line* lines;
    int lineCount;

public:
    Paragraph();
    ~Paragraph();
    void addLine(const char* txt);
    void display() const;
};