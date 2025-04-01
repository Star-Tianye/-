#pragma once
#include<iostream>
using namespace std;
// ��ջ�ڵ㶨��
struct StackNode {
    int row, col, dir;  // �С��С�����0:��,1:��,2:��,3:��
    StackNode* next;
    StackNode(int r, int c, int d) : row(r), col(c), dir(d), next(nullptr) {}
};

// ��ջ��
class LinkedStack {
public:
    LinkedStack() : top(nullptr) {}
    ~LinkedStack();
    void push(int row, int col, int dir); // ��ջ
    bool pop(int& row, int& col, int& dir); // ��ջ
    bool isEmpty() const { return top == nullptr; }

private:
    StackNode* top;
};