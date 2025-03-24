#pragma once
#include "bsai24005_Sections.h"

class Chapter {
private:
    Section* sections;
    int secCount;

public:
    Chapter();
    ~Chapter();
    void addSection(const char* txt);
    void display() const;
};