#pragma once
#include "bsai24005_Paragraph.h"

class Section {
private:
    Paragraph* paragraphs;
    int paraCount;

public:
    Section();
    ~Section();
    void addParagraph(const char* txt);
    void display() const;
};
