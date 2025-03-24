#include "bsai24005_Editor.h"
#include <conio.h>  // For _getch()
#include <iostream> // Add this for std::cout, std::endl, etc.
#include <algorithm> // Add this for std::min, std::max

using namespace std;

Editor::Editor() : running(true), mode('N'), cursorX(0), cursorY(0) {
    buffer.push_back(vector<char>());  // Start with an empty line
}

void Editor::start() {
    cout << "Text Editor Started in Normal Mode. Press 'i' to Insert, ':' for Command Mode, 'q' to Quit.\n";
    while (running) {
        char input = _getch();
        processInput(input);
    }
}

void Editor::processInput(char input) {
    if (mode == 'N') { // Normal Mode
        if (input == 'i') {
            mode = 'I';
            cout << "\nSwitched to Insert Mode.\n";
        }
        else if (input == ':') {
            mode = 'C';
            cout << "\nSwitched to Command Mode. Enter command:\n";
        }
        else if (input == 'q') {
            running = false;
            cout << "\nExiting editor.\n";
        }
        // Navigation commands
        else if (input == 'h' && cursorX > 0) {
            cursorX--;
        }
        else if (input == 'l' && cursorX < buffer[cursorY].size()) {
            cursorX++;
        }
        else if (input == 'j' && cursorY < buffer.size() - 1) {
            cursorY++;
            cursorX = min(cursorX, (int)buffer[cursorY].size());
        }
        else if (input == 'k' && cursorY > 0) {
            cursorY--;
            cursorX = min(cursorX, (int)buffer[cursorY].size());
        }
        else if (input == 'w') {
            // Move to the beginning of the next word
            while (cursorX < buffer[cursorY].size() && buffer[cursorY][cursorX] != ' ') cursorX++;
            while (cursorX < buffer[cursorY].size() && buffer[cursorY][cursorX] == ' ') cursorX++;
        }
        else if (input == 'b') {
            // Move to the beginning of the previous word
            while (cursorX > 0 && buffer[cursorY][cursorX - 1] == ' ') cursorX--;
            while (cursorX > 0 && buffer[cursorY][cursorX - 1] != ' ') cursorX--;
        }
        else if (input == 'g') {
            // Handle 'gg' (move to the beginning of the file)
            char nextInput = _getch();
            if (nextInput == 'g') {
                cursorY = 0;
                cursorX = 0;
            }
        }
        else if (input == '$') {
            // Move to the end of the current line
            cursorX = buffer[cursorY].size();
        }
        else if (input == 'G') {
            // Move to the end of the file
            cursorY = buffer.size() - 1;
            cursorX = buffer[cursorY].size();
        }
        else if (input == 4) { // Ctrl+d (scroll down half a page)
            int halfPage = (buffer.size() - 1) / 2;
            cursorY = min(cursorY + halfPage, (int)buffer.size() - 1);
        }
        else if (input == 21) { // Ctrl+u (scroll up half a page)
            int halfPage = (buffer.size() - 1) / 2;
            cursorY = max(cursorY - halfPage, 0);
        }
        // Delete commands
        else if (input == 'x') { // x: Delete character under the cursor
            if (cursorX < buffer[cursorY].size()) {
                saveState(); // Save state before making changes
                buffer[cursorY].erase(buffer[cursorY].begin() + cursorX);
                updateScreen();
            }
        }
        else if (input == 'd') {
            char nextInput = _getch();
            if (nextInput == 'd') { // dd: Delete current line
                if (buffer.size() > 1) {
                    saveState(); // Save state before making changes
                    buffer.erase(buffer.begin() + cursorY);
                    if (cursorY >= buffer.size()) cursorY = buffer.size() - 1;
                    cursorX = 0;
                    updateScreen();
                }
            }
            else if (nextInput == 'D') { // D: Delete from cursor to the end of the line
                saveState(); // Save state before making changes
                buffer[cursorY].erase(buffer[cursorY].begin() + cursorX, buffer[cursorY].end());
                updateScreen();
            }
        }
        // Yank and Paste commands
        else if (input == 'y') {
            char nextInput = _getch();
            if (nextInput == 'y') { // yy: Yank current line
                yankedLine = buffer[cursorY];
            }
        }
        else if (input == 'p') { // p: Paste after current line
            buffer.insert(buffer.begin() + cursorY + 1, yankedLine);
            cursorY++;
            cursorX = 0;
            updateScreen();
        }
        else if (input == 'P') { // P: Paste before current line
            buffer.insert(buffer.begin() + cursorY, yankedLine);
            cursorX = 0;
            updateScreen();
        }
        // Undo and Redo commands
        else if (input == 'u') { // u: Undo last action
            if (!undoHistory.empty()) {
                redoHistory.push_back(buffer);
                buffer = undoHistory.back();
                undoHistory.pop_back();
                updateScreen();
            }
        }
        else if (input == 18) { // Ctrl+r: Redo last undone action
            if (!redoHistory.empty()) {
                undoHistory.push_back(buffer);
                buffer = redoHistory.back();
                redoHistory.pop_back();
                updateScreen();
            }
        }
    }
    else if (mode == 'I') { // Insert Mode
        handleInsertMode(input);
    }
    else if (mode == 'C') { // Command Mode
        if (input == 27) { // ESC key
            mode = 'N';
            cout << "\nSwitched to Normal Mode.\n";
        }
        else if (input == 'w') {
            cout << "\n(Save command executed - Not yet implemented)\n";
        }
        else if (input == 'q') {
            running = false;
            cout << "\nExiting editor.\n";
        }
    }
}

