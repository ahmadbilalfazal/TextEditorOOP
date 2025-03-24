#pragma once
#include "bsai24005_Document.h"
#include "bsai24005_Utils.h"
#include <vector>
#include <iostream> // Add this for std::cout, std::endl, etc.
using namespace std;
class Editor {
private:
    Document doc;
    bool running;
    char mode; // 'N' - Normal, 'I' - Insert, 'C' - Command
    int cursorX, cursorY;
    vector<vector<char>> buffer; // Use std::vector explicitly
    vector<char> yankedLine; // Store the yanked line
    vector<vector<vector<char>>> undoHistory; // Stores past states for undo
    vector<vector<vector<char>>> redoHistory; // Stores undone states for redo

public:
    Editor();
    void start();
    void processInput(char input);
    void handleInsertMode(char input);
    void saveState();
    void updateScreen();
};