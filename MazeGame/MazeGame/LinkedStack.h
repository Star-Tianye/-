#pragma once
#include<iostream>
using namespace std;
// 链栈节点定义
struct StackNode {
    int row, col, dir;  // 行、列、方向（0:上,1:右,2:下,3:左）
    StackNode* next;
    StackNode(int r, int c, int d) : row(r), col(c), dir(d), next(nullptr) {}
};

// 链栈类
class LinkedStack {
public:
    LinkedStack() : top(nullptr) {}
    ~LinkedStack();
    void push(int row, int col, int dir); // 入栈
    bool pop(int& row, int& col, int& dir); // 出栈
    bool isEmpty() const { return top == nullptr; }

private:
    StackNode* top;
};