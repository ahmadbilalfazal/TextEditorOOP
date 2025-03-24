#include "bsai24005_Line.h"
using namespace std;

Line::Line() {
    text = new char[1];
    text[0] = '\0';
    length = 0;
}

Line::Line(const char* txt) {
    length = 0;
    while (txt[length] != '\0') length++;

    text = new char[length + 1];
    for (int i = 0; i < length; i++) text[i] = txt[i];
    text[length] = '\0';
}

Line::~Line() {
    delete[] text;
}

void Line::setText(const char* txt) {
    delete[] text;

    length = 0;
    while (txt[length] != '\0') length++;

    text = new char[length + 1];
    for (int i = 0; i < length; i++) text[i] = txt[i];
    text[length] = '\0';
}

const char* Line::getText() const {
    return text;
}

void Line::display() const {
    cout << text << endl;
}
