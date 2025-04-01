#include "LinkedStack.h"
using namespace std;
LinkedStack::~LinkedStack() {
    while (!isEmpty()) {
        StackNode* temp = top;
        top = top->next;
        delete temp;
    }
}

void LinkedStack::push(int row, int col, int dir) {
    StackNode* newNode = new StackNode(row, col, dir);
    newNode->next = top;
    top = newNode;
}

bool LinkedStack::pop(int& row, int& col, int& dir) {
    if (isEmpty()) return false;
    StackNode* temp = top;
    row = temp->row;
    col = temp->col;
    dir = temp->dir;
    top = top->next;
    delete temp;
    return true;
}