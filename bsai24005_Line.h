#pragma once
#include <iostream>

class Line {
private:
    char* text;
    int length;

public:
    Line();
    Line(const char* txt);
    ~Line();
    void setText(const char* txt);
    const char* getText() const;
    void display() const;
};