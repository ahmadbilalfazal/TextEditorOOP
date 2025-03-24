#pragma once
#include "bsai24005_Chapters.h"

class Document {
private:
    Chapter* chapters;
    int chapCount;

public:
    Document();
    ~Document();
    void addChapter(const char* txt);
    void display() const;
};