void Editor::handleInsertMode(char input) {
    if (input == 27) { // ESC key
        mode = 'N';
        cout << "\nSwitched to Normal Mode.\n";
    }
    else if (input == 8) { // Backspace
        if (cursorX > 0) {
            buffer[cursorY].erase(buffer[cursorY].begin() + cursorX - 1);
            cursorX--;
        }
        else if (cursorY > 0) {
            cursorX = buffer[cursorY - 1].size();
            buffer[cursorY - 1].insert(buffer[cursorY - 1].end(), buffer[cursorY].begin(), buffer[cursorY].end());
            buffer.erase(buffer.begin() + cursorY);
            cursorY--;
        }
    }
    else if (input == '\r') { // Enter key
        vector<char> newLine(buffer[cursorY].begin() + cursorX, buffer[cursorY].end());
        buffer[cursorY].erase(buffer[cursorY].begin() + cursorX, buffer[cursorY].end());
        buffer.insert(buffer.begin() + cursorY + 1, newLine);
        cursorY++;
        cursorX = 0;
    }
    else if (input == 9) { // Tab key
        buffer[cursorY].insert(buffer[cursorY].begin() + cursorX, ' ');
        buffer[cursorY].insert(buffer[cursorY].begin() + cursorX, ' ');
        buffer[cursorY].insert(buffer[cursorY].begin() + cursorX, ' ');
        buffer[cursorY].insert(buffer[cursorY].begin() + cursorX, ' ');
        cursorX += 4;
    }
    else if (input == 224) { // Arrow keys
        char arrowKey = _getch();
        if (arrowKey == 75 && cursorX > 0) cursorX--;           // Left arrow
        else if (arrowKey == 77 && cursorX < buffer[cursorY].size()) cursorX++;  // Right arrow
        else if (arrowKey == 72 && cursorY > 0) {               // Up arrow
            cursorY--;
            cursorX = min(cursorX, (int)buffer[cursorY].size());
        }
        else if (arrowKey == 80 && cursorY < buffer.size() - 1) { // Down arrow
            cursorY++;
            cursorX = min(cursorX, (int)buffer[cursorY].size());
        }
    }
    else { // Regular character input
        buffer[cursorY].insert(buffer[cursorY].begin() + cursorX, input);
        cursorX++;
    }

    updateScreen();
}

void Editor::saveState() {
    // Save the current buffer state to undoHistory
    undoHistory.push_back(buffer);
    // Clear redo history when a new change is made
    redoHistory.clear();
}

void Editor::updateScreen() {
    system("cls");
    for (int i = 0; i < buffer.size(); i++) {
        for (char c : buffer[i]) cout << c;
        cout << endl;
    }
    gotoRowCol(cursorY, cursorX);
}